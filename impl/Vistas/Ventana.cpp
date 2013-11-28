#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana() :
    //modeloVista(modeloVista),
    vista(NULL)

{
    modeloVista = new ModeloVista();
}

void Ventana::go(void)
{   
    //CREA VISTA
    while(!modeloVista->getApagar())
    {
        if (modeloVista->getNumPantalla() == 0)
			vista = new MenuInicio(modeloVista);
		
        else
        {
            if (modeloVista->getNumPantalla() == 1)
                vista= new VistaAjedrez(modeloVista);

            else if (modeloVista->getNumPantalla() == 2) //EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
                vista= new VistaAjedrezSolo(modeloVista);
            
            modeloVista->generaJugadores();
        }

        //LISTENERS
        vista->mRoot->addFrameListener(vista);
        //Register as a Window listener
        Ogre::WindowEventUtilities::addWindowEventListener(vista->mWindow, this);
        Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

        vista->mMouse->setEventCallback(vista);
        vista->mKeyboard->setEventCallback(vista);

        //RELLENA LA VISTA
        if (modeloVista->getNumPantalla() == 0)
            static_cast<MenuInicio*>(vista)->pantallaInicio();
        else
        {
            modeloVista->creaEscenaYModelo();
        }

        //EMPIEZA RENDERIZADO
        vista->empieza();

        //DESTRUYE VISTA
        Ogre::WindowEventUtilities::removeWindowEventListener(vista->mWindow, this);
        delete vista;
        vista = NULL;
    }
    delete modeloVista;
}
