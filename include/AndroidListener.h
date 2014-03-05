#ifndef __AndroidListener_H__
#define __AndroidListener_H__

#include "OgreBuildSettings.h"
#include "OgreLogManager.h"
#include "OgrePlugin.h"
#include "OgreFileSystemLayer.h"


#include "Ventana.h"
#include "Ogre.h"
#include "OIS.h"
#include <android_native_app_glue.h>
#include <android/log.h>
#include <EGL/egl.h>
#include "OgrePlatform.h"
#include "Android/OgreAndroidEGLWindow.h"

#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"

#ifdef USAROCKET
#include <Rocket/Core/FileInterface.h>
#endif
#include "AndroidFileInterface.h"

//#ifdef INCLUDE_RTSHADER_SYSTEM
//# include "ShaderSystem.h"

//#include "RenderSystems/GLES2/"

//#endif

#ifdef OGRE_STATIC_LIB
#   include "OgreStaticPluginLoader.h"
#endif

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
#   error This header is for use with Android only
#endif

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Ogre", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Ogre", __VA_ARGS__))

class OgreAndroidBridge;




/*=============================================================================
     | Android input handling
     =============================================================================*/
class AndroidMultiTouch : public OIS::MultiTouch
{
public:
    AndroidMultiTouch():OIS::MultiTouch("Ogre", false, 0, 0){}

    /** @copydoc Object::setBuffered */
    virtual void setBuffered(bool buffered){}

    /** @copydoc Object::capture */
    virtual void capture(){}

    /** @copydoc Object::queryInterface */
    virtual OIS::Interface* queryInterface(OIS::Interface::IType type) {return 0;}

    /** @copydoc Object::_initialize */
    virtual void _initialize(){}

    OIS::MultiTouchState &getMultiTouchState(int i){
        while(i >= mStates.size()){
            Ogre::RenderWindow* pRenderWnd = static_cast<Ogre::RenderWindow*>(Ogre::Root::getSingleton().getRenderTarget("OgreWindow"));
            if(pRenderWnd)
            {

                OIS::MultiTouchState state;
                state.width = pRenderWnd->getWidth();
                state.height = pRenderWnd->getHeight();
                mStates.push_back(state);
            }
        }
        return mStates[i];
    }
};

class AndroidKeyboard : public OIS::Keyboard
{
public:
    AndroidKeyboard():OIS::Keyboard("Ogre", false, 1, 0){}

    /** @copydoc Object::setBuffered */
    virtual void setBuffered(bool buffered){}

    /** @copydoc Object::capture */
    virtual void capture(){}

    /** @copydoc Object::queryInterface */
    virtual OIS::Interface* queryInterface(OIS::Interface::IType type) {return 0;}

    /** @copydoc Object::_initialize */
    virtual void _initialize(){}

    virtual bool isKeyDown( OIS::KeyCode key ) const{
        return false;
    }

    virtual const std::string& getAsString( OIS::KeyCode kc ){
        static std::string defstr = "";
        return defstr;
    }

    virtual void copyKeyStates( char keys[256] ) const{

    }
};

/*=============================================================================
     | Android input injection
     =============================================================================*/
class AndroidInputInjector
{
private:
    Ventana* mVentana;
    AndroidMultiTouch* mTouch;
    AndroidKeyboard* mKeyboard;

public:

    AndroidInputInjector(Ventana* ventana, AndroidMultiTouch* touch, AndroidKeyboard* keyboard)
        : mVentana(ventana), mTouch(touch), mKeyboard(keyboard) {}

    void injectKeyEvent(int action, int32_t keyCode)
    {
        if(keyCode == AKEYCODE_BACK)
        {
            OIS::KeyEvent evt(mKeyboard, OIS::KC_ESCAPE, 0);
            if(action == 0)
            {
                mVentana->vista->keyPressed(evt);
            }
            else
            {
                mVentana->vista->keyReleased(evt);
            }
        }
    }

    void injectTouchEvent(int action, float x, float y, int pointerId = 0)
    {
        OIS::MultiTouchState &state = mTouch->getMultiTouchState(pointerId);

        switch(action)
        {
        case 0:
            state.touchType = OIS::MT_Pressed;
            break;
        case 1:
            state.touchType = OIS::MT_Released;
            break;
        case 2:
            state.touchType = OIS::MT_Moved;
            break;
        case 3:
            state.touchType = OIS::MT_Cancelled;
            break;
        default:
            state.touchType = OIS::MT_None;
        }

        if(state.touchType != OIS::MT_None)
        {
            int last = state.X.abs;
            state.X.abs =  (int)x;
            state.X.rel = state.X.abs - last;

            last = state.Y.abs;
            state.Y.abs = (int)y;
            state.Y.rel = state.Y.abs - last;

            state.Z.abs = 0;
            state.Z.rel = 0;

            OIS::MultiTouchEvent evt(mTouch, state);

            switch(state.touchType)
            {
            case OIS::MT_Pressed:
                mVentana->vista->touchPressed(evt);
                break;
            case OIS::MT_Released:
                mVentana->vista->touchReleased(evt);
                break;
            case OIS::MT_Moved:
                mVentana->vista->touchMoved(evt);
                break;
            case OIS::MT_Cancelled:
                mVentana->vista->touchCancelled(evt);
                break;
            default:
                break;
            }
        }
    }
};

/*=============================================================================
     | Ogre Android bridge
     =============================================================================*/
class OgreAndroidBridge
{
public:
    static void init(struct android_app* state)
    {


        state->onAppCmd = &OgreAndroidBridge::handleCmd;
        state->onInputEvent = &OgreAndroidBridge::handleInput;

        if(mInit)
            return;


        /*
#ifdef OGRE_STATIC_LIB
        mStaticPluginLoader = new Ogre::StaticPluginLoader();
        mStaticPluginLoader->load();
#endif
        mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));
*/
        if(!mVentana)
        {
            mVentana= OGRE_NEW Ventana();
            //    mVentana->init();

            // mBrowser = OGRE_NEW SampleBrowser();
            //mBrowser->initAppForAndroid(mRenderWnd, app, mTouch, mKeyboard);
            // mBrowser->initApp();

            //  mWindow = createWindow();

            mRoot = new Ogre::Root();
            mVentana->listener->mRoot = mRoot;


            mVentana->listener->configuraOgre();
            mRoot->initialise(false);



            //  mVentana->vista->mAssetMgr = mAssetMgr;
            // = mAssetMgr;
            //   mVentana->listener->configuraRocket();


            // mRenderWnd->


        }










        mInit = true;





    }

    static void shutdown()
    {
        if(!mInit)
            return;

        mInit = false;
        /*
            if(mBrowser)
            {
                mBrowser->closeApp();
                OGRE_DELETE mBrowser;
                mBrowser = NULL;
            }
      */
        OGRE_DELETE mRoot;
        mRoot = NULL;
        mRenderWnd = NULL;

        delete mTouch;
        mTouch = NULL;

        delete mKeyboard;
        mKeyboard = NULL;

        delete mInputInjector;
        mInputInjector = NULL;

#ifdef OGRE_STATIC_LIB
        mStaticPluginLoader->unload();
        delete mStaticPluginLoader;
        mStaticPluginLoader = NULL;
#endif
    }

    static int32_t handleInput(struct android_app* app, AInputEvent* event)
    {
        if (mInputInjector)
        {
            if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
            {
                int action = (int)(AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(event));

                if(action == 0)
                    mInputInjector->injectTouchEvent(2, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );

                mInputInjector->injectTouchEvent(action, AMotionEvent_getRawX(event, 0), AMotionEvent_getRawY(event, 0) );
            }
            else
            {
                mInputInjector->injectKeyEvent(AKeyEvent_getAction(event), AKeyEvent_getKeyCode(event));
            }

            return 1;
        }
        return 0;
    }

    static void handleCmd(struct android_app* app, int32_t cmd)
    {
        switch (cmd)
        {
        case APP_CMD_SAVE_STATE:
            break;
        case APP_CMD_INIT_WINDOW:

            if (app->window && mRoot)
            {
                AConfiguration* config = AConfiguration_new();
                AConfiguration_fromAssetManager(config, app->activity->assetManager);

                if (!mRenderWnd)
                {

                    // locateResources();




                    Ogre::NameValuePairList opt;
                    opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)app->window);
                    opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

                    mRenderWnd = mRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);

                    if(!mTouch)
                        mTouch = new AndroidMultiTouch();

                    if(!mKeyboard)
                        mKeyboard = new AndroidKeyboard();




                    mVentana->listener->mWindow = mRenderWnd;


                    if(app != NULL)
                    {
                        mAssetMgr = app->activity->assetManager;
                        Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(app->activity->assetManager) );
                        Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(app->activity->assetManager) );
                    }

                    //			 AndroidFileInterface*  mAndroidFileInterface = new AndroidFileInterface(mAssetMgr);
                    //            Rocket::Core::SetFileInterface(mAndroidFileInterface);

                    mVentana->listener->configuraGraficos();








                    mVentana->go(); //crea vista



                    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
                    // Clear event times
                    Ogre::Root::getSingleton().clearEventTimes();
                    // mVentana->vista->initEventListener();

                    mInputInjector = new AndroidInputInjector(mVentana, mTouch, mKeyboard);


                }
                else
                {
                    static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_createInternalResources(app->window, config);
                }

                AConfiguration_delete(config);
            }

            break;
        case APP_CMD_TERM_WINDOW:
            if(mRoot && mRenderWnd)
                static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_destroyInternalResources();
            break;
        case APP_CMD_GAINED_FOCUS:
            break;
        case APP_CMD_LOST_FOCUS:
            break;
        case APP_CMD_CONFIG_CHANGED:
            break;
        }
    }

    static void go(struct android_app* state)
    {



        int ident, events;
        struct android_poll_source* source;

        while (true)
        {

            while ((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
            {

                if (source != NULL){

                    source->process(state, source);
                }

                if (state->destroyRequested != 0){

                    return;

                }
            }

            if(mRenderWnd != NULL && mRenderWnd->isActive() && !mVentana->modeloVista->getApagar() && !mVentana->modeloVista->reiniciar && !mRenderWnd->isClosed() && mRenderWnd->isVisible() && !mRenderWnd->isHidden())
            {



                mRenderWnd->windowMovedOrResized();


                mRoot->renderOneFrame();

            }

        }

    }

    // static Ogre::RenderWindow* getRenderWindow()
    //{
    //  return mRenderWnd;
    // }




    /*-----------------------------------------------------------------------------
            | Finds context-wide resource groups. I load paths from a config file here,
            | but you can choose your resource locations however you want.
            -----------------------------------------------------------------------------*/
    static void locateResources()
    {

        //-------------------------------------------------------------------------------------
        // setup resources
        // Only add the minimally required resource locations to load up the Ogre head mesh




        /*

        // load resource paths from config file
        Ogre::ConfigFile cf;

        cf.load(openAPKFile(mVentana->listener->mFSLayer->getConfigFilePath("resources.cfg")));





        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
        Ogre::String sec, type, arch;

        // go through all specified resource groups
        while (seci.hasMoreElements())
        {

            sec = seci.peekNextKey();

            Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator i;

            // go through all resource paths
            for (i = settings->begin(); i != settings->end(); i++)
            {

                type = i->first;
                arch = i->second;



                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
            }
        }


        const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList("General");
        arch = genLocs.front()->archive->getName();


        */



    }



    static Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName)
    {

        Ogre::DataStreamPtr stream;
        AAsset* asset = AAssetManager_open(mAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
        if(asset)
        {
            off_t length = AAsset_getLength(asset);
            void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
            memcpy(membuf, AAsset_getBuffer(asset), length);
            AAsset_close(asset);

            stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
        }
        return stream;
    }




private:





    static AAssetManager* mAssetMgr;       // Android asset manager to access files inside apk

    //cambia el browser por lo que sea, basevistas o baselisteners por ejemplo
    static Ventana* mVentana;
    static AndroidInputInjector* mInputInjector;
    static AndroidMultiTouch* mTouch;
    static AndroidKeyboard* mKeyboard;
    static Ogre::RenderWindow* mRenderWnd;
    static Ogre::Root* mRoot;
    static bool mInit;


    //static Ventana* punteroVentana;

#ifdef OGRE_STATIC_LIB
    static Ogre::StaticPluginLoader* mStaticPluginLoader;
#endif

};



#endif
