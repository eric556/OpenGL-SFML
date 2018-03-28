#pragma once
#include "Mesh.h"

class Plane : public Mesh
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Plane"/> class.
	/// </summary>
	/// <param name="width">The width of the pane.</param>
	/// <param name="height">The height of the pane.</param>
	Plane(float width, float height);
};