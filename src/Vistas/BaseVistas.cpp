#include "BaseVistas.h"

BaseVistas::BaseVistas(ModeloVista* modeloV) :
    //mInputManager(0),
    //mMouse(0),
    //mKeyboard(0)
    //, sys(0)
    //, mRoot(0)
    mCamera(0)
  //, tablero(0)
  , mTarget(0)
  #ifdef USAROCKET
  ,context(0)
  #endif
  ,mRoot(0)
  , mFSLayer (OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME))


{  
    modeloVista = modeloV;


    //esto cambialo para meter el mRoot primero con ANDROID
    //init();

}




BaseVistas::~BaseVistas()
{

#if ENABLE_SHADERS_CACHE_SAVE == 1
    if (Ogre::GpuProgramManager::getSingleton().isCacheDirty())
    {
        Ogre::String path = mFSLayer->getWritablePath("cache.bin");
        FILE * outFile = fopen(path.c_str(), "wb");
        if (outFile)
        {
            Ogre::LogManager::getSingleton().logMessage("Writing shader cache to ");
            Ogre::LogManager::getSingleton().logMessage(path.c_str());
            Ogre::DataStreamPtr ostream(new Ogre::FileHandleDataStream(path.c_str(), outFile, Ogre::DataStream::WRITE));
            Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(ostream);
            ostream->close();
        }
    }
#endif








    //Unattach OIS before window shutdown (very important under Linux)
    if( mInputManager )
    {
        mInputManager->destroyInputObject( mInputContext.mKeyboard );
        mInputManager->destroyInputObject( mInputContext.mMouse );
        OIS::InputManager::destroyInputSystem(mInputManager);
        mInputContext.mMouse = 0;
        mInputContext.mKeyboard = 0;
        mInputManager = 0;
    }

    mSceneMgr->removeRenderQueueListener( this );

#ifdef USAROCKET

    // Shutdown Rocket.
    
    context->RemoveReference();
    delete ogre_system;
    ogre_system = NULL;

    delete ogre_renderer;
    ogre_renderer = NULL;
#endif

    // delete mWindow;
    // mWindow = 0;
}

//void BaseVistas::createFrameListener()
//{
// Create the RocketFrameListener.
//mFrameListener = new RocketListener();

//mRoot->addFrameListener(this);

// Show the frame stats overlay.
//mFrameListener->showDebugOverlay(true);
//}

//int BaseVistas::getFPS()
//{
//    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
//    return ((int)stats.lastFPS);
//}


bool BaseVistas::frameStarted(const Ogre::FrameEvent& evt)
{


    return	Ogre::FrameListener::frameStarted(evt) && running;
}




bool BaseVistas::frameRenderingQueued(const Ogre::FrameEvent& evt)
{


    if(modeloVista->getApagar() || modeloVista->reiniciar || mWindow->isClosed() || !mWindow->isVisible() || mWindow->isHidden()){

        return false;

    }


    if (modeloVista->jugadaElegida()){
        //ESTO EN UN FUTURO HABRA QUE HACERLO EN OTRO THREAD
        modeloVista->aplicaCambio();


    }



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
            rotacionCamara( rotRestante);
            modeloVista->escenaMV->rotaCamara = Ogre::Real(0.0f);
        }
        else
        {
            rotacionCamara(rot);
            modeloVista->escenaMV->rotaCamara = modeloVista->escenaMV->rotaCamara - fRot;
        }
    }else mInputContext.capture();      // capture input

    return true;
}

#ifdef USAROCKET
// Called from Ogre before a queue group is rendered.
void BaseVistas::renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation))
{

    if (queueGroupId == Ogre::RENDER_QUEUE_OVERLAY && Ogre::Root::getSingleton().getRenderSystem()->_getViewport()->getOverlaysEnabled())
    {
        //#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

        context->Update();
        //	#endif
        configureRenderSystem();
        // #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

        context->Render();
        //#endif



    }


}

// Called from Ogre after a queue group is rendered.
void BaseVistas::renderQueueEnded(Ogre::uint8 ROCKET_UNUSED(queueGroupId), const Ogre::String& ROCKET_UNUSED(invocation), bool& ROCKET_UNUSED(repeatThisInvocation))
{


}

// Builds an OpenGL-style orthographic projection matrix.
void BaseVistas::buildProjectionMatrix(Ogre::Matrix4& projection_matrix)
{					
    float z_near = -1;
    float z_far = 1;

    projection_matrix = Ogre::Matrix4::ZERO;

    // Set up matrices.
    projection_matrix[0][0] = 2.0f / mWindow->getWidth();
    projection_matrix[0][3]= -1.0000000f;
    projection_matrix[1][1]= -2.0f / mWindow->getHeight();
    projection_matrix[1][3]= 1.0000000f;
    projection_matrix[2][2]= -2.0f / (z_far - z_near);
    projection_matrix[3][3]= 1.0000000f;
}



// Configures Ogre's rendering system for rendering Rocket.
void BaseVistas::configureRenderSystem()
{
    Ogre::RenderSystem* render_system = Ogre::Root::getSingleton().getRenderSystem();

    // Set up the projection and view matrices.
    
    buildProjectionMatrix(projection_matrix);

    render_system->_setProjectionMatrix(projection_matrix);


    render_system->_setViewMatrix(Ogre::Matrix4::IDENTITY);

    // Disable lighting, as all of Rocket's geometry is unlit.
    render_system->setLightingEnabled(false);
    // Disable depth-buffering; all of the geometry is already depth-sorted.
    render_system->_setDepthBufferParams(false, false);
    // Rocket generates anti-clockwise geometry, so enable clockwise-culling.
    render_system->_setCullingMode(Ogre::CULL_CLOCKWISE);
    // Disable fogging.
    render_system->_setFog(Ogre::FOG_NONE);

    // Enable writing to all four channels.
    render_system->_setColourBufferWriteEnabled(true, true, true, true);
    // Unbind any vertex or fragment programs bound previously by the application.
    render_system->unbindGpuProgram(Ogre::GPT_FRAGMENT_PROGRAM);
    render_system->unbindGpuProgram(Ogre::GPT_VERTEX_PROGRAM);

    // Set texture settings to clamp along both axes.
    Ogre::TextureUnitState::UVWAddressingMode addressing_mode;
    addressing_mode.u = Ogre::TextureUnitState::TAM_CLAMP;
    addressing_mode.v = Ogre::TextureUnitState::TAM_CLAMP;
    addressing_mode.w = Ogre::TextureUnitState::TAM_CLAMP;
    render_system->_setTextureAddressingMode(0, addressing_mode);

    // Set the texture coordinates for unit 0 to be read from unit 0.
    render_system->_setTextureCoordSet(0, 0);
    // Disable texture coordinate calculation.
    render_system->_setTextureCoordCalculation(0, Ogre::TEXCALC_NONE);
    // Enable linear filtering; images should be rendering 1 texel == 1 pixel, so point filtering could be used
    // except in the case of scaling tiled decorators.
    render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_POINT);
    // Disable texture coordinate transforms.
    render_system->_setTextureMatrix(0, Ogre::Matrix4::IDENTITY);
    // Reject pixels with an alpha of 0.
    render_system->_setAlphaRejectSettings(Ogre::CMPF_GREATER, 0, false);
    // Disable all texture units but the first.
    render_system->_disableTextureUnitsFrom(1);

    // Enable simple alpha blending.
    render_system->_setSceneBlending(Ogre::SBF_SOURCE_ALPHA, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);

    // Disable depth bias.
    render_system->_setDepthBias(0, 0);
}



void BaseVistas::BuildKeyMaps()
{
    key_identifiers[OIS::KC_UNASSIGNED] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_ESCAPE] = Rocket::Core::Input::KI_ESCAPE;
    key_identifiers[OIS::KC_1] = Rocket::Core::Input::KI_1;
    key_identifiers[OIS::KC_2] = Rocket::Core::Input::KI_2;
    key_identifiers[OIS::KC_3] = Rocket::Core::Input::KI_3;
    key_identifiers[OIS::KC_4] = Rocket::Core::Input::KI_4;
    key_identifiers[OIS::KC_5] = Rocket::Core::Input::KI_5;
    key_identifiers[OIS::KC_6] = Rocket::Core::Input::KI_6;
    key_identifiers[OIS::KC_7] = Rocket::Core::Input::KI_7;
    key_identifiers[OIS::KC_8] = Rocket::Core::Input::KI_8;
    key_identifiers[OIS::KC_9] = Rocket::Core::Input::KI_9;
    key_identifiers[OIS::KC_0] = Rocket::Core::Input::KI_0;
    key_identifiers[OIS::KC_MINUS] = Rocket::Core::Input::KI_OEM_MINUS;
    key_identifiers[OIS::KC_EQUALS] = Rocket::Core::Input::KI_OEM_PLUS;
    key_identifiers[OIS::KC_BACK] = Rocket::Core::Input::KI_BACK;
    key_identifiers[OIS::KC_TAB] = Rocket::Core::Input::KI_TAB;
    key_identifiers[OIS::KC_Q] = Rocket::Core::Input::KI_Q;
    key_identifiers[OIS::KC_W] = Rocket::Core::Input::KI_W;
    key_identifiers[OIS::KC_E] = Rocket::Core::Input::KI_E;
    key_identifiers[OIS::KC_R] = Rocket::Core::Input::KI_R;
    key_identifiers[OIS::KC_T] = Rocket::Core::Input::KI_T;
    key_identifiers[OIS::KC_Y] = Rocket::Core::Input::KI_Y;
    key_identifiers[OIS::KC_U] = Rocket::Core::Input::KI_U;
    key_identifiers[OIS::KC_I] = Rocket::Core::Input::KI_I;
    key_identifiers[OIS::KC_O] = Rocket::Core::Input::KI_O;
    key_identifiers[OIS::KC_P] = Rocket::Core::Input::KI_P;
    key_identifiers[OIS::KC_LBRACKET] = Rocket::Core::Input::KI_OEM_4;
    key_identifiers[OIS::KC_RBRACKET] = Rocket::Core::Input::KI_OEM_6;
    key_identifiers[OIS::KC_RETURN] = Rocket::Core::Input::KI_RETURN;
    key_identifiers[OIS::KC_LCONTROL] = Rocket::Core::Input::KI_LCONTROL;
    key_identifiers[OIS::KC_A] = Rocket::Core::Input::KI_A;
    key_identifiers[OIS::KC_S] = Rocket::Core::Input::KI_S;
    key_identifiers[OIS::KC_D] = Rocket::Core::Input::KI_D;
    key_identifiers[OIS::KC_F] = Rocket::Core::Input::KI_F;
    key_identifiers[OIS::KC_G] = Rocket::Core::Input::KI_G;
    key_identifiers[OIS::KC_H] = Rocket::Core::Input::KI_H;
    key_identifiers[OIS::KC_J] = Rocket::Core::Input::KI_J;
    key_identifiers[OIS::KC_K] = Rocket::Core::Input::KI_K;
    key_identifiers[OIS::KC_L] = Rocket::Core::Input::KI_L;
    key_identifiers[OIS::KC_SEMICOLON] = Rocket::Core::Input::KI_OEM_1;
    key_identifiers[OIS::KC_APOSTROPHE] = Rocket::Core::Input::KI_OEM_7;
    key_identifiers[OIS::KC_GRAVE] = Rocket::Core::Input::KI_OEM_3;
    key_identifiers[OIS::KC_LSHIFT] = Rocket::Core::Input::KI_LSHIFT;
    key_identifiers[OIS::KC_BACKSLASH] = Rocket::Core::Input::KI_OEM_5;
    key_identifiers[OIS::KC_Z] = Rocket::Core::Input::KI_Z;
    key_identifiers[OIS::KC_X] = Rocket::Core::Input::KI_X;
    key_identifiers[OIS::KC_C] = Rocket::Core::Input::KI_C;
    key_identifiers[OIS::KC_V] = Rocket::Core::Input::KI_V;
    key_identifiers[OIS::KC_B] = Rocket::Core::Input::KI_B;
    key_identifiers[OIS::KC_N] = Rocket::Core::Input::KI_N;
    key_identifiers[OIS::KC_M] = Rocket::Core::Input::KI_M;
    key_identifiers[OIS::KC_COMMA] = Rocket::Core::Input::KI_OEM_COMMA;
    key_identifiers[OIS::KC_PERIOD] = Rocket::Core::Input::KI_OEM_PERIOD;
    key_identifiers[OIS::KC_SLASH] = Rocket::Core::Input::KI_OEM_2;
    key_identifiers[OIS::KC_RSHIFT] = Rocket::Core::Input::KI_RSHIFT;
    key_identifiers[OIS::KC_MULTIPLY] = Rocket::Core::Input::KI_MULTIPLY;
    key_identifiers[OIS::KC_LMENU] = Rocket::Core::Input::KI_LMENU;
    key_identifiers[OIS::KC_SPACE] = Rocket::Core::Input::KI_SPACE;
    key_identifiers[OIS::KC_CAPITAL] = Rocket::Core::Input::KI_CAPITAL;
    key_identifiers[OIS::KC_F1] = Rocket::Core::Input::KI_F1;
    key_identifiers[OIS::KC_F2] = Rocket::Core::Input::KI_F2;
    key_identifiers[OIS::KC_F3] = Rocket::Core::Input::KI_F3;
    key_identifiers[OIS::KC_F4] = Rocket::Core::Input::KI_F4;
    key_identifiers[OIS::KC_F5] = Rocket::Core::Input::KI_F5;
    key_identifiers[OIS::KC_F6] = Rocket::Core::Input::KI_F6;
    key_identifiers[OIS::KC_F7] = Rocket::Core::Input::KI_F7;
    key_identifiers[OIS::KC_F8] = Rocket::Core::Input::KI_F8;
    key_identifiers[OIS::KC_F9] = Rocket::Core::Input::KI_F9;
    key_identifiers[OIS::KC_F10] = Rocket::Core::Input::KI_F10;
    key_identifiers[OIS::KC_NUMLOCK] = Rocket::Core::Input::KI_NUMLOCK;
    key_identifiers[OIS::KC_SCROLL] = Rocket::Core::Input::KI_SCROLL;
    key_identifiers[OIS::KC_NUMPAD7] = Rocket::Core::Input::KI_7;
    key_identifiers[OIS::KC_NUMPAD8] = Rocket::Core::Input::KI_8;
    key_identifiers[OIS::KC_NUMPAD9] = Rocket::Core::Input::KI_9;
    key_identifiers[OIS::KC_SUBTRACT] = Rocket::Core::Input::KI_SUBTRACT;
    key_identifiers[OIS::KC_NUMPAD4] = Rocket::Core::Input::KI_4;
    key_identifiers[OIS::KC_NUMPAD5] = Rocket::Core::Input::KI_5;
    key_identifiers[OIS::KC_NUMPAD6] = Rocket::Core::Input::KI_6;
    key_identifiers[OIS::KC_ADD] = Rocket::Core::Input::KI_ADD;
    key_identifiers[OIS::KC_NUMPAD1] = Rocket::Core::Input::KI_1;
    key_identifiers[OIS::KC_NUMPAD2] = Rocket::Core::Input::KI_2;
    key_identifiers[OIS::KC_NUMPAD3] = Rocket::Core::Input::KI_3;
    key_identifiers[OIS::KC_NUMPAD0] = Rocket::Core::Input::KI_0;
    key_identifiers[OIS::KC_DECIMAL] = Rocket::Core::Input::KI_DECIMAL;
    key_identifiers[OIS::KC_OEM_102] = Rocket::Core::Input::KI_OEM_102;
    key_identifiers[OIS::KC_F11] = Rocket::Core::Input::KI_F11;
    key_identifiers[OIS::KC_F12] = Rocket::Core::Input::KI_F12;
    key_identifiers[OIS::KC_F13] = Rocket::Core::Input::KI_F13;
    key_identifiers[OIS::KC_F14] = Rocket::Core::Input::KI_F14;
    key_identifiers[OIS::KC_F15] = Rocket::Core::Input::KI_F15;
    key_identifiers[OIS::KC_KANA] = Rocket::Core::Input::KI_KANA;
    key_identifiers[OIS::KC_ABNT_C1] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_CONVERT] = Rocket::Core::Input::KI_CONVERT;
    key_identifiers[OIS::KC_NOCONVERT] = Rocket::Core::Input::KI_NONCONVERT;
    key_identifiers[OIS::KC_YEN] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_ABNT_C2] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_NUMPADEQUALS] = Rocket::Core::Input::KI_OEM_NEC_EQUAL;
    key_identifiers[OIS::KC_PREVTRACK] = Rocket::Core::Input::KI_MEDIA_PREV_TRACK;
    key_identifiers[OIS::KC_AT] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_COLON] = Rocket::Core::Input::KI_OEM_1;
    key_identifiers[OIS::KC_UNDERLINE] = Rocket::Core::Input::KI_OEM_MINUS;
    key_identifiers[OIS::KC_KANJI] = Rocket::Core::Input::KI_KANJI;
    key_identifiers[OIS::KC_STOP] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_AX] = Rocket::Core::Input::KI_OEM_AX;
    key_identifiers[OIS::KC_UNLABELED] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_NEXTTRACK] = Rocket::Core::Input::KI_MEDIA_NEXT_TRACK;
    key_identifiers[OIS::KC_NUMPADENTER] = Rocket::Core::Input::KI_NUMPADENTER;
    key_identifiers[OIS::KC_RCONTROL] = Rocket::Core::Input::KI_RCONTROL;
    key_identifiers[OIS::KC_MUTE] = Rocket::Core::Input::KI_VOLUME_MUTE;
    key_identifiers[OIS::KC_CALCULATOR] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_PLAYPAUSE] = Rocket::Core::Input::KI_MEDIA_PLAY_PAUSE;
    key_identifiers[OIS::KC_MEDIASTOP] = Rocket::Core::Input::KI_MEDIA_STOP;
    key_identifiers[OIS::KC_VOLUMEDOWN] = Rocket::Core::Input::KI_VOLUME_DOWN;
    key_identifiers[OIS::KC_VOLUMEUP] = Rocket::Core::Input::KI_VOLUME_UP;
    key_identifiers[OIS::KC_WEBHOME] = Rocket::Core::Input::KI_BROWSER_HOME;
    key_identifiers[OIS::KC_NUMPADCOMMA] = Rocket::Core::Input::KI_SEPARATOR;
    key_identifiers[OIS::KC_DIVIDE] = Rocket::Core::Input::KI_DIVIDE;
    key_identifiers[OIS::KC_SYSRQ] = Rocket::Core::Input::KI_SNAPSHOT;
    key_identifiers[OIS::KC_RMENU] = Rocket::Core::Input::KI_RMENU;
    key_identifiers[OIS::KC_PAUSE] = Rocket::Core::Input::KI_PAUSE;
    key_identifiers[OIS::KC_HOME] = Rocket::Core::Input::KI_HOME;
    key_identifiers[OIS::KC_UP] = Rocket::Core::Input::KI_UP;
    key_identifiers[OIS::KC_PGUP] = Rocket::Core::Input::KI_PRIOR;
    key_identifiers[OIS::KC_LEFT] = Rocket::Core::Input::KI_LEFT;
    key_identifiers[OIS::KC_RIGHT] = Rocket::Core::Input::KI_RIGHT;
    key_identifiers[OIS::KC_END] = Rocket::Core::Input::KI_END;
    key_identifiers[OIS::KC_DOWN] = Rocket::Core::Input::KI_DOWN;
    key_identifiers[OIS::KC_PGDOWN] = Rocket::Core::Input::KI_NEXT;
    key_identifiers[OIS::KC_INSERT] = Rocket::Core::Input::KI_INSERT;
    key_identifiers[OIS::KC_DELETE] = Rocket::Core::Input::KI_DELETE;
    key_identifiers[OIS::KC_LWIN] = Rocket::Core::Input::KI_LWIN;
    key_identifiers[OIS::KC_RWIN] = Rocket::Core::Input::KI_RWIN;
    key_identifiers[OIS::KC_APPS] = Rocket::Core::Input::KI_APPS;
    key_identifiers[OIS::KC_POWER] = Rocket::Core::Input::KI_POWER;
    key_identifiers[OIS::KC_SLEEP] = Rocket::Core::Input::KI_SLEEP;
    key_identifiers[OIS::KC_WAKE] = Rocket::Core::Input::KI_WAKE;
    key_identifiers[OIS::KC_WEBSEARCH] = Rocket::Core::Input::KI_BROWSER_SEARCH;
    key_identifiers[OIS::KC_WEBFAVORITES] = Rocket::Core::Input::KI_BROWSER_FAVORITES;
    key_identifiers[OIS::KC_WEBREFRESH] = Rocket::Core::Input::KI_BROWSER_REFRESH;
    key_identifiers[OIS::KC_WEBSTOP] = Rocket::Core::Input::KI_BROWSER_STOP;
    key_identifiers[OIS::KC_WEBFORWARD] = Rocket::Core::Input::KI_BROWSER_FORWARD;
    key_identifiers[OIS::KC_WEBBACK] = Rocket::Core::Input::KI_BROWSER_BACK;
    key_identifiers[OIS::KC_MYCOMPUTER] = Rocket::Core::Input::KI_UNKNOWN;
    key_identifiers[OIS::KC_MAIL] = Rocket::Core::Input::KI_LAUNCH_MAIL;
    key_identifiers[OIS::KC_MEDIASELECT] = Rocket::Core::Input::KI_LAUNCH_MEDIA_SELECT;
}

int BaseVistas::GetKeyModifierState()
{
    int modifier_state = 0;

    if (mInputContext.mKeyboard->isModifierDown(OIS::Keyboard::Ctrl))
        modifier_state |= Rocket::Core::Input::KM_CTRL;
    if (mInputContext.mKeyboard->isModifierDown(OIS::Keyboard::Shift))
        modifier_state |= Rocket::Core::Input::KM_SHIFT;
    if (mInputContext.mKeyboard->isModifierDown(OIS::Keyboard::Alt))
        modifier_state |= Rocket::Core::Input::KM_ALT;

    /*#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

    if (GetKeyState(VK_CAPITAL) > 0)
        modifier_state |= Rocket::Core::Input::KM_CAPSLOCK;
    if (GetKeyState(VK_NUMLOCK) > 0)
        modifier_state |= Rocket::Core::Input::KM_NUMLOCK;
    if (GetKeyState(VK_SCROLL) > 0)
        modifier_state |= Rocket::Core::Input::KM_SCROLLLOCK;
*/
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE

    UInt32 key_modifiers = GetCurrentEventKeyModifiers();
    if (key_modifiers & (1 << alphaLockBit))
        modifier_state |= Rocket::Core::Input::KM_CAPSLOCK;

#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX

    XKeyboardState keyboard_state;
    XGetKeyboardControl(DISPLAY!, &keyboard_state);

    if (keyboard_state.led_mask & (1 << 0))
        modifier_state |= Rocket::Core::Input::KM_CAPSLOCK;
    if (keyboard_state.led_mask & (1 << 1))
        modifier_state |= Rocket::Core::Input::KM_NUMLOCK;
    if (keyboard_state.led_mask & (1 << 2))
        modifier_state |= Rocket::Core::Input::KM_SCROLLLOCK;

#endif

    return modifier_state;
}


#endif


//Adjust mouse clipping area
void BaseVistas::windowResized()
{
    unsigned int width, height, depth;
    int left, top;
    mWindow->getMetrics(width, height, depth, left, top);
    
    const OIS::MouseState &ms = mInputContext.mMouse->getMouseState();
    
    ms.width = width;
    ms.height = height;
}
/*
Ogre::Ray BaseVistas ::getCameraToViewportRay()
{

    return mCamera->getCameraToViewportRay
            (posx/float(mWindow->getWidth()), posy/float(mWindow->getHeight()));

}

*/
void BaseVistas::createCamera(void)
{


    // Create the camera
    mCamera = mSceneMgr->createCamera("MiCam");


    // Position it at 500 in Z direction
    // mCamera->setPosition(Ogre::Vector3(40,40,50));
    // Look back along -Z


    // mCamera->lookAt(Ogre::Vector3(0,0,0));


    // mCamera->setNearClipDistance(5);


    if (mCamera->getSceneManager()->getRootSceneNode() != mTarget)
    {


        mTarget = mCamera->getSceneManager()->getRootSceneNode();
        if(mTarget)
        {


            mCamera->setPosition(mTarget->_getDerivedPosition());
            mCamera->setOrientation(mTarget->_getDerivedOrientation());

            //rota sobre su eje horizontal (arriba/abajo)
            mCamera->pitch(Ogre::Degree(-48));

            //rota sobre su eje vertical (Izquieda/derecha)
            mCamera->yaw(Ogre::Degree(90));
            mCamera->moveRelative(Ogre::Vector3(0, 0, 100));



            //mCamera->setAutoTracking(true, mTarget);
        }
        else
        {


            mCamera->setAutoTracking(false);
        }
    }


    mCamera->setFixedYawAxis(true,Ogre::Vector3(0, 0, 0));

    // mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    //  mTopSpeed = topSpeed;

    // return mCamera;
}

void BaseVistas::createViewports(Ogre::RenderWindow* window)
{
    //  mWindow = window;
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);

    vp->setBackgroundColour(Ogre::ColourValue(0,0,0,50));
    vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mCamera->setAutoAspectRatio(true);
    mCamera->setNearClipDistance(5);


}


void BaseVistas::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
    mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}



void BaseVistas::rotacionCamara(Ogre::Degree angulo)
{
    Ogre::Real dist = mCamera->getPosition().length();

    mCamera->moveRelative(Ogre::Vector3(0, 0, -dist));
    //Mueve la camara a la posicion central
    // mCamera->setPosition(Ogre::Vector3(0,0,0));
    //Rota la camara
    mCamera->pitch(-angulo);

    //Devuelve la camara a su posicion original
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}








bool BaseVistas::configuraGraficos()
{

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID

    //SETUP RESOURCES
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                        archName, typeName, secName);
        }
    }

    //CONFIGURE RENDER SYSTEM
    Ogre::RenderSystem *renderSystem = Ogre::Root::getSingleton().getRenderSystem();
    // Manually set some configuration options (optional)
    
    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
    }

    if (modeloVista->pantallaCompleta){
        renderSystem->setConfigOption("Full Screen", "Yes");

    }else{
        renderSystem->setConfigOption("Full Screen", "No");
    }

    renderSystem->setConfigOption("Video Mode", modeloVista->resolucion);

    for(Ogre::ConfigOptionMap::iterator it = renderSystem->getConfigOptions().begin();
        it != renderSystem->getConfigOptions().end(); it++)
    {
        std::pair<const std::basic_string<char>,Ogre::ConfigOption> CO = *it;
    }
#else


    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib/cache", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib/GLSLES", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/materials/scripts", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/materials/textures", "APKFileSystem", "General");
    //Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/materials/programs", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/models", "APKFileSystem", "General");

#ifdef USAROCKET
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/", "APKFileSystem", "Rocket");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/librocket", "APKFileSystem", "Rocket");
#endif



#endif




    return true;
}


#ifdef USAROCKET


bool BaseVistas::configuraRocket()
{

    ogre_system = NULL;
    ogre_renderer = NULL;
    // Rocket initialisation.


    ogre_renderer = new RenderInterfaceOgre3D(mWindow->getWidth(), mWindow->getHeight());

    //ogre_renderer->setCustomProjectionMatrix(projection_matrix);


    Rocket::Core::SetRenderInterface(ogre_renderer);

    ogre_system = new SystemInterfaceOgre3D();
    Rocket::Core::SetSystemInterface(ogre_system);


    Rocket::Core::Initialise();

    Rocket::Controls::Initialise();


    BuildKeyMaps();


    context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(mWindow->getWidth(), mWindow->getHeight()));
    Rocket::Debugger::Initialise(context);

    context->SetDimensions( Rocket::Core::Vector2i( mWindow->getWidth(), mWindow->getHeight() ) );


    //Ogre::ResourceGroupManager::getSingleton().createResourceGroup("Rocket");
    //Ogre::ResourceGroupManager::getSingleton().addResourceLocation(rocket_path.Replace("\\", "/").CString(), "FileSystem", "Rocket");

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

    // Load the fonts from the path to the sample directory.
    Rocket::Core::FontDatabase::LoadFontFace(/*sample_path + "../../assets/*/"../media/librocket/Delicious-Roman.otf");
    Rocket::Core::FontDatabase::LoadFontFace("../media/librocket/Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("../media/librocket/Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("../media/librocket/Delicious-BoldItalic.otf");


    // Load the mouse cursor and release the caller's reference.
    Rocket::Core::ElementDocument* cursor = context->LoadMouseCursor("../media/librocket/cursor.rml");

    if (cursor)
        cursor->RemoveReference();

#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID


    Rocket::Core::FontDatabase::LoadFontFace("librocket/Delicious-Roman.otf");

    Rocket::Core::FontDatabase::LoadFontFace("librocket/Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("librocket/Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("librocket/Delicious-BoldItalic.otf");

#endif

    /*
    context->AddEventListener("click", );

*/
    return true;
}
#endif


bool BaseVistas::configuraOgre()
{

    //INICIA OGRE, PLUGINS ESTATICOS
    
#ifdef OGRE_STATIC_LIB
    mStaticPluginLoader = new Ogre::StaticPluginLoader();
    //mStaticPluginLoader->
    mStaticPluginLoader->load();
#endif
    mRoot->setRenderSystem(mRoot->getAvailableRenderers().at(0));



    //configuraGraficos();
    // Ogre::Root::getSingleton().createRenderWindow("OgreWindow", 0, 0, false, &opt);





    return true;
}

bool BaseVistas::configuraOIS()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    //INICIA OIS
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem( pl );

    mInputContext.mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mInputContext.mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mInputContext.mMouse->getMouseState().width = mWindow->getWidth();
    mInputContext.mMouse->getMouseState().height = mWindow->getHeight();


#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID

    /*	 if(!mInputContext.mTouch)
                        mInputContext.mTouch = new AndroidMultiTouch();

                    if(!mInputContext.mKeyboard)
                        mInputContext.mKeyboard = new AndroidKeyboard();

*/


#endif


    //mMouse->setEventCallback(vista);
    // mKeyboard->setEventCallback(vista);

    //	mMouse->setEventCallback(this);
    //	mKeyboard->setEventCallback(this);


    //Set initial mouse clipping size


    return true;
}


void BaseVistas::init()
{


    if (!mRoot)
    {
        mRoot =new Ogre::Root(/*"plugins.cfg"*/);

        configuraOgre();
        configuraGraficos();


        mWindow = mRoot->initialise(true,"3D CHESS");


        configuraOIS();

    }


    //Register as a Window listener
    mWindow->removeAllViewports();

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(0);
    mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "MANAGER");

    createCamera();

    createViewports(mWindow);





    setupShaderSystem();


    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();



    //OIS::InputContext mInputContext;


    mRoot->addFrameListener(this);
    // Add the application as a listener to Ogre's render queue so we can render during the overlay.
    mSceneMgr->addRenderQueueListener(this);

    //configureRenderSystem();




    //context->AddEventListener("click", this);
#ifdef USAROCKET

    configuraRocket();
#endif
    running = true;

}




void BaseVistas::setupShaderSystem(){


    // 7  - JUSTO DESPUES DE ADDVIERPORT DEL WINDOW
    // Initialize shader generator.
    // Must be before resource loading in order to allow parsing extended material attributes.
    bool success = initialiseRTShaderSystem(mRoot->getSceneManager("MANAGER"));
    if (!success)
    {
        OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND,
                    "Shader Generator Initialization failed - Core shader libs path not found",
                    "SampleBrowser::createDummyScene");
    }
    if(mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION) == false)
    {


        mWindow->getViewport(0)->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

        // creates shaders for base material BaseWhite using the RTSS
        Ogre::MaterialPtr baseWhite = Ogre::MaterialManager::getSingleton().getByName("BaseWhite", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);

        baseWhite->setLightingEnabled(false);

        mShaderGenerator->createShaderBasedTechnique(
                    "BaseWhite",
                    Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
                    Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,
                                           "BaseWhite");

        if(baseWhite->getNumTechniques() > 1)
        {
            baseWhite->getTechnique(0)->getPass(0)->setVertexProgram(
                        baseWhite->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
            baseWhite->getTechnique(0)->getPass(0)->setFragmentProgram(
                        baseWhite->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
        }

        // creates shaders for base material BaseWhiteNoLighting using the RTSS
        mShaderGenerator->createShaderBasedTechnique(
                    "BaseWhiteNoLighting",
                    Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
                    Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,
                                           "BaseWhiteNoLighting");
        Ogre::MaterialPtr baseWhiteNoLighting = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
        if(baseWhite->getNumTechniques() > 1)
        {
            baseWhiteNoLighting->getTechnique(0)->getPass(0)->setVertexProgram(
                        baseWhiteNoLighting->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
            baseWhiteNoLighting->getTechnique(0)->getPass(0)->setFragmentProgram(
                        baseWhiteNoLighting->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
        }
    }




#if ENABLE_SHADERS_CACHE_SAVE == 1
    if(Ogre::GpuProgramManager::getSingleton().canGetCompiledShaderBuffer())
        Ogre::GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true);
#endif
#if	ENABLE_SHADERS_CACHE_LOAD == 1
    // Load for a package version of the shaders.
    Ogre::String path = "cache.bin";
    FILE * inFile = NULL;
    inFile = fopen(path.c_str(), "rb");
    // If that does not exist, see if there is a version in the writable location.
    if (!inFile)
    {
        path = mFSLayer->getWritablePath("cache.bin");
        inFile = fopen(path.c_str(), "rb");
    }
    if (inFile)
    {
        Ogre::LogManager::getSingleton().logMessage("Loading shader cache from ");
        Ogre::LogManager::getSingleton().logMessage(path.c_str());
        Ogre::DataStreamPtr istream(new Ogre::FileHandleDataStream(path.c_str(), inFile, Ogre::DataStream::READ));
        Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(istream);
    }
#endif



}



//-----------------------------------------------------------------------------
//      | Initialize the RT Shader system.
//      -----------------------------------------------------------------------------
bool BaseVistas::initialiseRTShaderSystem(Ogre::SceneManager* sceneMgr)
{

    if (Ogre::RTShader::ShaderGenerator::initialize())
    {
        mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

        mShaderGenerator->addSceneManager(sceneMgr);




#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID && OGRE_PLATFORM != OGRE_PLATFORM_NACL && OGRE_PLATFORM != OGRE_PLATFORM_WINRT
        // Setup core libraries and shader cache path.
        Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
        Ogre::StringVector::iterator itGroup = groupVector.begin();
        Ogre::StringVector::iterator itGroupEnd = groupVector.end();
        Ogre::String shaderCoreLibsPath;
        Ogre::String shaderCachePath;

        for (; itGroup != itGroupEnd; ++itGroup)
        {
            Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
            Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
            Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
            bool coreLibsFound = false;

            // Try to find the location of the core shader lib functions and use it
            // as shader cache path as well - this will reduce the number of generated files
            // when running from different directories.
            for (; it != itEnd; ++it)
            {
                if ((*it)->archive->getName().find("RTShaderLib") != Ogre::String::npos)
                {
                    shaderCoreLibsPath = (*it)->archive->getName() + "/cache/";
                    shaderCachePath = shaderCoreLibsPath;
                    coreLibsFound = true;
                    break;
                }
            }
            // Core libs path found in the current group.
            if (coreLibsFound)
                break;
        }

        // Core shader libs not found -> shader generating will fail.
        if (shaderCoreLibsPath.empty())
            return false;


#ifdef _RTSS_WRITE_SHADERS_TO_DISK
        // Set shader cache path.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
        shaderCachePath = Ogre::macCachePath();
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        shaderCachePath = Ogre::macCachePath() + "/org.gnusoft.RTShaderCache";
#endif
        mShaderGenerator->setShaderCachePath(shaderCachePath);
#endif


#else
        //       mShaderGenerator->setShaderCachePath("RTShaderLib/cache");


#endif







        // Create and register the material manager listener if it doesn't exist yet.
        if (mMaterialMgrListener == NULL) {
            mMaterialMgrListener = new ShaderGeneratorTechniqueResolverListener(mShaderGenerator);
            Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
        }
    }


    return true;
}

//-----------------------------------------------------------------------------
////   | Destroy the RT Shader system.
//    -----------------------------------------------------------------------------
void BaseVistas::destroyRTShaderSystem()
{
    // Restore default scheme.
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    // Unregister the material manager listener.
    if (mMaterialMgrListener != NULL)
    {
        Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
        delete mMaterialMgrListener;
        mMaterialMgrListener = NULL;
    }

    // Destroy RTShader system.
    if (mShaderGenerator != NULL)
    {
        Ogre::RTShader::ShaderGenerator::destroy();
        mShaderGenerator = NULL;
    }
}

