#include "BaseListeners.h"

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

    vistaOgre->mInputContext.mMouse->setEventCallback(0);
    vistaOgre->mInputContext.mKeyboard->setEventCallback(0);
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


#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)

bool BaseListeners::touchMoved(const OIS::MultiTouchEvent& evt)
{
    std::cout << "HA DETECTADO MOVIMIENTO!! "<<std::endl;

}
bool BaseListeners::touchPressed(const OIS::MultiTouchEvent& evt)
{

    std::cout << "HA DETECTADO UNA PULSACION!! "<<std::endl;

    return true;

}
bool BaseListeners::touchReleased(const OIS::MultiTouchEvent& evt)
{
    std::cout << "HA DETECTADO UNA PULSACION SOLTADA!! "<<std::endl;

    return true;
}
bool BaseListeners::touchCancelled(const OIS::MultiTouchEvent& evt)
{
    return true;

}
#else



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


bool BaseListeners::mouseMoved( const OIS::MouseEvent &e )
{
    //std::cout << "mouseMoved"<<std::endl;

    //int key_modifier_state = GetKeyModifierState();

    // std::cout << key_modifier_state<<std::endl;
    //mInputContext.
    context->ProcessMouseMove(e.state.X.abs, e.state.Y.abs, 0);
    if (e.state.Z.rel != 0)
        context->ProcessMouseWheel(e.state.Z.rel / -120, 0);


    //	std::cout << "fin mouseMoved base"<<std::endl;

    //VistaAjedrez::mouseMoved(e);
    // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    // context.injectMouseMove(evt.state.X.rel, evt.state.Y.rel) ;
    return true;

}

#endif



bool BaseListeners::keyPressed( const OIS::KeyEvent &evt )
{



    Rocket::Core::Input::KeyIdentifier key_identifier = key_identifiers[evt.key];



    context->ProcessKeyDown(key_identifier, 0);




    return true;
}

bool BaseListeners::keyReleased( const OIS::KeyEvent &e )
{
    Rocket::Core::Input::KeyIdentifier key_identifier = key_identifiers[e.key];

    if (key_identifier != Rocket::Core::Input::KI_UNKNOWN)
        context->ProcessKeyUp(key_identifier, 0);



    //if (e.key == OIS::KC_ESCAPE)
    //	running = false;


    return true;
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

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID



Rocket::Core::ElementDocument* BaseListeners::openFontRocket(const Ogre::String& fileName)
{

    /*
          //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, (Rocket::Core::String("Rocket::Core::FileHandle Open: ") + path).CString());
        AAsset* asset = AAssetManager_open(mAssetMgr, path.CString(), AASSET_MODE_BUFFER);
       AndroidFilePointer* afp;
        if(asset)
        {
            afp = new AndroidFilePointer();
            afp->asset = asset;
            afp->offset = 0;
            Rocket::Core::FileHandle membuf = (Rocket::Core::FileHandle) afp;
           // return membuf;
        }



         //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Rocket::Core::FileHandle Read %d ...", size);
      //  if(!file) return 0;
      //  AndroidFilePointer* afp = (AndroidFilePointer*) file;
      //  AAsset* asset = afp->asset;

        void* buffer;
        off_t length = AAsset_getLength(asset);
        char const* assetBuffer = (char*) AAsset_getBuffer(asset);

            memcpy(buffer, assetBuffer, length);
            afp->offset += size;
            //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "... (afp->offset + size) <= length: read %d", size);
           // return size;



*/





    Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList("Rocket");

    std::cout << "PRIMER ARCHIVO: "<<  genLocs.front()->archive->getName() <<std::endl;

    //  genLocs.front()->archive
    // genLocs.front()->archive->getName();


    Ogre::ResourceGroupManager::LocationList::iterator it = genLocs.begin();
    Ogre::ResourceGroupManager::LocationList::iterator itEnd = genLocs.end();

    Ogre::String arch;
    for (; it != itEnd; ++it)
    {
        std::cout << "TODOS LOS ARCHIVOS de rockt: "<<  (*it)->archive->getName() <<std::endl;

        if ((*it)->archive->getName().find(fileName) != Ogre::String::npos)
        {

            std::cout << "HA ENCONTRADO EL ARCHIVO "<<   (*it)->archive->getName() <<std::endl;
            arch = (*it)->archive->getName();
            break;
        }
    }

    std::cout << "ARCH en font rocket "<<   arch <<std::endl;


    std::cout << "FONTFACE: "<<   (genLocs.front()->archive->getName()+"/"+fileName).c_str() <<std::endl;

    // Rocket::Core::FontDatabase::LoadFontFace((genLocs.front()->archive->getName()+"/"+fileName).c_str());



    Rocket::Core::Stream* st;




    //  Ogre::DataStreamPtr stream;
    AAsset* asset = AAssetManager_open(mAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
    if(asset)
    {
        std::cout << "ASSET ENCONTRADP" <<std::endl;

        off_t length = AAsset_getLength(asset);
        void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
        memcpy(membuf, AAsset_getBuffer(asset), length);

        st->Write(membuf,length);


        Rocket::Core::ElementDocument* document = context->LoadDocument(st);


        //  AAsset_close(asset);
        /*
        std::cout << "LOADFONTTTT:" <<  document->GetTagName() <<std::endl;
        std::cout << "LOADFONTTTT:" <<  document->GetAddress() <<std::endl;
        std::cout << "LOADFONTTTT:" <<  document->GetClassNames() <<std::endl;
        */
        return document;


        // st->

        //  Rocket::Core::FontDatabase::LoadFontFace(static_cast<Rocket::Core::byte*>(st),length);
        //   stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
    }


    return NULL;



}


#endif
