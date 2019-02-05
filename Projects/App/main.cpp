#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BlenderCam.h"
#include "Model.h"
#include "Cube.h"
#include "Sphere.h"
#include "Background.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	// activate the window
	window.setActive(true);

	GLenum err = glewInit();

	if (GLEW_OK != err) 
	{
		std::cout << "Problem with loading open GL\n";
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);


	Model model("./res/model/hammer_LP", "hammer_LP.fbx");

	Material* sky_box = MaterialLibrary::CreateMaterial("sky_box", "res/shaders/sky_box.shader");
	Cube cube(1.0f);

	Material* testMat = MaterialLibrary::CreateMaterial("test", "res/shaders/pbr_RM.shader");

	IBLMaps maps[] = 
	{
		Background::GenerateMaps("res/enviro/Theatre_Center/Theatre-Center_2k.hdr"),
		Background::GenerateMaps("res/enviro/Newport_Loft/Newport_Loft_Ref.hdr"),
		Background::GenerateMaps("res/enviro/Sierra_Madre_B/Sierra_Madre_B_Ref.hdr"),
		Background::GenerateMaps("res/enviro/Circus_Backstage/Circus_Backstage_3k.hdr"),
		Background::GenerateMaps("res/enviro/Milkyway/Milkyway_small.hdr")
	};
	int currentMap = 0;
	sky_box->SetUniform("environmentMap", 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    BlenderCam cam;

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)window.getSize().x / (float)window.getSize().y, 0.1f, 100.0f);
	//projection = glm::ortho(0.0f,1.0f, 1.0f, 0.0f, 0.1f, 100.0f);
	model.SetProjection(projection);
	sky_box->SetUniform("projection", projection);
	testMat->SetUniform("projection", projection);

	glm::mat4 modelMat;
	modelMat = glm::scale(modelMat, glm::vec3(0.01, 0.01, 0.01));

	glm::mat4 sphereModel;

	float lastX = 0;
	float lastY = 0;

	sf::Clock clock;
	bool running = true;
	float totalTime = 0;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Key::Escape) {
					running = false;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::Space)
				{
					if (currentMap < 4)
					{
						currentMap++;
					}
					else
					{
						currentMap = 0;
					}
				}
			}
		}

		float dt = clock.restart().asSeconds();
		totalTime += dt;

		glm::vec3 ligtPos[] =
		{
			glm::vec3(std::cosf(totalTime) * 10, -10, std::sinf(totalTime) * 10),
			glm::vec3(std::cosf(totalTime) * 10, -5, std::sinf(totalTime) * 10),
			glm::vec3(std::cosf(totalTime) * 10, 5, std::sinf(totalTime) * 10),
			glm::vec3(std::cosf(totalTime) * 10, 10, std::sinf(totalTime) * 10),
		};

        //Set the lights to no color because I liked the look of IBL by itself
		model.UpdateLights(ligtPos, 4, new glm::vec3[4]{
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
		});


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		{
            cam.MoveForward(5 * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
		{
            cam.MoveForward(-5 * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
            cam.StrafeRight(5 * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		{
            cam.StrafeRight(-5 * dt);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			
            cam.RotateY((sf::Mouse::getPosition(window).x - lastX) * dt * 10);
            cam.RotateX(((lastY - sf::Mouse::getPosition(window).y)) * dt * 10);
            
            lastX = sf::Mouse::getPosition(window).x;
			lastY = sf::Mouse::getPosition(window).y;

		}
		else
		{
			lastX = sf::Mouse::getPosition(window).x;
			lastY = sf::Mouse::getPosition(window).y;
		}

		model.Update(modelMat, cam.GetViewMatrix(), cam.GetPosition());
		sky_box->SetUniform("view", cam.GetViewMatrix());
		testMat->SetUniform("view", cam.GetViewMatrix());

		Renderer::Clear();
		glActiveTexture(GL_TEXTURE0 + 5);
		glBindTexture(GL_TEXTURE_CUBE_MAP, maps[currentMap].irradianceMap);
		glActiveTexture(GL_TEXTURE0 + 6);
		glBindTexture(GL_TEXTURE_CUBE_MAP, maps[currentMap].prefilterMap);
		glActiveTexture(GL_TEXTURE0 + 7);
		glBindTexture(GL_TEXTURE_2D, maps[currentMap].lut);

		model.Draw();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, maps[currentMap].enviormentMap);
		Renderer::Draw(&cube, sky_box);
		window.display();
	}
	return 0;
}