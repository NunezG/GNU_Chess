#ifndef __VistaAjedrezSolo_h_
#define __VistaAjedrezSolo_h_

#include "VistaAjedrez.h"

class VistaAjedrezSolo : public VistaAjedrez
{
public:
    VistaAjedrezSolo(ModeloVista* modeloV);
    ~VistaAjedrezSolo(void);


private:


    // Ogre::FrameListener
   // bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg,OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg,OIS::MouseButtonID id );

    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

};

#endif // #ifndef __VistaAjedrezSolo_h_
