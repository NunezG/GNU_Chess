#include "../../headers/Vistas/Escena.h"

Escena::Escena() :
    mCamera(0)
  //, tablero(0)
  , mTarget(0)
 // , mTopSpeed(150)
 // ,   mRaySceneQuery(0)
  //, mOrbiting(false)
  ,modoCamara(false)
  , camaraDerecha(false)
  , camaraIzquierda(false)
 // , columnas("ABCDEFGH")
 // , ventanaEmergente(0)
  , modoVS(0)
{
		std::cout << "INCIA ESCNAAJEDREZ "<<std::endl;

    tablero = new ObjetoOgre("Tablero");
    mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MANAGER");
    mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());

}

Escena::~Escena(void)
{
    mSceneMgr->destroyQuery(mRaySceneQuery);
    delete tablero;
    tablero = NULL;
}
/*
Tablero* Escena::getTablero()
{
    return tablero;
}
*/
void Escena::createScene()
{
						    std::cout << "creaTableroYCasillas dentroo "<<std::endl;
														std::cout << "creaT 11: "<< 	mSceneMgr->getName()<<std::endl;

							//std::cout << "creaT 2"<< tablero->getNombre() <<std::endl;

						
//AQUI LLAMA A MODELOVISTA Y HAQ QUE QUITAR MSCENEMGR
    creaTableroYCasillas(mSceneMgr);
						    std::cout << "creaTableroYCasillas "<<std::endl;


//CREA LA ILUMINACIÓN
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setShadowColour(Ogre::ColourValue(0.75, 0.75, 0.75) );
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.55, 0.55, 0.55));

    mSceneMgr->setShadowTextureCount(2);
    mSceneMgr->setShadowTextureSize(1024);

    Ogre::Light* light2 = mSceneMgr->createLight("Light2");
    light2->setPosition(70,500,70);
    //  light2->setDiffuseColour(0.1,0.1,0.1);
    light2->setType(Ogre::Light::LT_POINT);
    light2->setDirection(Ogre::Vector3(0,0,0));
    //  light2->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    //light2->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    //light2->setSpotlightFalloff(1.0f);
    light2->setCastShadows(true);

    Ogre::Light* light = mSceneMgr->createLight("Light1");
    light->setPosition(-70,500,-70);
    light->setType(Ogre::Light::LT_POINT);
    light->setDirection(Ogre::Vector3(0,0,0));
    // light2->setDiffuseColour(0.1,0.1,0.1);
    // light->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    // light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    // light->setSpotlightFalloff(1.0f);
    light->setCastShadows(true);
}

void Escena::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
    mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}




void Escena::creaTableroYCasillas(Ogre::SceneManager* sceneMgr)
{

								    std::cout << "creaTableroYCasillas1 "<<std::endl;


	objEscena= escenaMV->getTablero();

							    std::cout << "creaTableroYCasillasqqqqqq "<<std::endl;

    mSceneMgr = sceneMgr;

						    std::cout << "creaModelo3D "<<std::endl;

  //  nodoTablero = new ObjetoOgre("Tablero");
		tablero->creaModelo3D(mSceneMgr, "Tablero", TABLERO);
						    std::cout << "creaModelo3D 222222222222222222"<<std::endl;

    
							    std::cout << "creaCasillas"<<std::endl;
mSceneMgr->getRootSceneNode()->addChild(tablero->getNodoOgre());
  //  creaCasillas();
	generaEscena(objEscena, tablero );
    //creaVasallos();
   // creaNobleza();
   // creaPeones();
}


void Escena::generaEscena(ObjetoEscena* nodoEscena, ObjetoOgre* nodoOgre)
{
	Ogre::uint32 mask;
	
	
		//RECORRE HIJOS DEL TABLERO QUE SON LAS CASILLAS
	ObjetoEscena* tempObj;
	
		mask = nodoEscena->mask;
		
		ObjetoOgre* objeto;
	
	for (int i = 0; i<nodoEscena->vectorHijos.size(); i++)
	{

		//AQUI SE CREA EL OBJETO OGRE
	tempObj= nodoEscena->getHijo(i);
							    std::cout << "genera esto: "<< tempObj->nombreMalla  <<std::endl;

		objeto = new ObjetoOgre(tempObj->getNombre());
	 objeto->creaModelo3D(mSceneMgr, tempObj->nombreMalla, tempObj->mask);
	 objeto->cambiaMaterial(tempObj->materialName);
	
	 if (tempObj->rotate > 0) objeto->rota(tempObj->rotate);
	     objeto->trasladar(tempObj->yRel,tempObj->xRel);
	
		 //a la lista de casillas
		 nodoOgre->agregaHijo(objeto);
	
		//tempObj = nodoEscena->getHijo(i);
	
		if(!tempObj->sinHijos())
		{
			generaEscena(tempObj, objeto);
		}

	//	tempObj
	//generaEscena
	}
}
/*
void Escena::creaPiezas()
{
	std::string posInicial = "bcdefdcbaaaaaaaa00000000000000000000000000000000zzzzzzzzyxwvuwxy";
	 std::string nombreObjeto;
    //Ogre::String posCasilla;
    int posCasilla;

	//std::string meshName;
	// Ogre::uint32 mask;
   // Ficha* objeto;
	//ObjetoOgre* objeto;

	for(std::string::iterator it = posInicial.begin(); it != posInicial.end(); ++it) 
	{
  
			 nombreObjeto = "";

			
	switch (*it)
	{	
	case 'a':
		nombreObjeto.append("(P)Peon_");       
		//new ¿Peon?
		//mask = BLANCAS;
		//meshName = "Peon";
	  //  materialName = "MaterialFichaBlanca";
	break;
	case 'b':
        nombreObjeto.append("(T)Torre");       
		//mask = BLANCAS;
		//meshName = "Torre";
	  //  materialName = "MaterialFichaBlanca";
  
  
	break;
	case 'c':
		  nombreObjeto.append("(T)Alfil");       
		//mask = BLANCAS;
		//meshName = "Alfil";
	   // materialName = "MaterialFichaBlanca";
	break;
	case 'd':
		  nombreObjeto.append("(C)Caballo");       
		//mask = BLANCAS;
		//meshName = "Caballo";
	    //materialName = "MaterialFichaBlanca";
	break;
	case 'e':
		  nombreObjeto.append("(R)Rey");       
		//mask = BLANCAS;
		//meshName = "Rey";
	    //materialName = "MaterialFichaBlanca";
	break;
	case 'f':
		  nombreObjeto.append("(D)Reina");       
		//mask = BLANCAS;
		//meshName = "Reina";
	    //materialName = "MaterialFichaBlanca";
	break;
	case 'z':
		 nombreObjeto.append("(P)Peon_");       
		//new ¿Peon?
		//mask = NEGRAS;
		//meshName = "Peon";
	    //materialName = "MaterialFichaNegra";
	break;
	case 'y':
		 nombreObjeto.append("(T)Torre");       
		//mask = NEGRAS;
		//meshName = "Torre";
	    //materialName = "MaterialFichaNegra";
	break;
	case 'x':
		  nombreObjeto.append("(T)Alfil");       
		//mask = NEGRAS;
		//meshName = "Torre";
	    //materialName = "MaterialFichaNegra";
	break;
	case 'w':
		 nombreObjeto.append("(C)Caballo");       
		//mask = NEGRAS;
		//meshName = "Caballo";
	    //materialName = "MaterialFichaNegra";
	break;
	case 'v':
		 nombreObjeto.append("(R)Rey");       
		//mask = NEGRAS;
		//meshName = "Rey";
	    //materialName = "MaterialFichaNegra";
	break;
	case 'u':
		 nombreObjeto.append("(D)Reina");       
		//mask = NEGRAS;
		//meshName = "Reina";
	    //materialName = "MaterialFichaNegra";
	break;
	}
	nombreObjeto.append(Ogre::StringConverter::toString(*it));       
	 

	//do_things_with(*it);
	}
	

}
*/
void Escena::rotacionCamara(Ogre::Degree angulo)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    //Mueve la camara a la posicion central
    mCamera->setPosition(mTarget->_getDerivedPosition());
    //Rota la camara
    mCamera->yaw(-angulo);

    //Devuelve la camara a su posicion original
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}

void Escena::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(-40,-40,150));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);


    if (mCamera->getSceneManager()->getRootSceneNode() != mTarget)
    {
        mTarget = mCamera->getSceneManager()->getRootSceneNode();
        if(mTarget)
        {
            mCamera->setPosition(mTarget->_getDerivedPosition());
            mCamera->setOrientation(mTarget->_getDerivedOrientation());
            mCamera->yaw(Ogre::Degree(90));
            mCamera->pitch(-Ogre::Degree(50));
            mCamera->moveRelative(Ogre::Vector3(0, 0, 110));
            mCamera->setAutoTracking(true, mTarget);
        }
        else
        {
            mCamera->setAutoTracking(false);
        }
    }

    mCamera->setFixedYawAxis(true);

    // mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    //  mTopSpeed = topSpeed;

   // return mCamera;
}

void Escena::createViewports(Ogre::RenderWindow* window)
{
    mWindow = window;
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}


bool Escena::getCamaraIzquierda()
{
    return camaraIzquierda;
}

bool Escena::getCamaraDerecha(){
    return camaraDerecha;
}

void Escena::setCamaraIzquierda()
{
    camaraIzquierda = true;
}

void Escena::setCamaraDerecha()
{
    camaraDerecha = true;
}

void Escena::noMueveCamara()
{
    camaraIzquierda = false;
    camaraDerecha = false;
}

void Escena::setModoCamara(bool modo)
{
    modoCamara = modo;
}

bool Escena::getModoCamara()
{
   return modoCamara;
}

std::string Escena::encuentraCasillaSobrevolada(int posx, int posy)
{


    Ogre::uint32 mask = CASILLA;

    Ogre::Ray rayMouse = mCamera->getCameraToViewportRay
            (posx/float(mWindow->getWidth()), posy/float(mWindow->getHeight()));

    mRaySceneQuery->setRay(rayMouse);
    mRaySceneQuery->setSortByDistance(true);
    mRaySceneQuery->setQueryMask(mask);

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
		
    return "";
}

void Escena::muestraVentanaEmergente(std::string nombreLayout)
{
    //CEGUI::WindowManager::getSingleton().isAlive(nombreLayout);
/*
    if (!CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->isChild(nombreLayout))
    {
        ventanaEmergente = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(nombreLayout+"CEED.layout");
		ventanaEmergente->setMouseCursor("Vanilla-Images/MouseArrow");

		if (nombreLayout == "JaqueMate") 	
			ventanaEmergente->getChild("VentanaJM")->getChild("VarGanador")->setText(nombreActivo);

        //  newWindow->setSize( CEGUI::UVCEGUI2( CEGUI::UCEGUI1.0f, 0 ), CEGUI::UDim( 1.0f, 0 ) ) );

    //	CEGUI::GUIContext::

        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(ventanaEmergente);
    }else
    {
        ventanaEmergente = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild(nombreLayout);
        ventanaEmergente->setVisible(true);
    }
	*/
}

void Escena::apagaVentanaEmergente()
{
  /*  //CEGUI::System::getSingleton().getGUISheet()->cleanupChildren();
     if (ventanaEmergente != NULL && ventanaEmergente->isVisible())
     {
         ventanaEmergente->setVisible(false);
         CEGUI::WindowManager::getSingleton().destroyWindow(ventanaEmergente);
         ventanaEmergente = NULL;
     }
	 */
}
