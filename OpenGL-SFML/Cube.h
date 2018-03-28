#pragma once
#include "Mesh.h"

class Cube : public Mesh 
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Cube"/> class.
	/// </summary>
	/// <param name="size">The size of the cube.</param>
	Cube(float size);
};