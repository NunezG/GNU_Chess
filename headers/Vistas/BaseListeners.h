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

#include "../ModeloVista/ModeloVista.h"

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


class BaseListeners : public OIS::MouseListener, public OIS::KeyListener, public Rocket::Core::EventListener
{
public:
	   BaseListeners(RocketListener* vistaOgre);

    ~BaseListeners(void);

	
     Ogre::SceneNode* mTarget;
    //Ogre::Camera* mCamera;
	//Ogre::Ray getCameraToViewportRay();
		virtual void ProcessEvent(Rocket::Core::Event& event) = 0;


	void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);

		// MouseListener interface.
		virtual bool mouseMoved(const OIS::MouseEvent& e);
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);

		// KeyListener interface.
		virtual bool keyPressed(const OIS::KeyEvent& e);
		virtual bool keyReleased(const OIS::KeyEvent& e);

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
