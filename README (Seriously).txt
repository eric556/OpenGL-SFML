## Disclaimer
No, I am not a mathematical genius. I did not come up with this on my own (although I like to pretend I did). 
All of this code is made possible by the amazing people out in this world writing papers and coming up with 
implementations of this stuff and posting it FOR FREE on the internet. Below are some sources for the incredibly 
advanced math that people have come up with in the field of real time rendering which you can see working primarily in the shaders. 
The goal of this project was to create an OpenGL framework that I can use to render 3D models. During this process I realized 
how cool PBR and IBL shading was and decided to change the workflow from phong-blinn based lighting to PBR and IBL. 

## Links to sources
http://gamedevs.org/uploads/real-shading-in-unreal-engine-4.pdf
https://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf
http://www.trentreed.net/blog/physically-based-shading-and-image-based-lighting/
http://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.pdf
http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
https://chetanjags.wordpress.com/2015/08/26/image-based-lighting/
https://placeholderart.wordpress.com/2015/07/28/implementation-notes-runtime-environment-map-filtering-for-image-based-lighting/
http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf
https://www.shadertoy.com/view/4sSfzK

## Controls
W, A, S, D are used to pan the camera
Click the left mouse button and drag to rotate the camera
Space changes the scene

## Running the application
The application only runs on 64 bit right now (one of the libraries was not being nice). The executible is in the release folder.
of the x64 folder in the root directory. On startup you start inside the model. Hold S until you are outside to get a proper view.