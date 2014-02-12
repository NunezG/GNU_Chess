#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "OgreString.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include "SampleBrowser_Android.h"

SampleBrowser* OgreAndroidBridge::mBrowser = NULL;
AndroidInputInjector* OgreAndroidBridge::mInputInjector = NULL;
AndroidMultiTouch* OgreAndroidBridge::mTouch = NULL;
AndroidKeyboard* OgreAndroidBridge::mKeyboard = NULL;
Ogre::RenderWindow* OgreAndroidBridge::mRenderWnd = NULL;
Ogre::Root* OgreAndroidBridge::mRoot = NULL;
bool OgreAndroidBridge::mInit = false;

#   ifdef OGRE_STATIC_LIB
StaticPluginLoader* OgreAndroidBridge::mStaticPluginLoader = NULL;
#   endif

#endif


#include "../headers/Vistas/Ventana.h"



#ifdef __cplusplus
extern "C" {
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
    // Make sure glue isn't stripped.
    app_dummy();
    
    OgreAndroidBridge::init(state);
    OgreAndroidBridge::go(state);
#else

    try
    {
  std::ofstream out("./Salida.txt");
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    Ventana* punteroVentana= new Ventana();

	punteroVentana->init();
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
	#endif


    return 0;
}

#ifdef __cplusplus
}
#endif



