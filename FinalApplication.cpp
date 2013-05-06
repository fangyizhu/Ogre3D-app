#include "FinalApplication.h"
#include <string>

Ogre::Vector3 grav = Ogre::Vector3(0, -1000, 0);
int jumpFlag = 0;
int jumpAnimationFlag = 0;
Ogre::Vector3 nodePos = Ogre::Vector3(0, 0, 0);
Ogre::Vector3 nodeVelocity = Ogre::Vector3(0, 0, 0);

FinalApplication::FinalApplication(void)
{
}


FinalApplication::~FinalApplication(void)
{
}

//-------------------------------------Cube----------------------------------------
void createCubeEntity(Ogre::Vector3 position, float size){
}


//-------------------------------------------------------------------------------------
void FinalApplication::createCamera(void)
{
	// create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
	// set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,200,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
	// set the near clip distance
    mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
	mCameraMan->SdkCameraMan::setStyle(OgreBites::CS_MANUAL); //CS_MANUAL
    //mCamera->setPosition(Ogre::Vector3(0,250,1000));
}

//-------------------------------------------------------------------------------------
void FinalApplication::createScene(void)
{
	//create plane
	float xTiles  = 8; //num of verticle tiles
	float yTiles = 40; //num of horizontal tiles
	float tileSize = 100.0f * 4; //size of each tile
	float width  = xTiles * tileSize / 4; //4 per checkerboard pattern
	float height = yTiles * tileSize / 4; //4 per checkerboard pattern
	int uTile  = xTiles / 4;
	int vTile = yTiles / 4;
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, width, height, 1, 1, true, 1, uTile, vTile, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3( 0, 0, -200))->attachObject(entGround);
	entGround->setMaterialName("Examples/Checkerboard");
	entGround->setCastShadows(false);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	mEntity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	mNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("NinjaNode", Ogre::Vector3(0.0f, 0.0f, 0.0f));
	mNode->attachObject(mEntity);
}

void FinalApplication::createFrameListener(void){
	BaseApplication::createFrameListener();

	// Set idle animation
    mAnimationState = mEntity->getAnimationState("Idle1");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

	// Set default values for variables
	mWalkSpeed = 35.0f;
	mDirection = Ogre::Vector3::ZERO;
}

//-------------------------------------------------------------------------------------
bool FinalApplication::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	static bool mMouseDown = false;
	static Ogre::Real mToggle = 0.0;
	static Ogre::Real mToggle1 = 0.0;
	static Ogre::Real mRotate = 0.13;
	static Ogre::Real mMove = 250;

	//mMouseDown = currMouse;

	mToggle -= evt.timeSinceLastFrame;
	

	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
	if(mKeyboard->isKeyDown(OIS::KC_I)) {
		transVector.z -= mMove;
	}
	if(mKeyboard->isKeyDown(OIS::KC_K)) {
		transVector.z += mMove;
	}

	if(mKeyboard->isKeyDown(OIS::KC_L)) {
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)){
			mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(-mRotate*5));
		} else{
			transVector.x += mMove;
		}
	}
	if(mKeyboard->isKeyDown(OIS::KC_J)) {
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)){
			mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(-mRotate*5));
		} else{
			transVector.x -= mMove;
		}
	}
	// I made J to move left and F to jump - freya

	if(mKeyboard->isKeyDown(OIS::KC_F)) {
		if(jumpFlag == 0){
			jumpFlag = 1;
			jumpAnimationFlag = 1;
			nodeVelocity.y = 500;
			mAnimationState = mEntity->getAnimationState("JumpNoHeight");
			mAnimationState->setTimePosition(0);
			mAnimationState->setLoop(false);
			mAnimationState->setEnabled(true);
		}
		//transVector.y += mMove;
	}

	if(jumpFlag == 1){
		nodeVelocity.y += grav.y*evt.timeSinceLastFrame;
		nodePos.y += nodeVelocity.y*evt.timeSinceLastFrame;
		transVector.y = nodeVelocity.y;
		if(nodePos.y <= 0){
			jumpFlag = 0;
			nodePos.y = 0;
		}
	}

	mSceneMgr->getSceneNode("NinjaNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	mCamera->move(transVector * evt.timeSinceLastFrame);

	return true;
}
//-------------------------------------------------------------------------------------
bool FinalApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(jumpFlag == 1){
	}
	if(jumpFlag == 0) {
		mAnimationState = mEntity->getAnimationState("Idle1");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);
	}

	
	if(!processUnbufferedInput(evt)) return false;
	
	mAnimationState->addTime(evt.timeSinceLastFrame);

	
    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}