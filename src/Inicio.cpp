#include "OgrePlatform.h"





#include <cstdlib>
#include <cstring>
#include <ostream>
#include <iostream>


#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include <android_native_app_glue.h>
#include <AndroidListener.h>
#endif


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "OgreString.h"
#include <Ventana.h>
#endif



#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
//SampleBrowser* OgreAndroidBridge::mBrowser = NULL;
AndroidInputInjector* OgreAndroidBridge::mInputInjector = NULL;
AndroidMultiTouch* OgreAndroidBridge::mTouch = NULL;
AndroidKeyboard* OgreAndroidBridge::mKeyboard = NULL;
Ogre::RenderWindow* OgreAndroidBridge::mRenderWnd = NULL;
Ogre::Root* OgreAndroidBridge::mRoot = NULL;
bool OgreAndroidBridge::mInit = false;
Ventana* OgreAndroidBridge::mVentana = NULL;
AAssetManager* OgreAndroidBridge::mAssetMgr = NULL;


#   ifdef OGRE_STATIC_LIB
Ogre::StaticPluginLoader* OgreAndroidBridge::mStaticPluginLoader = NULL;
#   endif
#endif




#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
void android_main(struct android_app* state)
#else
int main(int argc, char *argv[])
#endif
{
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    app_dummy();

    // Make sure glue isn't stripped.

    //__android_log_write(ANDROID_LOG_INFO, "tag here", "message here");


    // Ventana* punteroVentana= new Ventana();

    OgreAndroidBridge::init(state);
    OgreAndroidBridge::go(state);

#else

    std::ofstream out("./Salida.txt");
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    try
    {


        Ventana* punteroVentana= new Ventana();

        //punteroVentana->init();
        punteroVentana->go();

        delete punteroVentana;

        // Inicio& init = new Inicio();
        // delete init;
    } catch( Ogre::Exception& e )
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " <<
                     e.getFullDescription().c_str() << std::endl;
#endif
    }
    return 0;

#endif


}




