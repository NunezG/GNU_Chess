#ifndef __FrameListeners_
#define __FrameListeners_

#define OGRE_STATIC_OctreeSceneManager
#define STATIC_LIB


#define _RTSS_WRITE_SHADERS_TO_DISK
//#define ENABLE_SHADERS_CACHE_SAVE 1
//#define ENABLE_SHADERS_CACHE_LOAD 1


#include "OgreFramework.h"
#include "RocketEventListener.h"


//#include <Ogre.h>

//#include "MenuRocket.h"
//#include "VistaAjedrez.h"
//#include "VistaAjedrezSolo.h"





 



class FrameListeners : public Ogre::FrameListener
{
public:
	   FrameListeners(OgreFramework* fw);

    ~FrameListeners(void);



		// FrameListener interface.
		virtual bool frameStarted(const Ogre::FrameEvent& evt);


    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		
	ModeloVista* modeloVista;

	OgreFramework* framework;

	//Ogre::Ray getCameraToViewportRay();
	 virtual void setVistaActiva(RocketEventListener* vista);
	 virtual void borraVistaActiva();
	    	   		 RocketEventListener* vistaActiva;

	 		//	bool running;

protected:



private:
  
		
};

#endif
