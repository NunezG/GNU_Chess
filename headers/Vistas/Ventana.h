#ifndef __Ventana_
#define __Ventana_

#include <OgreWindowEventUtilities.h>

#include "MenuInicio.h"
#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"

class Ventana :  public Ogre::WindowEventListener
{
public:
    Ventana();
    void go();


private:
    BaseVistas* vista;
    ModeloVista* modeloVista;
};

#endif
