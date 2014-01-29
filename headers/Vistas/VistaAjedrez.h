#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_
#include "Escena.h"

#include "BaseVistas.h"


class VistaAjedrez : public BaseVistas, public Escena
{
public:
    VistaAjedrez(ModeloVista* modeloV, Ogre::RenderWindow* mWindow);
    ~VistaAjedrez(void);


	
		

			/// Called from Ogre before a queue group is rendered.
	//virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
	/// Called from Ogre after a queue group is rendered.
   // virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);
	void actualizaNodo(ObjetoOgre* nodo);

		// MouseListener interface.
		virtual bool mouseMoved(const OIS::MouseEvent& e);
		virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);

		// KeyListener interface.
		virtual bool keyPressed(const OIS::KeyEvent& e);
		virtual bool keyReleased(const OIS::KeyEvent& e);

   // virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		void createScene();


protected:
   



private:
  //  CEGUI::Window *ventanaJaque;

  //  EscenaAjedrez* escenaAjedrez;

};

#endif // #ifndef __VistaAjedrez_h_
