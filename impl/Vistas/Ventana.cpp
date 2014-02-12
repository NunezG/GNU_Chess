#include "../../headers/Vistas/Ventana.h"

Ventana::Ventana() :
    //modeloVista(modeloVista),
    vista(0)
{
	//Rocket Listener
	modeloVista = new ModeloVista();
}


void Ventana::init(void)
{ 

	listener = new RocketListener(modeloVista);

	//std::cout << "addWindowEventListener "<<std::endl;
	Ogre::WindowEventUtilities::addWindowEventListener(listener->mWindow, this);
	//	std::cout << "fin addWindowEventListener "<<std::endl;

}


void Ventana::go(void)
{   
	

	

    //CREA VISTA
    while(!listener->modeloVista->getApagar())
    {
		modeloVista->reiniciar = false;
		
		creaVista();

	//	std::cout << "empieza"<<std::endl;

		//   creaVista??z
		  //EMPIEZA RENDERIZADO
        listener->empieza();
 //  std::cout << "acaba"<<std::endl;
    }		
	   std::cout << "finito"<<std::endl;
	   		  
	   
	   delete vista;
   
        //DESTRUYE VISTA
        Ogre::WindowEventUtilities::removeWindowEventListener(listener->mWindow, this);
     
		delete listener;
        listener = NULL;

		delete modeloVista;
}

void Ventana::creaVista()
{
					std::cout << "creaVista11111111111111 "<<std::endl;

	//Unattach OIS before window shutdown (very important under Linux)
   // if( listener->mInputManager )
   // {
  
        
   // }

	delete vista;
	vista = NULL;

	//vista->context->dele


				std::cout << "creaVista "<<std::endl;

    if (modeloVista->getNumPantalla() == 0)
	{
			std::cout << "vistamenurocket "<<std::endl;
		vista = new MenuRocket(listener);
			    std::cout << "escensa "<<std::endl;
			//static_cast<VistaAjedrez*>(vista)->createScene();

	}else
    {
						std::cout << "elsseee "<<std::endl;

            if (modeloVista->getNumPantalla() == 1)
			{
							   			    std::cout << "vista ajedrez a dos "<<std::endl;

               vista =  new VistaAjedrez(listener);


			}
            else if (modeloVista->getNumPantalla() == 2) {//EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
              			   			    std::cout << "vista ajedrez solo "<<std::endl;

				vista =  new VistaAjedrezSolo(listener);            
			}

			static_cast<VistaAjedrez*>(vista)->createScene();

	}
								 //  listener->createScene();
	              			   			    std::cout << "LISTENERS "<<std::endl;


			vista->createOverlay();

	  //LISTENERS
		listener->mInputContext.mMouse->setEventCallback(vista);
		listener->mInputContext.mKeyboard->setEventCallback(vista);
        listener->mRoot->addFrameListener(listener);
}