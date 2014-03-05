#include "BaseListeners.h"

BaseListeners::BaseListeners( RocketListener* vistaO) :
    //mInputManager(0),
    //mMouse(0),
    //mKeyboard(0)
    //, sys(0)
    //, mRoot(0)
    //  mCamera(0)
    //, tablero(0)
    //mTarget(0)
    mSceneMgr(0)
  
{  

    vistaOgre = vistaO;

    //modeloVista =


    //vistaOgre->mWindow;


    mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("MANAGER");


    
    //initEventListener();



    //1
    //mShaderGenerator->removeAllShaderBasedTechniques(); // clear techniques from the RTSS


    //2
    //	if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION))
    //          {
    //            destroyDummyScene();
    //          destroyRTShaderSystem();
    //    }

    //3
    // if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION))
    //      {
    //        createDummyScene();
    //  }

    //  setShaderGenerator(mShaderGenerator);


    //6
    //  if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
    //{
    //    mShaderGenerator->addSceneManager(mRoot->getSceneManager("MANAGER"));
    //}


    //mShaderGenerator->addSceneManager(mSceneMgr);




    //4 SETUP
    // Check if the render system supports any shader profiles.
    // Don't load samples that require shaders if we don't have any shader support, GL ES 1.x for example.
    // const Ogre::RenderSystemCapabilities* caps = vistaOgre->mRoot->getRenderSystem()->getCapabilities();
    //  Ogre::RenderSystemCapabilities::ShaderProfiles profiles = caps->getSupportedShaderProfiles();

    //5
    //     bool hasProgrammableGPU = (!profiles.empty());





}

BaseListeners::~BaseListeners()
{

#ifdef USAROCKET
    context->RemoveEventListener("click", this);
    context->UnloadAllDocuments();
#endif

    vistaOgre->mInputContext.mMouse->setEventCallback(0);
    vistaOgre->mInputContext.mKeyboard->setEventCallback(0);


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
    //context->ProcessMouseMove(evt.state.X.abs, evt.state.Y.abs, 0);

    return true;

}

bool BaseListeners::touchPressed(const OIS::MultiTouchEvent& evt)
{

    //context->ProcessMouseMove(evt.state.X.abs, evt.state.Y.abs, 0);
    //   context->ProcessMouseButtonDown(0, 0);

    return true;

}
bool BaseListeners::touchReleased(const OIS::MultiTouchEvent& evt)
{
    //	context->ProcessMouseButtonUp(0, 0);
    return true;
}
bool BaseListeners::touchCancelled(const OIS::MultiTouchEvent& evt)
{

    return true;

}
#else



bool BaseListeners::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32


#ifdef USAROCKET

    context->ProcessMouseButtonDown((int) id, 0);
#endif
    //context->Proc
#endif



    // sys->injectMouseButtonDown(convertButton(id));
    return true;
}

bool BaseListeners::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#ifdef USAROCKET

    context->ProcessMouseButtonUp((int) id, 0);
#endif
#endif
    
    // sys->injectMouseButtonUp(convertButton(id));
    return true;
}


bool BaseListeners::mouseMoved( const OIS::MouseEvent &e )
{
    //int key_modifier_state = GetKeyModifierState();

    //mInputContext.

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#ifdef USAROCKET

    context->ProcessMouseMove(e.state.X.abs, e.state.Y.abs, 0);
    if (e.state.Z.rel != 0)
        context->ProcessMouseWheel(e.state.Z.rel / -120, 0);
#endif
#endif

    //VistaAjedrez::mouseMoved(e);

    return true;

}

#endif
bool BaseListeners::keyPressed( const OIS::KeyEvent &evt )
{


#ifdef USAROCKET

    Rocket::Core::Input::KeyIdentifier key_identifier = vistaOgre->key_identifiers[evt.key];



    context->ProcessKeyDown(key_identifier, 0);

#endif


    return true;
}

bool BaseListeners::keyReleased( const OIS::KeyEvent &e )
{
#ifdef USAROCKET

    Rocket::Core::Input::KeyIdentifier key_identifier = vistaOgre->key_identifiers[e.key];

    if (key_identifier != Rocket::Core::Input::KI_UNKNOWN)
        context->ProcessKeyUp(key_identifier, 0);
#endif

    if (e.key == OIS::KC_ESCAPE)
        running = false;


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
    Ogre::Real dist = (vistaOgre->mCamera->getPosition() - vistaOgre->mTarget->_getDerivedPosition()).length();
    vistaOgre->mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));

}


#ifdef USAROCKET

void BaseListeners::initEventListener()
{
    
    context = Rocket::Core::GetContext("main");



    context->AddEventListener("click", this);


}

#endif
void BaseListeners::rotacionCamara(Ogre::Degree angulo)
{
    Ogre::Real dist = (vistaOgre->mCamera->getPosition() - vistaOgre->mTarget->_getDerivedPosition()).length();

    //Mueve la camara a la posicion central
    vistaOgre->mCamera->setPosition(vistaOgre->mTarget->_getDerivedPosition());
    //Rota la camara
    vistaOgre->mCamera->yaw(-angulo);

    //Devuelve la camara a su posicion original
    vistaOgre->mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}
/*
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID



Rocket::Core::ElementDocument* BaseListeners::openFontRocket(const Ogre::String& fileName)
{







    Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList("Rocket");


    //  genLocs.front()->archive
    // genLocs.front()->archive->getName();


    Ogre::ResourceGroupManager::LocationList::iterator it = genLocs.begin();
    Ogre::ResourceGroupManager::LocationList::iterator itEnd = genLocs.end();

    Ogre::String arch;
    for (; it != itEnd; ++it)
    {

        if ((*it)->archive->getName().find(fileName) != Ogre::String::npos)
        {

            arch = (*it)->archive->getName();
            break;
        }
    }

    // Rocket::Core::FontDatabase::LoadFontFace((genLocs.front()->archive->getName()+"/"+fileName).c_str());



    Rocket::Core::Stream* st;




    //  Ogre::DataStreamPtr stream;
    AAsset* asset = AAssetManager_open(mAssetMgr, fileName.c_str(), AASSET_MODE_BUFFER);
    if(asset)
    {

        off_t length = AAsset_getLength(asset);
        void* membuf = OGRE_MALLOC(length, Ogre::MEMCATEGORY_GENERAL);
        memcpy(membuf, AAsset_getBuffer(asset), length);

        st->Write(membuf,length);


        Rocket::Core::ElementDocument* document = context->LoadDocument(st);


        //  AAsset_close(asset);

        return document;


        // st->

        //  Rocket::Core::FontDatabase::LoadFontFace(static_cast<Rocket::Core::byte*>(st),length);
        //   stream = Ogre::DataStreamPtr(new Ogre::MemoryDataStream(membuf, length, true, true));
    }


    return NULL;



}


#endif
*/
