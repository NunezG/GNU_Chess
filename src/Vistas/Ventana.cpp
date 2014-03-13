#include "Ventana.h"



Ventana::Ventana() :
    //modeloVista(modeloVista),
    vista(0)
{



    //Rocket Listener
    modeloVista = new ModeloVista();

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
modeloVista->voltea = 90;

#else
	modeloVista->voltea = 180;


#endif
    listener = new RocketListener(modeloVista);
}


void Ventana::init(void)
{ 
   



}


void Ventana::go(void)
{   
    listener->init();

   

//#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
   // modeloVista->reiniciar = false;

    //creaVista();

//#ifdef USAROCKET

  //  vista->initEventListener();
//#endif

  //  vista->createView(); //inicia vista
//#else


	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

    Ogre::WindowEventUtilities::addWindowEventListener(listener->mWindow, this);


    //CREA VISTA
    while(!listener->modeloVista->getApagar())
    {
        
        creaVista();



        //   creaVista??z
        //EMPIEZA RENDERIZADO
	
        listener->empieza();	


    }

    delete vista;

    //DESTRUYE VISTA
    Ogre::WindowEventUtilities::removeWindowEventListener(listener->mWindow, this);

    delete listener;
    listener = NULL;

    delete modeloVista;
		#endif

//#endif

}

void Ventana::creaVista()
{
    //Unattach OIS before window shutdown (very important under Linux)
    // if( listener->mInputManager )
    // {


    // }

    delete vista;

    vista = NULL;

	modeloVista->reiniciar = false;

    //vista->context->dele

//#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
 //  modeloVista->setNumPantalla(1);
//#endif

    if (modeloVista->getNumPantalla() == 0)
    {
        vista = new MenuRocket(listener);


        //static_cast<VistaAjedrez*>(vista)->createScene();

    }else
    {

        if (modeloVista->getNumPantalla() == 1)
        {

            vista =  new VistaAjedrez(listener);


        }
        else if (modeloVista->getNumPantalla() == 2) {//EL CONTRUCTOR DE FrameListeners CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI

            vista =  new VistaAjedrezSolo(listener);
        }

        //static_cast<VistaAjedrez*>(vista)->createScene();

    }
    //  listener->createScene();
   

    //LISTENERS
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    listener->mInputContext.mMouse->setEventCallback(vista);
    listener->mInputContext.mKeyboard->setEventCallback(vista);

#else

    if(listener->mInputContext.mMultiTouch)
    {
        listener->mInputContext.mMultiTouch->setEventCallback(vista);
    }




#endif 

#ifdef USAROCKET

        vista->initEventListener();
#endif
        vista->createView();

}
