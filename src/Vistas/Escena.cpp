#include "Escena.h"

Escena::Escena(RocketListener* vistaO) :

    // , mTopSpeed(150)
    // ,   mRaySceneQuery(0)
    //, mOrbiting(false)
    modoCamara(false)
  , camaraDerecha(false)
  , camaraIzquierda(false)
  // , columnas("ABCDEFGH")
  // , ventanaEmergente(0)
  , modoVS(0)
{

    rocketL= vistaO;
    //objEscena= vistaO->modeloVista->escenaMV->getTablero();
    //vistaOgre = vistaO;

}

Escena::~Escena(void)
{
    delete objetoInicio;
    objetoInicio = NULL;
}
/*
Tablero* Escena::getTablero()
{
    return tablero;
}
*/



void Escena::createScene()
{
    //COUTCOMENTADOstd::cout << "createScene dentroo "<<std::endl;

    sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MANAGER");


    //COUTCOMENTADOstd::cout << "GENERA ESCENA: "<< 	sceneMgr->getName()<<std::endl;

    ////COUTCOMENTADOstd::cout << "creaT 2"<< tablero->getNombre() <<std::endl;


    //AQUI LLAMA A MODELOVISTA Y HAQ QUE QUITAR MSCENEMGR
    generaEscena();
    //COUTCOMENTADOstd::cout << "crea LUCES DE LA ESCENA "<<std::endl;

    sceneMgr->setAmbientLight(Ogre::ColourValue(0.95, 0.95, 0.95));

    //CREA LA ILUMINACIÓN
    //  sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    // sceneMgr->setShadowColour(Ogre::ColourValue(0.5,0.5, 0.5) );
    //sceneMgr->setShadowTextureFadeStart(0.1);
    //	    sceneMgr->setShadowTextureFadeEnd(0.6);
    //sceneMgr->setShadowTextureSelfShadow(true);

    //  sceneMgr->setShadowTextureCount(2);
    // sceneMgr->setShadowTextureSize(1024);

    Ogre::Light* light = sceneMgr->createLight("Light1");
    //light->setPosition(20,80,50);
    light->setPosition(80,100, 0);
    light->setType(Ogre::Light::LT_POINT);
    light->setDirection(Ogre::Vector3(0,0,0));
    //light->set
    //light->setAttenuation(3250,1.0,0.27,0.028);
    //light->setCastShadows(false);

    /*
     Ogre::Light* light2 = sceneMgr->createLight("Light2");
    light2->setPosition(-80,100,0);
    //  light2->setDiffuseColour(0.1,0.1,0.1);
    light2->setType(Ogre::Light::LT_POINT);
    light2->setDirection(Ogre::Vector3(0,0,0));
    //  light2->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    //light2->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    //light2->setSpotlightFalloff(1.0f);
  //  light2->setCastShadows(false);

    */

    // light2->setDiffuseColour(0.1,0.1,0.1);
    // light->setSpotlightInnerAngle(Ogre::Degree(30.0f));
    // light->setSpotlightOuterAngle(Ogre::Degree(60.0f));
    // light->setSpotlightFalloff(1.0f);


    //Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();


}



void Escena::generaEscena()
{


    //COUTCOMENTADOstd::cout << "INCIA ESCNAAJEDREZ "<<std::endl;
    std::vector<std::string> mat;
    mat.push_back("MaterialTablero");


    //OBJETO INICIAL
    //objetoInicio = new ObjetoOgre();
    //COUTCOMENTADOstd::cout << "ccucucu EN ESCENA (VISTA)"<<std::endl;

    objetoInicio = new ObjetoOgre("Tablero", TABLERO, "Tablero" ,  mat  ,sceneMgr);

    //COUTCOMENTADOstd::cout << "creaCasillgghkjglgljglgTA)"<<std::endl;


    sceneMgr->getRootSceneNode()->addChild(objetoInicio->getNodoOgre());
    //COUTCOMENTADOstd::cout << "creaCasiggkgjgkhf11STA)"<<std::endl;


    rocketL->modeloVista->escenaMV->getTablero()->objetoPadre = objetoInicio;
    //COUTCOMENTADOstd::cout << "cre333333333333333333333333STA)"<<std::endl;

    rocketL->modeloVista->escenaMV->getTablero()->creaCasillas();
    //COUTCOMENTADOstd::cout << "cre55555555555555555555555TA)"<<std::endl;


    rocketL->modeloVista->escenaMV->getTablero()->creaPiezas();
    //	listener

    //COUTCOMENTADOstd::cout << "creaCa566666666666666666666666666666ISTA)"<<std::endl;



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
