#ifndef __Ventana_
#define __Ventana_

#include "RocketListener.h"

class Ventana :  public Ogre::WindowEventListener
{
public:
    Ventana();
    void go();

private:
  //  BaseVistas* vista;
     // ModeloVista* modeloVista;
	  RocketListener* listener;

};

#endif
