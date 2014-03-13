
#include "VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(RocketListener* vistaOgre) : EventListeners( vistaOgre), Escena(vistaOgre)
{  
    //  modelo =Modelo::getSingletonPtr();
    //  mWindow = mRoot->initialise(true, "Root Ajedrez");
    // Escena = Escena::getSingletonPtr();
    //  EventListeners::iniciaOIS();


}

VistaAjedrez::~VistaAjedrez(void)
{    
   
    mSceneMgr->destroyQuery(mRaySceneQuery);

}


void VistaAjedrez::actualizaNodo()
{



}




std::string VistaAjedrez::encuentraCasillaSobrevolada(int posx, int posy)
{
  
    Ogre::uint32 mask = CASILLA;

    Ogre::Ray rayMouse = vistaOgre->mCamera->getCameraToViewportRay
            (posx/float(vistaOgre->mWindow->getWidth()), posy/float(vistaOgre->mWindow->getHeight()));

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

    // Ogre::RaySceneQueryResult &result = executeRay(, , 'C');
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();

    if (it != result.end())
    {

        Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

        return nodoSobrevolado->getName();
    }

    return "";
}



#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)

bool VistaAjedrez::touchMoved(const OIS::MultiTouchEvent& evt)
{
 
    EventListeners::touchMoved(evt);
    return true;

}
/*
bool VistaAjedrez::touchPressed(const OIS::MultiTouchEvent& evt)
{
    EventListeners::touchPressed(evt);
    return true;

}
*/
bool VistaAjedrez::touchReleased(const OIS::MultiTouchEvent& evt)
{
    EventListeners::touchReleased(evt);
    return true;
}
bool VistaAjedrez::touchCancelled(const OIS::MultiTouchEvent& evt)
{

    EventListeners::touchCancelled(evt);
    return true;

}



#else

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{  

    EventListeners::mouseMoved(arg);
    
    if (getModoCamara())   // yaw around the target, and pitch locally
    {
        rotacionCamara(Ogre::Degree(arg.state.X.rel/6));
    }
    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        DistanciaCamara(arg.state.Z.rel);
    }
    else{

        const std::string casilla = encuentraCasillaSobrevolada(arg.state.X.abs, arg.state.Y.abs);

        if (casilla != "")
        {

            vistaOgre->modeloVista->JugadorActivo->casillaSobrevolada(casilla);
            actualizaNodo();
        }

    }

    return true;
}

bool VistaAjedrez::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{   
    EventListeners::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);
    
    if(mbMiddle) setModoCamara(false);
    
    return true;
}



//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed(const OIS::KeyEvent &arg)
{    
    
    EventListeners::keyPressed(arg);
    
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

    EventListeners::keyReleased(arg);
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
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    EventListeners::mousePressed(evt, id);
#else 
    EventListeners::touchPressed(evt);
#endif

    int posx = evt.state.X.abs;   // Posicion del puntero
    int posy = evt.state.Y.abs;   //  en pixeles.


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho -------------
#endif


        //ObjetoOgre* tableroOgre = tablero
        std::string nombreCasilla = encuentraCasillaSobrevolada(posx, posy);


        if (nombreCasilla!="")
        {
            vistaOgre->modeloVista->procesaNodoPulsado(nombreCasilla);

            //HAY QUE ACTUALIZAR EL ESTADO DE LA VISTA DEL TABLERO
            //   tablero->getHijo(nombreCasilla);

            ObjetoOgre* casilla = static_cast<ObjetoOgre*>(objetoInicio->getHijo(nombreCasilla));



            actualizaNodo();
        }
       
        
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    }
    
    else if (id == OIS::MB_Middle)
    {
        setModoCamara(true);
    }
#endif

 
    return true;
}

#ifdef USAROCKET

void VistaAjedrez::ProcessEvent(Rocket::Core::Event& event)
{
    // EventListeners::ProcessEvent(event);


}
#endif

void VistaAjedrez::createView()
{

    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

    // Escena = new Escena();
   
    //camera = mCamera;
    //modeloVista = modeloV;

    // modeloVista->escena = this;

    //Escena= modelov

    //modeloVista->escena = Escena;
    //escena

    //escenaMV = new EscenaAjedrez();

	
    vistaOgre->modeloVista->generaJugadores();
   
    vistaOgre->modeloVista->creaEscenaYModelo();
    
    Escena::createScene();


}

