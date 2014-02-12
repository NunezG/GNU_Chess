#ifndef __Ventana_
#define __Ventana_

#include "RocketListener.h"
#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"
#include "MenuRocket.h"

class Ventana :  public Ogre::WindowEventListener
{
public:
    Ventana();
	void init();
    void go();

private:
  //  BaseVistas* vista;
     // ModeloVista* modeloVista;
	  RocketListener* listener;
	  BaseListeners* vista;
	  	   ModeloVista* modeloVista;

	  	void creaVista();

};

#endif
