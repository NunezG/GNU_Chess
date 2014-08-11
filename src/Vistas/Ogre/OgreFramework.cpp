#include "OgreFramework.h"

OgreFramework::OgreFramework() :
    //mMouse(0),
    //mKeyboard(0)
    //, sys(0)
    //, mRoot(0)
    mCamera(0)
  //, tablero(0)
  , mTarget(0)
  ,mRoot(0)
  ,mWindow(0)
  ,mSceneMgr(0)
  , modeloVista(0)
  , mStaticPluginLoader(0)
  , vp(0)
  
  ,mMaterialMgrListener(0)
  //, mFSLayer (OGRE_NEW(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME))

{  
    modeloVista = new ModeloVista();

	
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
modeloVista->voltea = 90;

#else
	modeloVista->voltea = 180;
    mInputManager = 0;



#endif

    //esto cambialo para meter el mRoot primero con ANDROID
    //init();

}




OgreFramework::~OgreFramework()
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


	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32


    //Unattach OIS before window shutdown (very important under Linux)
  
        mInputManager->destroyInputObject( mInputContext.mKeyboard );
        mInputManager->destroyInputObject( mInputContext.mMouse );
        OIS::InputManager::destroyInputSystem(mInputManager);
       
		// delete mTouch;
      //  mTouch = NULL;

      //  delete mKeyboard;
     //   mKeyboard = NULL;
		
		mInputContext.mMouse = 0;
        mInputContext.mKeyboard = 0;
        mInputManager = 0;
 
#else

    delete mInputContext.mKeyboard;
   delete mInputContext.mMultiTouch;
    mInputContext.mKeyboard = 0;
    mInputContext.mMultiTouch = 0;


#endif
 


    if (mRoot )
    {
        //Ogre::WindowEventUtilities::addWindowEventListener(mWindow, vista);



        // mRoot->removeFrameListener(vista);
        //mRoot->destroySceneManager(modelo->escenaAjedrez->mSceneMgr);
        //  modelo->escenaAjedrez->destruyeTablero();
        //  mRoot->destroySceneManager(mSceneMgr);
        delete mRoot;
        mRoot = NULL;
    }


#ifdef OGRE_STATIC_LIB
        mStaticPluginLoader->unload();
        delete mStaticPluginLoader;
        mStaticPluginLoader = NULL;
#endif



		delete modeloVista;
		modeloVista = NULL;
	//borraVistaActiva();

   // delete mWindow;





    // delete mWindow;
    // mWindow = 0;
}

//void OgreFramework::createFrameListener()
//{
// Create the RocketFrameListener.
//mFrameListener = new RocketFrameListener();

//mRoot->addFrameListener(this);

// Show the frame stats overlay.
//mFrameListener->showDebugOverlay(true);
//}

//int OgreFramework::getFPS()
//{
//    Ogre::RenderTarget::FrameStats stats = mWindow->getStatistics();
//    return ((int)stats.lastFPS);
//}




void OgreFramework::empieza()
{

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID

    mRoot->startRendering();

#else



#endif
    //mRoot->stop
}

	void OgreFramework::startScene()
	{

		
    //Register as a Window listener
    mWindow->removeAllViewports();

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    mSceneMgr = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "MANAGER");

    createCamera();

    createViewports(mWindow);

    setupShaderSystem();


	}




//Adjust mouse clipping area
void OgreFramework::windowResized()
{

    unsigned int width, height, depth;
    int left, top;
    mWindow->getMetrics(width, height, depth, left, top);
    
    const OIS::MouseState &ms = mInputContext.mMouse->getMouseState();
    
    ms.width = width;
    ms.height = height;
}



void OgreFramework::createCamera(void)
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


 //   mCamera->setFixedYawAxis(true,Ogre::Vector3(0, 0, 0));

    // mInputMan = new InputMan::SdkCameraMan(mCamera);   // create a default camera controller
    //  mTopSpeed = topSpeed;

    // return mCamera;
}

void OgreFramework::createViewports(Ogre::RenderWindow* window)
{
    //  mWindow = window;
    // Create one viewport, entire window
	vp = mWindow->addViewport(mCamera);

    vp->setBackgroundColour(Ogre::ColourValue(50,55,50,50));
   // vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
                Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mCamera->setAutoAspectRatio(true);
    mCamera->setNearClipDistance(5);


}


void OgreFramework::DistanciaCamara(int distanciaRelativa)
{
    Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();
    mCamera->moveRelative(Ogre::Vector3(0, 0, -distanciaRelativa * 0.0008f * dist));
}

void OgreFramework::rotacionCamara(Ogre::Degree angulo)
{
    Ogre::Real dist = mCamera->getPosition().length();

    mCamera->moveRelative(Ogre::Vector3(0, 0, -dist));
    //Mueve la camara a la posicion central
    // mCamera->setPosition(Ogre::Vector3(0,0,0));
    //Rota la camara

	#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    mCamera->pitch(-angulo);
#else
    mCamera->yaw(-angulo);
#endif

    //Devuelve la camara a su posicion original
    mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}




void OgreFramework::locateResources()
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

 
#else


    //Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib", "APKFileSystem", "Essential");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib/materials", "APKFileSystem", "Essential");
   // Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib/cache", "APKFileSystem", "Essential");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/RTShaderLib/GLSLES", "APKFileSystem", "Essential");

	 Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/materials/textures", "APKFileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/materials/scripts", "APKFileSystem", "General");
	    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/models", "APKFileSystem", "General");   
    //Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/materials/programs", "APKFileSystem", "General");

   // Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/", "APKFileSystem", "Rocket");
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("/librocket", "APKFileSystem", "Rocket");

	
#endif






}




bool OgreFramework::configuraGraficos()
{


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



    return true;
}



bool OgreFramework::configuraOgre()
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

bool OgreFramework::configuraOIS()
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

	
   //   mInputContext.mMultiTouch = new AndroidMultiTouch();

   //   mInputContext.mKeyboard = new AndroidKeyboard();

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


void OgreFramework::init()
{


#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
   
        mRoot =new Ogre::Root(/*"plugins.cfg"*/);

        configuraOgre();

	    locateResources();

		configuraGraficos();


       mWindow = mRoot->initialise(true, "3D Chess");



	// mWindow = mRoot->createRenderWindow("3D Chess", 800, 600, false, 0);

        configuraOIS();


		startScene();

#else

	
            mRoot = new Ogre::Root();

            configuraOgre();

            mRoot->initialise(false);


			        configuraOIS();

#endif

			         

    //OIS::InputContext mInputContext;

  
    //configureRenderSystem();

    //context->AddEventListener("click", this);

}




void OgreFramework::setupShaderSystem(){


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
bool OgreFramework::initialiseRTShaderSystem(Ogre::SceneManager* sceneMgr)
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
void OgreFramework::destroyRTShaderSystem()
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

