#ifndef __VistaAjedrez_h_
#define __VistaAjedrez_h_

#include "BaseVistas.h"

class VistaAjedrez : public  BaseVistas
{
public:
    VistaAjedrez(ModeloVista* modeloV);
    ~VistaAjedrez(void);

protected:
    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
  //  CEGUI::Window *ventanaJaque;

 //   ModeloVista* modeloVista;
    EscenaAjedrez* escenaAjedrez;

};

#endif // #ifndef __VistaAjedrez_h_
