#ifndef __BaseVistas_
#define __BaseVistas_
#define OGRE_STATIC_GL
#define OGRE_STATIC_OctreeSceneManager
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OIS.h>

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
//#include <Ogre.h>
#include <OgreStaticPluginLoader.h>

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

/*=============================================================================
	| Utility structure for passing OIS devices. Does not own them.
	=============================================================================*/
	struct InputContext
	{
		InputContext()
		{
			mKeyboard = 0;
			mMouse = 0;
			mMultiTouch = 0;
			mAccelerometer = 0;
		}

		void capture() const
		{
			if(mKeyboard)
				mKeyboard->capture();
			if(mMouse)
				mMouse->capture();
			if(mMultiTouch)
				mMultiTouch->capture();
			if(mAccelerometer)
	            mAccelerometer->capture();
		}

		bool isKeyDown(OIS::KeyCode key) const
		{
			return mKeyboard && mKeyboard->isKeyDown(key);
		}

		bool getCursorPosition(Ogre::Real& x, Ogre::Real& y) const
		{
			// prefer mouse
			if(mMouse)
			{
				x = (Ogre::Real)mMouse->getMouseState().X.abs;
				y = (Ogre::Real)mMouse->getMouseState().Y.abs;
				return true;
			}
			
			// than touch device
			if(mMultiTouch)
			{
	            std::vector<OIS::MultiTouchState> states = mMultiTouch->getMultiTouchStates();
		        if(states.size() > 0)
		        {
		        	x = (Ogre::Real)states[0].X.abs;
		        	y = (Ogre::Real)states[0].Y.abs;
		        	return true;
			    }
			}

			// fallback
			x = y = 0.0;
			return false;
		}

		OIS::Keyboard* mKeyboard;         // context keyboard device
		OIS::Mouse* mMouse;               // context mouse device
		OIS::MultiTouch* mMultiTouch;     // context multitouch device
		OIS::JoyStick* mAccelerometer;    // context accelerometer device
	};


class BaseVistas : public Ogre::RenderQueueListener, public Ogre::FrameListener
{
public:
	   BaseVistas(ModeloVista* modeloV);

    ~BaseVistas(void);

	void createCamera(void);
    void createViewports(Ogre::RenderWindow* window);
     Ogre::SceneNode* mTarget;
    Ogre::Camera* mCamera;
	//Ogre::Ray getCameraToViewportRay();
	 ModeloVista* modeloVista;

	void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);

		// FrameListener interface.
		virtual bool frameStarted(const Ogre::FrameEvent& evt);


    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);


			/// Called from Ogre before a queue group is rendered.
	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
	/// Called from Ogre after a queue group is rendered.
    virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);
			Rocket::Core::Context* context;
		    Ogre::RenderWindow* mWindow;
			//	 OIS::Mouse*    mMouse;
 //   OIS::Keyboard* mKeyboard;
		 
	    Ogre::Root *mRoot;
							InputContext mInputContext;		// all OIS devices are here

protected:
   
//    CEGUI::System* sys;

	 //   ModeloVista* modeloVista;

			

				    OIS::InputManager* mInputManager;

	// Configures Ogre's rendering system for rendering Rocket.
		void configureRenderSystem();

		
		// Builds an OpenGL-style orthographic projection matrix.
		void buildProjectionMatrix(Ogre::Matrix4& matrix);
		
						      Ogre::SceneManager* mSceneMgr;

		//void createFrameListener();
				  
	

private:


	Ogre::StaticPluginLoader*  mStaticPluginLoader;

  //  int getFPS();
  //  CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
			    bool configuraGraficos(const char *desiredRenderer);


			SystemInterfaceOgre3D* ogre_system;
		RenderInterfaceOgre3D* ogre_renderer;
	
   // CEGUI::OgreRenderer* renderer;
		bool running;
			void BuildKeyMaps();
		int GetKeyModifierState();
	
		typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
		KeyIdentifierMap key_identifiers;

		
		//void destroyScene();
	
			      void windowResized();


};

#endif
