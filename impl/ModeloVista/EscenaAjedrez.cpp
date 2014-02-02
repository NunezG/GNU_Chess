#include "../../headers/ModeloVista/EscenaAjedrez.h"

EscenaAjedrez::EscenaAjedrez() :
	    rotaCamara(0)
   // ,mCamera(0)
  //, tablero(0)
 // , mTarget(0)
 // , mTopSpeed(150)
 // ,   mRaySceneQuery(0)
  //, mOrbiting(false)
  ,modoCamara(false)
  , camaraDerecha(false)
  , camaraIzquierda(false)
 // , columnas("ABCDEFGH")
 // , ventanaEmergente(0)
  , modoVS(0)
 // , listaNodos(0)
{
		std::cout << "INCIA ESCNAAJEDREZ "<<std::endl;

   			 tablero = new TableroMV();



}

EscenaAjedrez::~EscenaAjedrez(void)
{
    delete tablero;
    tablero = NULL;
}

TableroMV* EscenaAjedrez::getTablero()
{
    return tablero;
}
void EscenaAjedrez::createSceneMV()
{
						    std::cout << "creaTableroYCasillas en escenaajedrez"<<std::endl;
						   // std::cout << "creaT 11"<< 	mSceneMgr->getName()<<std::endl;

							//std::cout << "creaT 2"<< tablero->getNombre() <<std::endl;


   // tablero->creaTableroYCasillas(mSceneMgr);
						    std::cout << "creaTableroYCasillas "<<std::endl;



}







bool EscenaAjedrez::getCamaraIzquierda()
{
    return camaraIzquierda;
}

bool EscenaAjedrez::getCamaraDerecha(){
    return camaraDerecha;
}

void EscenaAjedrez::setCamaraIzquierda()
{
    camaraIzquierda = true;
}

void EscenaAjedrez::setCamaraDerecha()
{
    camaraDerecha = true;
}

void EscenaAjedrez::noMueveCamara()
{
    camaraIzquierda = false;
    camaraDerecha = false;
}

void EscenaAjedrez::setModoCamara(bool modo)
{
    modoCamara = modo;
}

bool EscenaAjedrez::getModoCamara()
{
   return modoCamara;
}


void EscenaAjedrez::muestraVentanaEmergente(std::string nombreLayout)
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


void EscenaAjedrez::apagaVentanaEmergente()
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
