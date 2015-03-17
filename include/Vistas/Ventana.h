#ifndef __Ventana_
#define __Ventana_

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define USAROCKET
//#endif
 

#include "RocketFrameListener.h"
#include "VistaAjedrez.h"
//#include "VistaAjedrezSolo.h"
#include "MenuRocket.h"
#include "OgreFramework.h"





class Ventana 
	#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
	:  public Ogre::WindowEventListener
#endif
{
public:
    Ventana();
	~Ventana();

	void init();
    void go();

	      OgreFramework* framework;

		  RocketFrameListener* listener;
         // RocketEventListener* vista;
	  	  // ModeloVista* modeloVista;
	  	void creaVista();

private:
  //  FrameListeners* vista;
     // ModeloVista* modeloVista;


};

#endif
