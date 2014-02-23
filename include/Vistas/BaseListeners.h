#ifndef __BaseListeners_
#define __BaseListeners_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//#include <CEGUI-CEGUIUI/CEGUISystem.h>
//#include <CEGUI-CEGUIUI/CEGUIWindow.h>
//#include <CEGUI-CEGUIUI/CEGUIMinizipResourceProvider.h>
//#include <CEGUI-CEGUIUI/CEGUIEventSet.h>
//#include <CEGUI/RendererModulesCEGUIGL/CEGUIOpenGLRenderer.h>
//#include <CEGUI/CEGUI.h>


//#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "ModeloVista.h"

#include "RocketListener.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>


//#include "MenuRocket.h"
//#include "VistaAjedrez.h"
//#include "VistaAjedrezSolo.h"

#include <OgreWindowEventUtilities.h>


#include <Rocket/Core/Context.h>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>

#include <Rocket/Core/String.h>

#include <Rocket/Core/Core.h>
#include <Rocket/Debugger.h>

#include "RenderInterfaceOgre3D.h"
#include "SystemInterfaceOgre3D.h"

#if (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)

#include "Android/OgreAPKFileSystemArchive.h"
#include "Android/OgreAPKZipArchive.h"
#endif

class BaseListeners :  public Rocket::Core::EventListener,
	
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
		public OIS::KeyListener,
		public OIS::MouseListener
#else
        public OIS::MultiTouchListener
#endif

{
public:
	   BaseListeners(RocketListener* vistaOgre);

    ~BaseListeners(void);

	
     Ogre::SceneNode* mTarget;
    //Ogre::Camera* mCamera;
	//Ogre::Ray getCameraToViewportRay();
		virtual void ProcessEvent(Rocket::Core::Event& event) = 0;

#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
		virtual bool touchMoved(const OIS::MultiTouchEvent& evt);
		virtual bool touchPressed(const OIS::MultiTouchEvent& evt);
		virtual bool touchReleased(const OIS::MultiTouchEvent& evt);
		virtual bool touchCancelled(const OIS::MultiTouchEvent& evt);

		
#else
// MouseListener interface.
		virtual bool mouseMoved(const OIS::MouseEvent& e);
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);


#endif
     // KeyListener interface.
     virtual bool keyPressed(const OIS::KeyEvent& e);
     virtual bool keyReleased(const OIS::KeyEvent& e);

	void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);

   
   #if (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)

	    Rocket::Core::ElementDocument* openFontRocket(const Ogre::String& fileName);

	AAssetManager* mAssetMgr;       // Android asset manager to access files inside apk
#endif

			Rocket::Core::Context* context;

			RocketListener* vistaOgre; 
			bool reinicia;

			virtual void createOverlay() = 0;

protected:
   
//    CEGUI::System* sys;
	  //ModeloVista* modeloVista;

		  //  Ogre::RenderWindow* mWindow;
			

				    OIS::InputManager* mInputManager;

	//	 OIS::Mouse*    mMouse;
   // OIS::Keyboard* mKeyboard;
		 
		
		// Builds an OpenGL-style orthographic projection matrix.
		void buildProjectionMatrix(Ogre::Matrix4& matrix);
		
						      Ogre::SceneManager* mSceneMgr;

		//void createFrameListener();

private:
  //  int getFPS();
  //  CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

	  //  Ogre::Root *mRoot;

			SystemInterfaceOgre3D* ogre_system;
		RenderInterfaceOgre3D* ogre_renderer;
	
   // CEGUI::OgreRenderer* renderer;
		bool running;
	
		typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
		KeyIdentifierMap key_identifiers;

		
		//void destroyScene();
	
			     


};

#endif
