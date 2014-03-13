#ifndef __Ventana_
#define __Ventana_

#include "RocketListener.h"
#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"
#include "MenuRocket.h"






class Ventana 
	#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
	:  public Ogre::WindowEventListener
#endif
{
public:
    Ventana();
	void init();
    void go();
		  RocketListener* listener;
          EventListeners* vista;
	  	   ModeloVista* modeloVista;
	  	void creaVista();

private:
  //  FrameListeners* vista;
     // ModeloVista* modeloVista;


};

#endif
