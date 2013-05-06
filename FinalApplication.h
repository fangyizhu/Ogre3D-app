#pragma once

#include "BaseApplication.h"
#include "Cube.h"
#include <deque>
#include <vector>
#include <string>

class FinalApplication : public BaseApplication
{
public:
	FinalApplication(void);
	virtual ~FinalApplication(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createFrameListener(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	
	Ogre::Real mDistance;                  // The distance the object has left to travel
    Ogre::Vector3 mDirection;              // The direction the object is moving
    Ogre::Vector3 mDestination;            // The destination the object is moving towards
 
    Ogre::AnimationState *mAnimationState; // The current animation state of the object
 
    Ogre::Entity *mEntity;                 // The Entity we are animating
    Ogre::SceneNode *mNode;                // The SceneNode that the Entity is attached to
    std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to

    Ogre::Real mWalkSpeed;                 // The speed at which the object is moving


	//---------------- cube ---------------
	std::vector<Cube*> _cubes;
	std::vector<Ogre::Entity*> _cubeEntities;
	std::vector<std::string> _cubeEntityNames;
	std::vector<Ogre::SceneNode*> _cubeNodes;
	std::vector<std::string> _cubeNodeNames;

private:
    bool processUnbufferedInput(const Ogre::FrameEvent& evt);
	void createCubeEntity(Ogre::Vector3 position, float size);
};
