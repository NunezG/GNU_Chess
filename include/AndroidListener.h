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

//#ifdef OGRE_STATIC_LIB
//#   include "OgreStaticPluginLoader.h"
//#endif

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
                mVentana->listener->vistaActiva->keyPressed(evt);
            }
            else
            {
                mVentana->listener->vistaActiva->keyReleased(evt);
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
                mVentana->listener->vistaActiva->touchPressed(evt);
                break;
            case OIS::MT_Released:
                mVentana->listener->vistaActiva->touchReleased(evt);
                break;
            case OIS::MT_Moved:
                mVentana->listener->vistaActiva->touchMoved(evt);
                break;
            case OIS::MT_Cancelled:
                mVentana->listener->vistaActiva->touchCancelled(evt);
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



            //  mVentana->vista->mAssetMgr = mAssetMgr;
            // = mAssetMgr;
            //   mVentana->listener->configuraRocket();

            mVentana->init();


            mRoot = mVentana->framework->mRoot;

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
        OGRE_DELETE mVentana;


         // OGRE_DELETE mRoot;
          mRoot = NULL;




        //OGRE_DELETE mRenderWnd;
          mRenderWnd = NULL;



        // delete mTouch;
        //  mTouch = NULL;

        //  delete mKeyboard;
        //   mKeyboard = NULL;

        delete mInputInjector;
        mInputInjector = NULL;


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

			
		 if(app != NULL)
           {

                        mAssetMgr = app->activity->assetManager;
                        Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKFileSystemArchiveFactory(mAssetMgr) );
                        Ogre::ArchiveManager::getSingleton().addArchiveFactory( new Ogre::APKZipArchiveFactory(mAssetMgr) );
                   



		  AndroidFileInterface*  mAndroidFileInterface = new AndroidFileInterface(mAssetMgr);
                    Rocket::Core::SetFileInterface(mAndroidFileInterface);
		 }


            if (app->window && mRoot)
            {

                AConfiguration* config = AConfiguration_new();
                AConfiguration_fromAssetManager(config, mAssetMgr);

                if (!mRenderWnd)
                {

                    // locateResources();

                   


                    Ogre::NameValuePairList opt;
                    opt["externalWindowHandle"] = Ogre::StringConverter::toString((int)app->window);
                    opt["androidConfig"] = Ogre::StringConverter::toString((int)config);

                    mRenderWnd = mRoot->createRenderWindow("OgreWindow", 0, 0, false, &opt);



                    mRenderWnd->setActive(false);
                    mVentana->framework->mWindow = mRenderWnd;

                    mVentana->framework->locateResources();


                    mVentana->framework->mInputContext.mMultiTouch = new AndroidMultiTouch();

                    mVentana->framework->mInputContext.mKeyboard = new AndroidKeyboard();

                    /*  if(!mTouch)
                        mTouch = new AndroidMultiTouch();

                    if(!mKeyboard)
                        mKeyboard = new AndroidKeyboard();

*/

                    mVentana->framework->startScene();


                    //  mVentana->framework->configuraGraficos();


                    mVentana->go(); //crea vista




                    /*
                    mVentana->creaVista();


                    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
                    // Clear event times
                    Ogre::Root::getSingleton().clearEventTimes();
                    // mVentana->vista->initEventListener();

                    mInputInjector = new AndroidInputInjector(mVentana, mTouch, mKeyboard);
                    */


                }
                else
                {
                    static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_createInternalResources(app->window, config);
                }



                AConfiguration_delete(config);
            }

            break;
        case APP_CMD_TERM_WINDOW:
			std::cout << "LLAMA A TERM WINDOW"<<std::endl;
            if(mRoot && mRenderWnd)
                static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_destroyInternalResources();
            break;
        case APP_CMD_DESTROY:
            std::cout << "LLAMA A DESTROY"<<std::endl;
            if(mRoot && mRenderWnd)
               // static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_destroyInternalResources();
            break;
        case APP_CMD_STOP:
            std::cout << "LLAMA A STOPPPPP"<<std::endl;
            if(mRoot && mRenderWnd)
               // static_cast<Ogre::AndroidEGLWindow*>(mRenderWnd)->_destroyInternalResources();
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


        while (1)
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



            if(mVentana->framework->modeloVista->getApagar())
            {


                         shutdown();
                         ANativeActivity_finish(state->activity);

						   break;

           }else if(mRenderWnd != NULL && mRenderWnd->isActive() && !mRenderWnd->isClosed() && mRenderWnd->isVisible() && !mRenderWnd->isHidden())
            {

                mRenderWnd->windowMovedOrResized();

                bool resultFrame = mRoot->renderOneFrame();


            }else if(mVentana->listener && (!mVentana->listener->vistaActiva || !mVentana->listener->vistaActiva->running))
            {

                				                mVentana->creaVista();

                // mVentana->vista->initEventListener();
                delete mInputInjector;
                mInputInjector = NULL;


				                mInputInjector = new AndroidInputInjector(mVentana,static_cast<AndroidMultiTouch*>(mVentana->framework->mInputContext.mMultiTouch), static_cast<AndroidKeyboard*>(mVentana->framework->mInputContext.mKeyboard));
				Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
                // Clear event times
                Ogre::Root::getSingleton().clearEventTimes();
												  mRenderWnd->setActive(true);

            }
        }




    }

    // static Ogre::RenderWindow* getRenderWindow()
    //{
    //  return mRenderWnd;
    // }





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

    //cambia el browser por lo que sea, FrameListeners o RocketEventListener por ejemplo
    static Ventana* mVentana;
    static AndroidInputInjector* mInputInjector;
    // static AndroidMultiTouch* mTouch;
    // static AndroidKeyboard* mKeyboard;
    static Ogre::RenderWindow* mRenderWnd;
    static Ogre::Root* mRoot;
    static bool mInit;


    //static Ventana* punteroVentana;


};



#endif
