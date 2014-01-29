#ifndef __BaseVistas_
#define __BaseVistas_

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


class BaseVistas : public Ogre::RenderQueueListener, public Ogre::FrameListener, public OIS::MouseListener, public OIS::KeyListener
{
public:
	   BaseVistas(ModeloVista* modeloV, Ogre::RenderWindow* mWindow);

    ~BaseVistas(void);


    
		// FrameListener interface.
		virtual bool frameStarted(const Ogre::FrameEvent& evt);

		// MouseListener interface.
		virtual bool mouseMoved(const OIS::MouseEvent& e);
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);

		// KeyListener interface.
		virtual bool keyPressed(const OIS::KeyEvent& e);
		virtual bool keyReleased(const OIS::KeyEvent& e);

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		   virtual void createScene();


			/// Called from Ogre before a queue group is rendered.
	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
	/// Called from Ogre after a queue group is rendered.
    virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);

protected:
   
//    CEGUI::System* sys;

	    ModeloVista* modeloVista;

		    Ogre::RenderWindow* mWindow;
			

				    OIS::InputManager* mInputManager;

		 OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
		 
	// Configures Ogre's rendering system for rendering Rocket.
		void configureRenderSystem();

		
		// Builds an OpenGL-style orthographic projection matrix.
		void buildProjectionMatrix(Ogre::Matrix4& matrix);
		

		//void createFrameListener();

private:
  //  int getFPS();
  //  CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

   // CEGUI::OgreRenderer* renderer;
		Rocket::Core::Context* context;
		bool running;
			void BuildKeyMaps();
		int GetKeyModifierState();
	
		typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
		KeyIdentifierMap key_identifiers;

		
		//void destroyScene();
	
			      void windowResized();

				      Ogre::SceneManager* mSceneMgr;

};

#endif
