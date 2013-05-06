#pragma once
#include "BaseApplication.h"

class Cube
{
	public:
		Cube();
		Cube(Ogre::Vector3 position, float size);
		virtual ~Cube(void);
		bool inCube(Ogre::Vector3 position);
	private:
		Ogre::Vector3 _position;
		float _size;
};

