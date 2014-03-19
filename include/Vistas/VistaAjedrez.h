#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_
#include "Escena.h"

#include "RocketEventListener.h"


class VistaAjedrez : public Escena, public RocketEventListener
{
public:
    VistaAjedrez(OgreFramework* fw);
    ~VistaAjedrez(void);

	     Ogre::RaySceneQuery *mRaySceneQuery;
// ModeloVista* modeloVista;
	  //  Ogre::RenderWindow* mWindow;

            std::string encuentraCasillaSobrevolada();


					void ProcessEvent(Rocket::Core::Event& event);
			/// Called from Ogre before a queue group is rendered.
	//virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
	/// Called from Ogre after a queue group is rendered.
   // virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);
	void actualizaNodo();
    void createView();


 
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
		// KeyListener interface.
		virtual bool keyPressed(const OIS::KeyEvent& e);

#endif
		
    virtual bool keyReleased(const OIS::KeyEvent& e);


   // virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);


protected:
   



private:
  //  CEGUI::Window *ventanaJaque;

  //  EscenaAjedrez* escenaAjedrez;

};

#endif // #ifndef __VistaAjedrez_h_
