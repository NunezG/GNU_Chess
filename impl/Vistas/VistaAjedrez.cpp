
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(RocketListener* vistaOgre) : BaseListeners( vistaOgre), Escena(vistaOgre)
{  
    //  modelo =Modelo::getSingletonPtr();
    //  mWindow = mRoot->initialise(true, "Root Ajedrez");
    // Escena = Escena::getSingletonPtr();
    //  BaseListeners::iniciaOIS();
	    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
		
   // Escena = new Escena();
    				    std::cout << "vistaajedreeez "<<std::endl;
												//camera = mCamera;
//modeloVista = modeloV;
    
   // modeloVista->escena = this;
    
    //Escena= modelov
    
    //modeloVista->escena = Escena;
    //escena

						//escenaMV = new EscenaAjedrez();

    
	    				    std::cout << "generaJugadores "<<std::endl;

	vistaOgre->modeloVista->generaJugadores();
	    				    std::cout << "inicia creaEscenaYModelo "<<std::endl;




    vistaOgre->modeloVista->creaEscenaYModelo();
		    				    std::cout << "finnnnn creaEscenaYModelo "<<std::endl;

}

VistaAjedrez::~VistaAjedrez(void)
{    
				std::cout << "del VistaAjedrez"<<std::endl;

	    mSceneMgr->destroyQuery(mRaySceneQuery);

}


void VistaAjedrez::actualizaNodo()
{



}


void VistaAjedrez::createScene()
{


			std::cout << "createScene VistaAjedrez "<<std::endl;
			//BaseListeners::createScene();
						std::cout << "2222222 createScene VistaAjedrez"<<std::endl;
				Escena::createScene();


}

std::string VistaAjedrez::encuentraCasillaSobrevolada(int posx, int posy)
{
										std::cout << "encuentraCasillaSobrevolada"<<std::endl;


    Ogre::uint32 mask = CASILLA;

    Ogre::Ray rayMouse = vistaOgre->mCamera->getCameraToViewportRay
            (posx/float(vistaOgre->mWindow->getWidth()), posy/float(vistaOgre->mWindow->getHeight()));


											std::cout << "encuentraCasillaSobrevolada 2222"<<std::endl;

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);
											std::cout << "encuentraCasillaSobrevolada33333"<<std::endl;

    Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

       // Ogre::RaySceneQueryResult &result = executeRay(, , 'C');
        Ogre::RaySceneQueryResult::iterator it;
        it = result.begin();

        if (it != result.end())
        {
						   	std::cout << "nodo encontrado"<<std::endl;


            Ogre::SceneNode* nodoSobrevolado = it->movable->getParentSceneNode();

            return nodoSobrevolado->getName();
        }
												std::cout << "encuentraCasillaSobrevolada fin"<<std::endl;

    return "";
}

//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed(const OIS::KeyEvent &arg)
{    
    
   // BaseListeners::keyPressed(arg);
    
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
    //BaseListeners::keyReleased(arg);
    noMueveCamara();
    return true;
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{  

    BaseListeners::mouseMoved(arg);
    
   // CEGUI::Vector2<float> mCursorPosition=sys->getDefaultGUIContext().getMouseCursor().getPosition();
//	sys->getDefaultGUIContext().getMouseCursor().get
   
							std::cout << "moviendo en ajedr"<<std::endl;

    if (getModoCamara())   // yaw around the target, and pitch locally
    {
        rotacionCamara(Ogre::Degree(arg.state.X.rel/6));
    }
    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        DistanciaCamara(arg.state.Z.rel);
    }
    else{

									std::cout << "busca a ver"<<std::endl;


        const std::string casilla = encuentraCasillaSobrevolada(arg.state.X.abs, arg.state.Y.abs);
											std::cout << "fin busca a ver"<<std::endl;


        if (casilla != "")
		{
												std::cout << "encuentra casilla sobrevvv"<<std::endl;

       vistaOgre->modeloVista->JugadorActivo->casillaSobrevolada(casilla);
	   actualizaNodo();
		}
				std::cout << "fincaca"<<std::endl;



    }

										std::cout << "acacacacacacadeeeeee"<<std::endl;


    return true;
}













//void VistaAjedrez::renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation))
//{
	//	std::cout << "renderQueueStarted EN VISTA AJEDREZ"<<std::endl;

    //if (!BaseListeners::renderQueueStarted(queueGroupId, invocation, true)) return false;
    //else
    //{
   /*     Tablero* tablero = getTablero();

        if(getCamaraIzquierda())
            tablero->rotacionCamara = Ogre::Degree(18 * evt.timeSinceLastFrame);

        else if (getCamaraDerecha())
            tablero->rotacionCamara = Ogre::Degree(18 * -evt.timeSinceLastFrame);

        if(tablero->rotacionCamara != Ogre::Degree(0))
        {
            Ogre::Degree rot = Ogre::Degree(Ogre::Real(80.0f) * evt.timeSinceLastFrame);

            //Rota la camara
            if (rot > tablero->rotacionCamara)
            {
                rotacionCamara(tablero->rotacionCamara);
                tablero->rotacionCamara = Ogre::Real(0.0f);
            }
            else
            {
                rotacionCamara(rot);
                tablero->rotacionCamara = tablero->rotacionCamara - rot;
            }
      }
	    */
    //}
    //return true;
//}

bool VistaAjedrez::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{  
    BaseListeners::mousePressed(arg, id);
    
//    CEGUI::Vector2<float> mCursorPosition=sys->getDefaultGUIContext().getMouseCursor().getPosition();
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho ------------- 
        if (vistaOgre->modeloVista->jugadaElegida()){
									   	std::cout << "jugadaElegidajugadaElegida"<<std::endl;

            vistaOgre->modeloVista->aplicaCambio();

		}

       else 
		   {
			   	std::cout << "pulsa1"<<std::endl;

				   //ObjetoOgre* tableroOgre = tablero
				   std::string nombreCasilla = encuentraCasillaSobrevolada(posx, posy);
				   			   	std::cout << "pulsa2: "<<  nombreCasilla <<std::endl;

				   vistaOgre->modeloVista->procesaNodoPulsado(nombreCasilla);
			       			   	std::cout << "pulsa3"<<std::endl;

				   //HAY QUE ACTUALIZAR EL ESTADO DE LA VISTA DEL TABLERO
				//   tablero->getHijo(nombreCasilla);

								ObjetoOgre* casilla = static_cast<ObjetoOgre*>(objetoInicio->getHijo(nombreCasilla));


											       			   	std::cout << "pulsa4"<<std::endl;

				   actualizaNodo();
				   			   	std::cout << "pulsaend"<<std::endl;

		}
	}
    
    else if (id == OIS::MB_Middle)
    {
        setModoCamara(true);
    }
    return true;
}

bool VistaAjedrez::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{   
    BaseListeners::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);
    
    if(mbMiddle) setModoCamara(false);
    
    return true;
}



	void VistaAjedrez::ProcessEvent(Rocket::Core::Event& event)
	{
		//BaseListeners::ProcessEvent(event);


	}



	
					void VistaAjedrez::createOverlay()
					{







					}
