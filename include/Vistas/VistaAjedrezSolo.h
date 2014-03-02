#ifndef __VistaAjedrezSolo_h_
#define __VistaAjedrezSolo_h_

#include "VistaAjedrez.h"

class VistaAjedrezSolo : public VistaAjedrez
{
public:
    VistaAjedrezSolo(RocketListener* vistaOgre);
    ~VistaAjedrezSolo(void);


private:


    // Ogre::FrameListener
   // bool frameRenderingQueued(const Ogre::FrameEvent& evt);


	
#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)
 
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg,OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg,OIS::MouseButtonID id );

	 //bool frameRenderingQueued(const Ogre::FrameEvent& evt);
   // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
#endif
   
};

#endif // #ifndef __VistaAjedrezSolo_h_
