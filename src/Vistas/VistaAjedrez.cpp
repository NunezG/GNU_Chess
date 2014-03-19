
#include "VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(OgreFramework* fw) : RocketEventListener( fw), Escena(fw->modeloVista->escenaMV)
{  
    //  modelo =Modelo::getSingletonPtr();
    //  mWindow = mRoot->initialise(true, "Root Ajedrez");
    // Escena = Escena::getSingletonPtr();
    //  RocketEventListener::iniciaOIS();

		  	  Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");


}

VistaAjedrez::~VistaAjedrez(void)
{    
   
	
    //sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MANAGER");


    framework->mSceneMgr->destroyQuery(mRaySceneQuery);

    framework->modeloVista->borraJugadores();
   
			//delete objetoInicio;

  
}


void VistaAjedrez::actualizaNodo()
{



}




std::string VistaAjedrez::encuentraCasillaSobrevolada()
{
    Ogre::Real posx, posy;
    framework->mInputContext.getCursorPosition(posx,posy);

    Ogre::uint32 mask = CASILLA;

    Ogre::Ray rayMouse = framework->mCamera->getCameraToViewportRay
            (posx/float(framework->mWindow->getWidth()), posy/float(framework->mWindow->getHeight()));

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
 
    RocketEventListener::touchMoved(evt);
    return true;

}
/*
bool VistaAjedrez::touchPressed(const OIS::MultiTouchEvent& evt)
{
    RocketEventListener::touchPressed(evt);
    return true;

}
*/
bool VistaAjedrez::touchReleased(const OIS::MultiTouchEvent& evt)
{

    RocketEventListener::touchReleased(evt);
    return true;
}
bool VistaAjedrez::touchCancelled(const OIS::MultiTouchEvent& evt)
{

    RocketEventListener::touchCancelled(evt);
    return true;

}



#else

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{  
	//Ogre::Root::getSingleton().getSceneManager()
    RocketEventListener::mouseMoved(arg);
    
    if (getModoCamara())   // yaw around the target, and pitch locally
    {
        framework->rotacionCamara(Ogre::Degree(arg.state.X.rel/6));
    }
    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        framework->DistanciaCamara(arg.state.Z.rel);
    }
    else{
        const std::string casilla = encuentraCasillaSobrevolada();

        if (casilla != "")
        {

            modeloVista->JugadorActivo->casillaSobrevolada(casilla);
            actualizaNodo();
        }

    }

    return true;
}

bool VistaAjedrez::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{   
    RocketEventListener::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);
    
    if(mbMiddle) setModoCamara(false);
    
    return true;
}



//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed(const OIS::KeyEvent &arg)
{    

    RocketEventListener::keyPressed(arg);
    
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


#endif

bool VistaAjedrez::keyReleased( const OIS::KeyEvent &arg )
{ 

    if (arg.key == OIS::KC_ESCAPE)// Pulsa Esc
    {

        modeloVista->setNumPantalla(0);
       // modeloVista->reiniciar = true;

        //  modeloVista->setApagar(true);
    }

    RocketEventListener::keyReleased(arg);
    noMueveCamara();
    return true;
}




#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
bool VistaAjedrez::touchPressed(const OIS::MultiTouchEvent& evt)
#else
bool VistaAjedrez::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id )
#endif
{  
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    RocketEventListener::mousePressed(evt, id);
#else 
    RocketEventListener::touchPressed(evt);
#endif



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho -------------
#endif


        //ObjetoOgre* tableroOgre = tablero
        std::string nombreCasilla = encuentraCasillaSobrevolada();


        if (nombreCasilla!="")
        {
            framework->modeloVista->procesaNodoPulsado(nombreCasilla);

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


void VistaAjedrez::ProcessEvent(Rocket::Core::Event& event)
{
    // RocketEventListener::ProcessEvent(event);


}


void VistaAjedrez::createView()
{

    mRaySceneQuery = framework->mSceneMgr->createRayQuery(Ogre::Ray());

    // Escena = new Escena();
   
    //camera = mCamera;
    //modeloVista = modeloV;

    // modeloVista->escena = this;

    //Escena= modelov

    //modeloVista->escena = Escena;
    //escena

    //escenaMV = new EscenaAjedrez();

    framework->modeloVista->generaJugadores();
   
    //framework->modeloVista->creaEscenaYModelo();
    
    Escena::createScene();

}

