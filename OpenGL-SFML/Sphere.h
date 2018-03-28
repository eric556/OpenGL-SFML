#pragma once
#include "Mesh.h"


class Sphere : public Mesh 
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Sphere"/> class.
	/// </summary>
	/// <param name="radius">The radius of the sphere.</param>
	Sphere(float radius);
private:
	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359;
};