#include "../../headers/Vistas/BaseListeners.h"

BaseListeners::BaseListeners( RocketListener* vistaO) :
    //mInputManager(0),
    //mMouse(0),
    //mKeyboard(0)
  //, sys(0)
  //, mRoot(0)
  //  mCamera(0)
  //, tablero(0)
   mTarget(0)
  ,mSceneMgr(0)
  
{  

	vistaOgre = vistaO;

	//modeloVista = 

					    std::cout << "base 1"<<std::endl;

						//vistaOgre->mWindow;
					    std::cout << "base2 "<<std::endl;

		context = Rocket::Core::GetContext("main");
						    std::cout << "base 3"<<std::endl;

		mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MANAGER");

				    std::cout << "base4 "<<std::endl;

    
	


	context->AddEventListener("click", this); 



}

BaseListeners::~BaseListeners()
{
			std::cout << "del BaseListeners"<<std::endl;
	
    context->RemoveEventListener("click", this);
				std::cout << "del BaseListeners222"<<std::endl;
				context->UnloadAllDocuments();

	  vistaOgre->mMouse->setEventCallback(0);
      vistaOgre->mKeyboard->setEventCallback(0);
				std::cout << "findel BaseListeners"<<std::endl;


    // delete mWindow;
    // mWindow = 0;
}

//void BaseListeners::createFrameListener()
//{
	// Create the RocketFrameListener.
	//mFrameListener = new RocketListener();

	//mRoot->addFrameListener(this);

	// Show the frame stats overlay.
	//mFrameListener->showDebugOverlay(true);
//}

//int BaseListeners::getFPS()
//{
//    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
//    return ((int)stats.lastFPS);
//}



bool BaseListeners::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{

		context->ProcessMouseButtonDown((int) id, 0);
		//context->Proc
   // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    //context.injectMouseButtonDown(CEGUI::MouseButton(id));
    //  sys->injectMouseButtonDown(convertButton(id));
    return true;
}

bool BaseListeners::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
		context->ProcessMouseButtonUp((int) id, 0);

    //CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    //CEGUI::MouseButton(buttonID);

   // context.injectMouseButtonUp(CEGUI::MouseButton(id));
    // sys->injectMouseButtonUp(convertButton(id));
    return true;
}

bool BaseListeners::keyPressed( const OIS::KeyEvent &evt )
{
   // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

   // context.injectKeyDown(CEGUI::Key::Scan(evt.key));
   // context.injectChar(evt.text);

    if (evt.key == OIS::KC_ESCAPE)// Pulsa Esc
    {
        vistaOgre->mWindow->setHidden(true);
      //  modeloVista->setApagar(true);
    }
    else if (evt.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        // mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }


		Rocket::Core::Input::KeyIdentifier key_identifier = key_identifiers[evt.key];

	

		context->ProcessKeyDown(key_identifier, 0);

	


    return true;
}

bool BaseListeners::keyReleased( const OIS::KeyEvent &e )
{
	Rocket::Core::Input::KeyIdentifier key_identifier = key_identifiers[e.key];

	if (key_identifier != Rocket::Core::Input::KI_UNKNOWN)
		context->ProcessKeyUp(key_identifier, 0);

	if (e.key == OIS::KC_ESCAPE)
		running = false;

   // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

      //  context.injectKeyUp(CEGUI::Key::Scan(arg.key));
        return true;
}

bool BaseListeners::mouseMoved( const OIS::MouseEvent &e )
{
					std::cout << "mouseMoved"<<std::endl;

	//int key_modifier_state = GetKeyModifierState();

						                 // std::cout << key_modifier_state<<std::endl;
												
	context->ProcessMouseMove(e.state.X.abs, e.state.Y.abs, 0);
	if (e.state.Z.rel != 0)
		context->ProcessMouseWheel(e.state.Z.rel / -120, 0);


						std::cout << "fin mouseMoved base"<<std::endl;

	//VistaAjedrez::mouseMoved(e);
   // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    // context.injectMouseMove(evt.state.X.rel, evt.state.Y.rel) ;
        return true;

}





//Adjust mouse clipping area
void BaseListeners::windowResized()
{
    unsigned int width, height, depth;
    int left, top;
    vistaOgre->mWindow->getMetrics(width, height, depth, left, top);
    
    const OIS::MouseState &ms = vistaOgre->mMouse->getMouseState();
    
    ms.width = width;
    ms.height = height;
}
/*
Ogre::Ray BaseListeners ::getCameraToViewportRay()
{

	return mCamera->getCameraToViewportRay
            (posx/float(mWindow->getWidth()), posy/float(mWindow->getHeight()));

}

*/


void BaseListeners::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (vistaOgre->mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
    vistaOgre->mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}



void BaseListeners::rotacionCamara(Ogre::Degree angulo)
{
    Ogre::Real dist = (vistaOgre->mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

    //Mueve la camara a la posicion central
    vistaOgre->mCamera->setPosition(mTarget->_getDerivedPosition());
    //Rota la camara
    vistaOgre->mCamera->yaw(-angulo);

    //Devuelve la camara a su posicion original
    vistaOgre->mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}










