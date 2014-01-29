#include "../../headers/Vistas/RocketListener.h"
//#include <Rocket/Core/Context.h>

//#include "RocketApplication.h"

RocketListener::RocketListener()  
{
	
		ogre_system = NULL;
		ogre_renderer = NULL;

	// Switch the working directory to Ogre's bin directory.
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	//char path[MAX_PATH];
	//rocket_path = getcwd(path, MAX_PATH);
	//rocket_path += "/../../";

	// Normalise the path. This path is used to specify the resource location (see line 56 below).
	//_fullpath(path, rocket_path.CString(), MAX_PATH);
	//rocket_path = Rocket::Core::String(path).Replace("\\", "/");

	// The sample path is the path to the Ogre3D sample directory. All resources are loaded
	// relative to this path.
	//sample_path = getcwd(path, MAX_PATH);
	//sample_path += "/../Samples/basic/ogre3d/";
//#if OGRE_DEBUG_MODE
//	chdir((Ogre::String(getenv("OGRE_HOME")) + "\\bin\\debug\\").c_str());
//#else
//	chdir((Ogre::String(getenv("OGRE_HOME")) + "\\bin\\release\\").c_str());
//#endif
//#endif


	//mWindow = window;


		modeloVista = new ModeloVista();
    //INICIA OGRE
    mRoot =new Ogre::Root("plugins.cfg");
	  configuraGraficos("OpenGL Rendering Subsystem");
    mWindow = mRoot->initialise(true,"3D CHESS");
	 
    
	//mInputManager->inpu

    //Set initial mouse clipping size
				 
    //INICIA CEGUI
/*    CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);

    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");

    CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");

    sys = CEGUI::System::getSingletonPtr();

    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

   // sys->getDefaultGUIContext().getMouseCursor().se
          //  getMouseCursor().setDefaultImage(sheet->getMouseCursor());

    // CEGUI::MouseCursor::getSingleton().setImage(sys->getDefaultMouseCursor());

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet= wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    // sys->setGUISheet(sheet);
    sys->getDefaultGUIContext().setRootWindow( sheet );
    //CEGUI::System::getSingleton().getDefaultGUIContext.getrgetRenderer();

//sys->getDefaultGUIContext().
    sheet->setMouseCursor("Vanilla-Images/MouseArrow");

  // CEGUI::System::getSingleton().getDefaultGUIContext().setDefault
   // CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage("Vanilla-Images/MouseArrow");
   // CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getImage()-

   sys->getDefaultGUIContext().getMouseCursor().setImage(sheet->getMouseCursor());
    windowResized();

    //sys->renderGUI();
    sys->getRenderer()->beginRendering();

	*/

	//INICIA ROCKET??
							std::cout << "INICIA ROCKET"<<std::endl;
														std::cout << mWindow->getWidth()<<std::endl;
							std::cout << mWindow->getHeight()<<std::endl;

        //Register as a Window listener
        Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	

			// Rocket initialisation.
	ogre_renderer = new RenderInterfaceOgre3D(mWindow->getWidth(), mWindow->getHeight());
	Rocket::Core::SetRenderInterface(ogre_renderer);
									std::cout << "TRES"<<std::endl;

	ogre_system = new SystemInterfaceOgre3D();
	Rocket::Core::SetSystemInterface(ogre_system);





									std::cout << "Uno"<<std::endl;
	
		Rocket::Core::Initialise();
											std::cout << "UNODOS"<<std::endl;

	Rocket::Controls::Initialise();
								std::cout << "FIN INICIA ROCKET"<<std::endl;


}

RocketListener::~RocketListener()
{
	
   // CEGUI::OgreRenderer::destroySystem();
    
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

	
	delete ogre_system;
	ogre_system = NULL;

	delete ogre_renderer;
	ogre_renderer = NULL;
		Rocket::Core::Shutdown();
		    delete modeloVista;


}







bool RocketListener::configuraGraficos(const char *desiredRenderer)
{
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
    
    //CONFIGUREOPENGL
    Ogre::RenderSystem *renderSystem;
    bool ok = false;
    
    Ogre::RenderSystemList renderers =
            Ogre::Root::getSingleton().getAvailableRenderers();
    
    // See if the list is empty (no renderers available)
    if(renderers.empty())
        return false;
    
    for(Ogre::RenderSystemList::iterator it = renderers.begin();
        it != renderers.end(); it++)
    {
        renderSystem = *it;
        if(strstr(renderSystem->getName().c_str(), desiredRenderer))
        {
            ok = true;
            break;
        }
    }
    if(!ok)
    {
        // We still don't have a renderer; pick
        // up the first one from the list
        renderSystem = *renderers.begin();
    }
    Ogre::Root::getSingleton().setRenderSystem(renderSystem);
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
    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    return true;
}


void RocketListener::empieza()
{
    mRoot->startRendering();
}


void RocketListener::creaVista()
{
	delete vista;
				std::cout << "creaVista "<<std::endl;

	

    if (modeloVista->getNumPantalla() == 0)
	{
			std::cout << "1 "<<std::endl;
		vista = new VistaAjedrez(modeloVista, mWindow);
			    std::cout << "escensa "<<std::endl;

				   vista->createScene();

	}else
        {
            if (modeloVista->getNumPantalla() == 1)
               vista =  new VistaAjedrez(modeloVista, mWindow);

            else if (modeloVista->getNumPantalla() == 2) //EL CONTRUCTOR DE BASEVISTAS CONFIGURA OPENGL, INICIA mWINDOW, INICIA OIS Y CEGUI
               vista =  new VistaAjedrezSolo(modeloVista, mWindow);
                   
        }



	  //LISTENERS
        mRoot->addFrameListener(vista);

	 
}


