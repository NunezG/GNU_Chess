#include "RocketFrameListener.h"

//#include "EventManager.h"

//#include <Shell.h>
//#include "EventHandler.h"
//#include "GameDetails.h"
//#include <map>
//#include <Rocket/Core/Context.h>


RocketFrameListener::RocketFrameListener(OgreFramework* fw):  FrameListeners(fw),  
    //,vista(0)
    context(0)
  
{

    //modeloVista= modeloV;
    




}

RocketFrameListener::~RocketFrameListener()
{


    borraVistaActiva();


    framework->mSceneMgr->removeRenderQueueListener( this );


    // Shutdown Rocket.
    
    context->RemoveReference();
    //context->RemoveEventListener

    delete ogre_system;
    ogre_system = NULL;

    delete ogre_renderer;
    ogre_renderer = NULL;


    // Rocket::Core::SetRenderInterface(0);
    //Rocket::Core::SetSystemInterface(0);


    // Rocket::Core::Shutdown();



}

// Called from Ogre before a queue group is rendered.
void RocketFrameListener::renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation))
{

    if (queueGroupId == Ogre::RENDER_QUEUE_OVERLAY && Ogre::Root::getSingleton().getRenderSystem()->_getViewport()->getOverlaysEnabled())
    {

        context->Update();

        // #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        configureRenderSystem();
        //	#endif
        // #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        context->Render();
        ogre_renderer->hecho = true;

        //#endif



    }


}

// Called from Ogre after a queue group is rendered.
void RocketFrameListener::renderQueueEnded(Ogre::uint8 ROCKET_UNUSED(queueGroupId), const Ogre::String& ROCKET_UNUSED(invocation), bool& ROCKET_UNUSED(repeatThisInvocation))
{


}
/*
// Builds an OpenGL-style orthographic projection matrix.
void FrameListeners::buildProjectionMatrix(Ogre::Matrix4& projection_matrix)
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
*/


// Configures Ogre's rendering system for rendering Rocket.
void RocketFrameListener::configureRenderSystem()
{



    Ogre::RenderSystem* render_system = Ogre::Root::getSingleton().getRenderSystem();

    // Set up the projection and view matrices.
    




    // buildProjectionMatrix(projection_matrix);

    //   render_system->_setProjectionMatrix(projection_matrix);
    //  render_system->_setViewMatrix(Ogre::Matrix4::IDENTITY);




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
    // render_system->unbindGpuProgram(Ogre::GPT_FRAGMENT_PROGRAM);
    // render_system->unbindGpuProgram(Ogre::GPT_VERTEX_PROGRAM);


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
    // render_system->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_POINT);
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






bool RocketFrameListener::configuraRocket()
{

    ogre_system = NULL;
    ogre_renderer = NULL;
    // Rocket initialisation.


    ogre_renderer = new RenderInterfaceOgre3D(framework->mWindow->getWidth(), framework->mWindow->getHeight());

    //ogre_renderer->setCustomProjectionMatrix(projection_matrix);

    Rocket::Core::SetRenderInterface(ogre_renderer);


    ogre_system = new SystemInterfaceOgre3D();
    Rocket::Core::SetSystemInterface(ogre_system);



    Rocket::Core::Initialise();


    Rocket::Controls::Initialise();




    context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(framework->mWindow->getWidth(), framework->mWindow->getHeight()));

    Rocket::Debugger::Initialise(context);

    context->SetDimensions( Rocket::Core::Vector2i( framework->mWindow->getWidth(), framework->mWindow->getHeight() ) );


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


void RocketFrameListener::init()
{


    // Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        //framework->init();


    // Add the application as a listener to Ogre's render queue so we can render during the overlay.
    framework->mSceneMgr->addRenderQueueListener(this);

    configuraRocket();

}


void RocketFrameListener::borraVistaActiva()
{

    context->RemoveEventListener("click", vistaActiva);
    context->UnloadAllDocuments();


    FrameListeners::borraVistaActiva();


}

void RocketFrameListener::setVistaActiva(RocketEventListener* vista)
{

    FrameListeners::setVistaActiva(vista);

    vistaActiva->BuildKeyMaps();

}

/*
// Releases all event handlers registered with the manager.
void RocketFrameListener::Shutdown()
{
    for (EventHandlerMap::iterator i = event_handlers.begin(); i != event_handlers.end(); ++i)
        delete (*i).second;

    event_handlers.clear();
    event_handler = NULL;
}*/
/*
// Registers a new event handler with the manager.
void RocketFrameListener::RegisterEventHandler(const Rocket::Core::String& handler_name)
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
bool RocketFrameListener::LoadWindow(const Rocket::Core::String& window_name)
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
