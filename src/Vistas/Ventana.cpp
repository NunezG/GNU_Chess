#include "Ventana.h"



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



}


void Ventana::go(void)
{   
	
		listener->init();

					std::cout << "FININIT"<<std::endl;


	//std::cout << "addWindowEventListener "<<std::endl;

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
                    creaVista();

#else


                    Ogre::WindowEventUtilities::addWindowEventListener(listener->mWindow, this);


	//	std::cout << "fin addWindowEventListener "<<std::endl;

					std::cout << "EVENT"<<std::endl;

    //CREA VISTA
    while(!listener->modeloVista->getApagar())
    {
		modeloVista->reiniciar = false;


						std::cout << "CREAVISTA"<<std::endl;

        creaVista();

	//	std::cout << "empieza"<<std::endl;
		vista->createOverlay();

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
#endif

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
        vista = new VistaAjedrez(listener);


        std::cout << "escensa "<<std::endl;

        static_cast<VistaAjedrez*>(vista)->createScene();

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




            std::cout << "FINOVERLAY "<<std::endl;

	  //LISTENERS
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		listener->mInputContext.mMouse->setEventCallback(vista);
		listener->mInputContext.mKeyboard->setEventCallback(vista);
				
#else
			if(listener->mInputContext.mMultiTouch)
			{
				std::cout << "HAY MULTITOUCH!! "<<std::endl;
				listener->mInputContext.mMultiTouch->setEventCallback(vista);
            }else  std::cout << "MULTITOUCH FALTAAAA EN LSTENER  "<<std::endl;




#endif 

            std::cout << "acaba creavista "<<std::endl;

}
