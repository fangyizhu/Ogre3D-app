// **********************************************
// To use this file, uncomment the particular 
// tutorial or application you'd like to run.
// Make sure all other #define TO_RUN lines 
// are commented out.
//
// This replaces any of the main() method code
// that is referenced by the tutorials.
// **********************************************

//#define TO_RUN HW4Application
//#define TO_RUN BasicTutorial1
//#define TO_RUN BasicTutorial2
//#define TO_RUN BasicTutorial3
//#define TO_RUN BasicTutorial4
//#define TO_RUN BasicTutorial6
//#define TO_RUN BasicTutorial8
//#define TO_RUN IntermediateTutorial1
#define TO_RUN FinalApplication

#include "HW4Application.h"
#include "BasicTutorial1.h"
#include "BasicTutorial2.h"
#include "BasicTutorial3.h"
//#include "BasicTutorial4.h"
#include "BasicTutorial6.h"
#include "BasicTutorial8.h"
#include "FinalApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TO_RUN app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif