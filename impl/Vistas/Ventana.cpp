#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana() 
    //modeloVista(modeloVista),
  //  vista(NULL)

{
    
}

void Ventana::go(void)
{   
	//Rocket Listener

	listener = new RocketListener();
	std::cout << "addWindowEventListener "<<std::endl;
	Ogre::WindowEventUtilities::addWindowEventListener(listener->mWindow, this);
		std::cout << "fin addWindowEventListener "<<std::endl;

    //CREA VISTA
    while(!listener->modeloVista->getApagar())
    {
	    std::cout << "ANTES DE creaVista "<<std::endl;

		listener->creaVista();



		std::cout << "empieza"<<std::endl;

		//   creaVista??z
		  //EMPIEZA RENDERIZADO
        listener->empieza();
   std::cout << "acaba"<<std::endl;
    }		
	   std::cout << "finito"<<std::endl;


        //DESTRUYE VISTA
        Ogre::WindowEventUtilities::removeWindowEventListener(listener->mWindow, this);
        delete listener;
        listener = NULL;
}