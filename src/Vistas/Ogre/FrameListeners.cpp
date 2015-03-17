#include "FrameListeners.h"

FrameListeners::FrameListeners(OgreFramework* fw) :
	  vistaActiva(0)

    //mInputManager(0),
    //mMouse(0),
    //mKeyboard(0)
    //, sys(0)
    //, mRoot(0)
   

{  

    modeloVista = fw->modeloVista;

	framework  =fw;
    //esto cambialo para meter el mRoot primero con ANDROID
    //init();


	    fw->mRoot->addFrameListener(this);

	 //   running = true;

}




FrameListeners::~FrameListeners()
{

    // delete mWindow;
    // mWindow = 0;
}

bool FrameListeners::frameStarted(const Ogre::FrameEvent& evt)
{


    return	Ogre::FrameListener::frameStarted(evt) && vistaActiva->running;
}




bool FrameListeners::frameRenderingQueued(const Ogre::FrameEvent& evt)
{



    if(modeloVista->getApagar() || framework->mWindow->isClosed() || !framework->mWindow->isVisible() || framework->mWindow->isHidden()){
                   std::cout << "SALE DE FRAMERENDEREINQUEUE  "<<modeloVista->getApagar()  <<  framework->mWindow->isClosed() <<  !framework->mWindow->isVisible() <<  framework->mWindow->isHidden() <<  std::endl;

        return false;

    }


	//el thread se comprueba aqui
	//std::thread t1(lanzaArbol, 1);
	
	//if ()
//	t1.join();

	//Modelo::


    //Ogre::Entity* ent = mSceneMgr->getEntity("Casilla");
    // ent->getMesh()->reload();


    //	Ogre::TextureManager::getSingleton().reloadAll();
    //Ogre::ResourceManager::reloadAll();


    //  mInputContext.capture();

    //poner esto en otro sitio

    if( modeloVista->escenaMV->getCamaraIzquierda())
        modeloVista->escenaMV->rotaCamara = (18 * evt.timeSinceLastFrame);


    else if ( modeloVista->escenaMV->getCamaraDerecha())
        modeloVista->escenaMV->rotaCamara = (18 * -evt.timeSinceLastFrame);


    if(modeloVista->escenaMV->rotaCamara != 0)
    {

        float fRot = Ogre::Real(80.0f) * evt.timeSinceLastFrame;
        if (modeloVista->escenaMV->rotaCamara < 0) fRot = -fRot;

        Ogre::Degree rot = Ogre::Degree(fRot);

        Ogre::Degree rotRestante = Ogre::Degree(modeloVista->escenaMV->rotaCamara);
        //Rota la camara


        if ((fRot > 0 && rot > rotRestante) ||(fRot < 0 && rot < rotRestante))
        {


            framework->rotacionCamara( rotRestante);
            modeloVista->escenaMV->rotaCamara = Ogre::Real(0.0f);
        }
        else
        {

            framework->rotacionCamara(rot);
            modeloVista->escenaMV->rotaCamara = modeloVista->escenaMV->rotaCamara - fRot;
        }

	}

		framework->mInputContext.capture();      // capture input
	





   // if (modeloVista->jugadaElegida())
	//{
        //ESTO EN UN FUTURO HABRA QUE HACERLO EN OTRO THREAD
		//std::cout << "INICIA APLICA CAMBIO" << std::endl;
		


        modeloVista->compruebaCambio();
		//std::cout << "ACABA APLICA CAMBIO" << std::endl;


   // }





    return true;
}



void FrameListeners::borraVistaActiva()
{


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    if(framework->mInputContext.mKeyboard)
    framework->mInputContext.mKeyboard->setEventCallback(0);
if(framework->mInputContext.mMouse)
    framework->mInputContext.mMouse->setEventCallback(0);

#endif


#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
// if(framework->mInputContext.mMultiTouch)
  //  {
	//	framework->mInputContext.mMultiTouch->setEventCallback(0);
// }
	//if (vistaOgre->mInputContext.mAccelerometer) vistaOgre->mInputContext.mAccelerometer->setEventCallback(0);
#endif



 delete vistaActiva;


}



void FrameListeners::setVistaActiva(RocketEventListener* vista)
{


	vistaActiva = vista;

	modeloVista = vista->modeloVista;
	  

	
    //LISTENERS
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
    framework->mInputContext.mMouse->setEventCallback(vista);
	
    framework->mInputContext.mKeyboard->setEventCallback(vista);
#else


		//framework->mInputContext.mMultiTouch->setEventCallback(vista);


#endif 




}

