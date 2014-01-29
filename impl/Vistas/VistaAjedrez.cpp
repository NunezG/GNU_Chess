
#include "../../headers/Vistas/VistaAjedrez.h"

//-------------------------------------------------------------------------------------
VistaAjedrez::VistaAjedrez(ModeloVista* modeloV, Ogre::RenderWindow* mWindow) : BaseVistas(modeloV, mWindow), Escena()
{  
    //  modelo =Modelo::getSingletonPtr();
    //  mWindow = mRoot->initialise(true, "Root Ajedrez");
    // Escena = Escena::getSingletonPtr();
    //  BaseVistas::iniciaOIS();

   // Escena = new Escena();
    				    std::cout << "vistaajedreeez "<<std::endl;

    
   // modeloVista->escena = this;
    
    //Escena= modelov
    
    //modeloVista->escena = Escena;
    //escena

						escenaMV = modeloV->escenaMV;

    createCamera();
    createViewports(mWindow);
	    				    std::cout << "generaJugadores "<<std::endl;

	modeloVista->generaJugadores();
	    				    std::cout << "inicia creaEscenaYModelo "<<std::endl;




    modeloVista->creaEscenaYModelo();
		    				    std::cout << "finnnnn creaEscenaYModelo "<<std::endl;

}

VistaAjedrez::~VistaAjedrez(void)
{    
}

void VistaAjedrez::actualizaNodo(ObjetoOgre* nodo)
{
//	std::cout << "actualizaNodo: "<< nodo->getNombre()<<std::endl;

	ObjetoEscena* objEsc;

	for (int i = 0; i<escenaMV->getTablero()->vectorHijos.size(); i++)
	{
		objEsc = escenaMV->getTablero()->getHijo(i);
		if (!tablero->getHijo(i)->sinHijos())
			tablero->getHijo(i)->getHijo(0)->cambiaMaterial(objEsc->getHijo(0)->materialName);


	}

	//ObjetoEscena* objEsc = escenaMV->getTablero()->getHijo(nodo->getNombre());

		//std::cout << "actualizaNodo222: "<< objEsc->getNombre()<<std::endl;

				//std::cout << "actualizaNodo333: "<< nodo->getHijo(0)->getNombre()<<std::endl;
								//std::cout << "actualizaNodomat: "<< nodo->getHijo(0)->materia<<std::endl;

		//std::cout << "actualizaNodo444: "<< objEsc->getHijo(0)->getNombre()<<std::endl;
			//	std::cout << "actualizaNodoMAT: "<< objEsc->getHijo(0)->materialName<<std::endl;


		



}


void VistaAjedrez::createScene()
{


			std::cout << "createScene VistaAjedrez "<<std::endl;
			BaseVistas::createScene();
						std::cout << "2222222 createScene VistaAjedrez"<<std::endl;

				Escena::createScene();

}


//-------------------------------------------------------------------------------------
bool VistaAjedrez::keyPressed(const OIS::KeyEvent &arg)
{    
    
   // BaseVistas::keyPressed(arg);
    
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
    //BaseVistas::keyReleased(arg);
    noMueveCamara();
    return true;
}

bool VistaAjedrez::mouseMoved( const OIS::MouseEvent &arg )
{  

    BaseVistas::mouseMoved(arg);
    
   // CEGUI::Vector2<float> mCursorPosition=sys->getDefaultGUIContext().getMouseCursor().getPosition();
//	sys->getDefaultGUIContext().getMouseCursor().get
   
    if (getModoCamara())   // yaw around the target, and pitch locally
    {
        rotacionCamara(Ogre::Degree(arg.state.X.rel/6));
    }
    else if (arg.state.Z.rel != 0)  // move the camera toward or away from the target
    {
        DistanciaCamara(arg.state.Z.rel);
    }
    else{

    //    const std::string casilla = encuentraCasillaSobrevolada(mCursorPosition);

     //   if (casilla != "")
      //  modeloVista->JugadorActivo->casillaSobrevolada(casilla);


    }

    return true;
}

//void VistaAjedrez::renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation))
//{
	//	std::cout << "renderQueueStarted EN VISTA AJEDREZ"<<std::endl;

    //if (!BaseVistas::renderQueueStarted(queueGroupId, invocation, true)) return false;
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
    //BaseVistas::mousePressed(arg, id);
    
//    CEGUI::Vector2<float> mCursorPosition=sys->getDefaultGUIContext().getMouseCursor().getPosition();
    int posx = arg.state.X.abs;   // Posicion del puntero
    int posy = arg.state.Y.abs;   //  en pixeles.
    if (id == OIS::MB_Left)
    {  // Boton izquierdo o derecho ------------- 
        if (modeloVista->jugadaElegida())
            modeloVista->aplicaCambio();

       else 
		   {
			   	std::cout << "pulsa1"<<std::endl;

				   //ObjetoOgre* tableroOgre = tablero
				   std::string nombreCasilla = encuentraCasillaSobrevolada(posx, posy);
				   			   	std::cout << "pulsa2: "<<  nombreCasilla <<std::endl;

				   modeloVista->procesaNodoPulsado(nombreCasilla);
			       			   	std::cout << "pulsa3"<<std::endl;

				   //HAY QUE ACTUALIZAR EL ESTADO DE LA VISTA DEL TABLERO
				//   tablero->getHijo(nombreCasilla);

								ObjetoOgre* casilla = tablero->getHijo(nombreCasilla);
											       			   	std::cout << "pulsa4"<<std::endl;

				   actualizaNodo(casilla);
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
   // BaseVistas::mouseReleased(arg, id);
    bool mbMiddle= (id == OIS::MB_Middle);
    
    if(mbMiddle) setModoCamara(false);
    
    return true;
}
