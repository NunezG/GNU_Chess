#include "RocketListener.h"

//#include "EventManager.h"
#ifdef USAROCKET

#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#endif
//#include <Shell.h>
//#include "EventHandler.h"
//#include "GameDetails.h"
#include <map>
//#include <Rocket/Core/Context.h>


RocketListener::RocketListener(ModeloVista* modeloV):  BaseVistas(modeloV)   
  //,vista(0)

{

    //modeloVista= modeloV;
    //COUTCOMENTADOstd::cout << "rocketl OGRE"<<std::endl;



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



}

RocketListener::~RocketListener()
{

    // CEGUI::OgreRenderer::destroySystem();
    OIS::InputManager::destroyInputSystem(mInputManager);
    mInputContext.mMouse = 0;
    mInputContext.mKeyboard = 0;
    mInputManager = 0;


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

#ifdef USAROCKET

    Rocket::Core::Shutdown();
#endif
    delete modeloVista;


}




void RocketListener::empieza()
{
    mRoot->startRendering();
    //mRoot->stop
}



/*
// Releases all event handlers registered with the manager.
void RocketListener::Shutdown()
{
    for (EventHandlerMap::iterator i = event_handlers.begin(); i != event_handlers.end(); ++i)
        delete (*i).second;

    event_handlers.clear();
    event_handler = NULL;
}*/
/*
// Registers a new event handler with the manager.
void RocketListener::RegisterEventHandler(const Rocket::Core::String& handler_name)
{
    // Release any handler bound under the same name.
    EventHandlerMap::iterator iterator = event_handlers.find(handler_name);
    if (iterator != event_handlers.end())
        delete (*iterator).second;

    event_handlers[handler_name] = this;
}
*/


/*
// Loads a window and binds the event handler for it.
bool RocketListener::LoadWindow(const Rocket::Core::String& window_name)
{
    // Set the event handler for the new screen, if one has been registered.
    EventHandler* old_event_handler = event_handler;
    EventHandlerMap::iterator iterator = event_handlers.find(window_name);
    if (iterator != event_handlers.end())
        event_handler = (*iterator).second;
    else
        event_handler = NULL;

    // Attempt to load the referenced RML document.
    Rocket::Core::String document_path = Rocket::Core::String("data/") + window_name + Rocket::Core::String(".rml");
    Rocket::Core::ElementDocument* document = context->LoadDocument(document_path.CString());
    if (document == NULL)
    {
        event_handler = old_event_handler;
        return false;
    }

    // Set the element's title on the title; IDd 'title' in the RML.
    Rocket::Core::Element* title = document->GetElementById("title");
    if (title != NULL)
        title->SetInnerRML(document->GetTitle());

    document->Focus();
    document->Show();

    // Remove the caller's reference.
    document->RemoveReference();

    return true;
}
*/
