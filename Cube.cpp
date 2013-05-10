#include "Cube.h"

Cube::Cube(void)
{
}

Cube::Cube(Ogre::Vector3 position, float size)
{
	_position = position;
	_size = size;
}

Cube::~Cube(void)
{
}

bool Cube::inCube(Ogre::Vector3 position)
{

	return false;
}
