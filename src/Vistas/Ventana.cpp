#include "Ventana.h"



Ventana::Ventana() :
    //modeloVista(modeloVista),
    listener(0)
  ,framework(0)
{


    framework = new OgreFramework();

    //Rocket Listener
    

}


Ventana::~Ventana() 
{

    delete listener;
    listener = NULL;



    delete framework;
    framework = NULL;
    

}



void Ventana::init(void)
{ 

    framework->init();


    //AQUI CREA EL LISTENER!!!





}


void Ventana::go(void)
{   

    listener = new RocketFrameListener(framework);

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
    Ogre::WindowEventUtilities::addWindowEventListener(framework->mWindow, this);


    //CREA VISTA
    while(!framework->modeloVista->getApagar())
    {
		std::cout << "REINICIA CREAVISTA!!! "  << std::endl;



        creaVista();

        //   creaVista??z
        //EMPIEZA RENDERIZADO

        framework->empieza();

    }


    //listener->borraVistaActiva();

    //  delete vista;

    //DESTRUYE VISTA
    Ogre::WindowEventUtilities::removeWindowEventListener(framework->mWindow, this);


#endif

    //#endif

}

void Ventana::creaVista()
{
    //Unattach OIS before window shutdown (very important under Linux)
    // if( listener->mInputManager )
    // {


    // }

    //ES TODO ESTO NECESARIO???
    listener->borraVistaActiva();

    RocketEventListener* vista;

    //framework->modeloVista->reiniciar = false;

    //vista->context->dele

    //#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    //framework->modeloVista->setNumPantalla(1);
    //#endif

    if (framework->modeloVista->getNumPantalla() == 0)
    {

        vista = new MenuRocket(framework);


        //static_cast<VistaAjedrez*>(vista)->createScene();

    }else
    {
  
            vista =  new VistaAjedrez(framework);


        
 
        //static_cast<VistaAjedrez*>(vista)->createScene();

    }
    //  listener->createScene();


    //ASIGNA VISTA A LISTENER!!!

    listener->setVistaActiva(vista);


    vista->createView();

    framework->mWindow->setActive(true);

    vista = NULL;

}		 

