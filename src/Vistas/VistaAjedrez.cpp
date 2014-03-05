
#include "VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(RocketListener* vistaOgre) : BaseListeners( vistaOgre), Escena(vistaOgre)
{  
    //  modelo =Modelo::getSingletonPtr();
    //  mWindow = mRoot->initialise(true, "Root Ajedrez");
    // Escena = Escena::getSingletonPtr();
    //  BaseListeners::iniciaOIS();


}

VistaAjedrez::~VistaAjedrez(void)
{    
    //COUTCOMENTADOstd::cout << "del VistaAjedrez"<<std::endl;

    mSceneMgr->destroyQuery(mRaySceneQuery);

}


void VistaAjedrez::actualizaNodo()
{



}




std::string VistaAjedrez::encuentraCasillaSobrevolada(int posx, int posy)
{
    //COUTCOMENTADOstd::cout << "encuentraCasillaSobrevolada"<<std::endl;


    Ogre::uint32 mask = CASILLA;

    Ogre::Ray rayMouse = vistaOgre->mCamera->getCameraToViewportRay
            (posx/float(vistaOgre->mWindow->getWidth()), posy/float(vistaOgre->mWindow->getHeight()));


    //COUTCOMENTADOstd::cout << "encuentraCasillaSobrevolada 2222"<<std::endl;

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);
    //COUTCOMENTADOstd::cout << "encuentraCasillaSobrevolada33333"<<std::endl;

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

    // Ogre::RaySceneQueryResult &result = executeRay(, , 'C');
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();

    if (it != result.end())
    {
        //COUTCOMENTADOstd::cout << "nodo encontrado"<<std::endl;


        Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

        return nodoSobrevolado->getName();
    }
    //COUTCOMENTADOstd::cout << "encuentraCasillaSobrevolada fin"<<std::endl;

    return "";
}



#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)

bool VistaAjedrez::touchMoved(const OIS::MultiTouchEvent& evt)
{
    //COUTCOMENTADOstd::cout << "HA DETECTADO MOVIMIENTO en VistaAjedrez!! "<<std::endl;




    BaseListeners::touchMoved(evt);
    return true;

}
/*
bool VistaAjedrez::touchPressed(const OIS::MultiTouchEvent& evt)
{

    //COUTCOMENTADOstd::cout << "HA DETECTADO UNA PULSACION VistaAjedrez!! "<<std::endl;
    BaseListeners::touchPressed(evt);
    return true;

}
*/
bool VistaAjedrez::touchReleased(const OIS::MultiTouchEvent& evt)
{
    //COUTCOMENTADOstd::cout << "HA DETECTADO UNA PULSACION SOLTADA VistaAjedrez!! "<<std::endl;
    BaseListeners::touchReleased(evt);
    return true;
}
bool VistaAjedrez::touchCancelled(const OIS::MultiTouchEvent& evt)
{

    BaseListeners::touchCancelled(evt);
    return true;

}



#else

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{  

    BaseListeners::mouseMoved(arg);
    
    //COUTCOMENTADOstd::cout << "moviendo en ajedr"<<std::endl;

    if (getModoCamara())   // yaw around the target, and pitch locally
    {
        rotacionCamara(Ogre::Degree(arg.state.X.rel/6));
    }
    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        DistanciaCamara(arg.state.Z.rel);
    }
    else{

        //COUTCOMENTADOstd::cout << "busca a ver"<<std::endl;


        const std::string casilla = encuentraCasillaSobrevolada(arg.state.X.abs, arg.state.Y.abs);
        //COUTCOMENTADOstd::cout << "fin busca a ver"<<std::endl;


        if (casilla != "")
        {
            //COUTCOMENTADOstd::cout << "encuentra casilla sobrevvv"<<std::endl;

            vistaOgre->modeloVista->JugadorActivo->casillaSobrevolada(casilla);
            actualizaNodo();
        }
        //COUTCOMENTADOstd::cout << "fincaca"<<std::endl;



    }

    //COUTCOMENTADOstd::cout << "acacacacacacadeeeeee"<<std::endl;


    return true;
}

bool VistaAjedrez::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{   
    BaseListeners::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);
    
    if(mbMiddle) setModoCamara(false);
    
    return true;
}



//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed(const OIS::KeyEvent &arg)
{    
    
    BaseListeners::keyPressed(arg);
    
    if (arg.key == OIS::KC_A || arg.key == OIS::KC_LEFT)
    {
        setCamaraIzquierda();
        //  Escena->mueveCamaraIzquierda();
        //   mCamera->moveRelative(Ogre::Vector3(-1,0,0));//yaw(Ogre::Degree(-1.25f));
    }else if (arg.key == OIS::KC_D || arg.key == OIS::KC_RIGHT)
    {
        setCamaraDerecha();

        //  Escena->mueveCamaraDerecha();
        // mCamera->moveRelative(Ogre::Vector3(1,0,0));
        // mCamera->pitch(Ogre::Degree(1.025f));
    }else if (arg.key == OIS::KC_C)
    {
        if (getModoCamara())
            setModoCamara(false);
        else
            setModoCamara(true);
        
    }else if (arg.key == OIS::KC_P)
    {
        // IMPLEMENTAR PAUSA
    }
    return true;
}

//void VistaAjedrez::rotar


bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 

    if (arg.key == OIS::KC_ESCAPE)// Pulsa Esc
    {

        vistaOgre->modeloVista->setNumPantalla(0);
        vistaOgre->modeloVista->reiniciar = true;

        //  modeloVista->setApagar(true);
    }

    BaseListeners::keyReleased(arg);
    noMueveCamara();
    return true;
}

#endif



#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
bool VistaAjedrez::touchPressed(const OIS::MultiTouchEvent& evt)
#else
bool VistaAjedrez::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id )
#endif
{  
    //COUTCOMENTADOstd::cout << "PROCESA MOUSE PULSADOOOOOOOOOOOOOOOOOOOOOO"<<std::endl;
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    BaseListeners::mousePressed(evt, id);
#else 
    BaseListeners::touchPressed(evt);
#endif

    int posx = evt.state.X.abs;   // Posicion del puntero
    int posy = evt.state.Y.abs;   //  en pixeles.


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho -------------
#endif

        //COUTCOMENTADOstd::cout << "pulsa1"<<std::endl;

        //ObjetoOgre* tableroOgre = tablero
        std::string nombreCasilla = encuentraCasillaSobrevolada(posx, posy);

        //COUTCOMENTADOstd::cout << "pulsa2: "<<  nombreCasilla <<std::endl;

        if (nombreCasilla!="")
        {
            vistaOgre->modeloVista->procesaNodoPulsado(nombreCasilla);
            //COUTCOMENTADOstd::cout << "pulsa3"<<std::endl;

            //HAY QUE ACTUALIZAR EL ESTADO DE LA VISTA DEL TABLERO
            //   tablero->getHijo(nombreCasilla);

            ObjetoOgre* casilla = static_cast<ObjetoOgre*>(objetoInicio->getHijo(nombreCasilla));


            //COUTCOMENTADOstd::cout << "pulsa4"<<std::endl;

            actualizaNodo();
        }
        //COUTCOMENTADOstd::cout << "pulsaend"<<std::endl;

        
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    }
    
    else if (id == OIS::MB_Middle)
    {
        setModoCamara(true);
    }
#endif

    //COUTCOMENTADOstd::cout << "FINNNNNNNNNNNN PROCESA MOUSE PULSADOOOOOOOOOOOOOOOOOOOOOO"<<std::endl;

    return true;
}

#ifdef USAROCKET

void VistaAjedrez::ProcessEvent(Rocket::Core::Event& event)
{
    // BaseListeners::ProcessEvent(event);


}
#endif

void VistaAjedrez::createView()
{

    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    // Escena = new Escena();
    //COUTCOMENTADOstd::cout << "vistaajedreeez "<<std::endl;
    //camera = mCamera;
    //modeloVista = modeloV;

    // modeloVista->escena = this;

    //Escena= modelov

    //modeloVista->escena = Escena;
    //escena

    //escenaMV = new EscenaAjedrez();


    //COUTCOMENTADOstd::cout << "generaJugadores "<<std::endl;

    vistaOgre->modeloVista->generaJugadores();
    //COUTCOMENTADOstd::cout << "inicia creaEscenaYModelo "<<std::endl;


    vistaOgre->modeloVista->creaEscenaYModelo();
    //COUTCOMENTADOstd::cout << "finnnnn creaEscenaYModelo "<<std::endl;
    Escena::createScene();


}

