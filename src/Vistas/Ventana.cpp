#include "Ventana.h"



Ventana::Ventana() :
    //modeloVista(modeloVista),
    vista(0)
{



    //Rocket Listener
    modeloVista = new ModeloVista();

    listener = new RocketListener(modeloVista);
}


void Ventana::init(void)
{ 
    //COUTCOMENTADOstd::cout << "RocketListener"<<std::endl;


    //COUTCOMENTADOstd::cout << "fin RocketListener"<<std::endl;



}


void Ventana::go(void)
{   
    listener->init();

    //COUTCOMENTADOstd::cout << "listeer inint"<<std::endl;



    //COUTCOMENTADOstd::cout << "FININIT"<<std::endl;


    ////COUTCOMENTADOstd::cout << "addWindowEventListener "<<std::endl;

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    modeloVista->reiniciar = false;

    creaVista();

#ifdef USAROCKET

    vista->initEventListener();
#endif

    vista->createView(); //inicia vista
#else



    Ogre::WindowEventUtilities::addWindowEventListener(listener->mWindow, this);


    //	//COUTCOMENTADOstd::cout << "fin addWindowEventListener "<<std::endl;

    //COUTCOMENTADOstd::cout << "EVENT"<<std::endl;

    //CREA VISTA
    while(!listener->modeloVista->getApagar())
    {
        modeloVista->reiniciar = false;


        //COUTCOMENTADOstd::cout << "CREAVISTA"<<std::endl;

        creaVista();


#ifdef USAROCKET

        vista->initEventListener();
#endif
        //	//COUTCOMENTADOstd::cout << "empieza"<<std::endl;
        vista->createView();

        //   creaVista??z
        //EMPIEZA RENDERIZADO
        listener->empieza();
        //  //COUTCOMENTADOstd::cout << "acaba"<<std::endl;
    }
    //COUTCOMENTADOstd::cout << "finito"<<std::endl;


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
    //COUTCOMENTADOstd::cout << "creaVista11111111111111 "<<std::endl;

    //Unattach OIS before window shutdown (very important under Linux)
    // if( listener->mInputManager )
    // {


    // }

    delete vista;
    vista = NULL;

    //vista->context->dele

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    modeloVista->setNumPantalla(1);
#endif
    //COUTCOMENTADOstd::cout << "creaVista "<<std::endl;

    if (modeloVista->getNumPantalla() == 0)
    {
        //COUTCOMENTADOstd::cout << "vistamenurocket"<<std::endl;
        vista = new MenuRocket(listener);


        //COUTCOMENTADOstd::cout << "escensa "<<std::endl;


        //static_cast<VistaAjedrez*>(vista)->createScene();

    }else
    {
        //COUTCOMENTADOstd::cout << "elsseee "<<std::endl;

        if (modeloVista->getNumPantalla() == 1)
        {
            //COUTCOMENTADOstd::cout << "vista ajedrez a dos "<<std::endl;

            vista =  new VistaAjedrez(listener);


        }
        else if (modeloVista->getNumPantalla() == 2) {//EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
            //COUTCOMENTADOstd::cout << "vista ajedrez solo "<<std::endl;

            vista =  new VistaAjedrezSolo(listener);
        }
        //COUTCOMENTADOstd::cout << "createScene "<<std::endl;

        //static_cast<VistaAjedrez*>(vista)->createScene();

    }
    //  listener->createScene();
    //COUTCOMENTADOstd::cout << "LISTENERS "<<std::endl;




    //COUTCOMENTADOstd::cout << "FINOVERLAY "<<std::endl;

    //LISTENERS
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    listener->mInputContext.mMouse->setEventCallback(vista);
    listener->mInputContext.mKeyboard->setEventCallback(vista);

#else
    if(listener->mInputContext.mMultiTouch)
    {
        //COUTCOMENTADOstd::cout << "HAY MULTITOUCH!! "<<std::endl;
        listener->mInputContext.mMultiTouch->setEventCallback(vista);
    }//else  //COUTCOMENTADOstd::cout << "MULTITOUCH FALTAAAA EN LSTENER  "<<std::endl;




#endif 

    //COUTCOMENTADOstd::cout << "acaba creavista "<<std::endl;

}
