#ifndef RocketListener_H
#define RocketListener_H

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreFrameListener.h>

#ifdef USAROCKET

#include <Rocket/Core/Context.h>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>

#include <Rocket/Core/String.h>

#include <Rocket/Core/Core.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Debugger.h>
#endif
//class RocketApplication;

#include <OgreRoot.h>
#include <OgreConfigFile.h>

//#include "MenuRocket.h"
//#include "VistaAjedrez.h"
//#include "VistaAjedrezSolo.h"
#include "BaseVistas.h"

#include <OgreWindowEventUtilities.h>


class RocketListener: public BaseVistas
{
	public:
		RocketListener(ModeloVista* modeloV);
		virtual ~RocketListener();

		

  //  Ogre::RenderWindow* mWindow;
	   // ModeloVista* modeloVista;
		  void empieza();

   







	

	/// Releases all event handlers registered with the manager.
	//static void Shutdown();

	/// Registers a new event handler with the manager.
	/// @param[in] handler_name The name of the handler; this must be the same as the window it is handling events for.
	/// @param[in] handler The event handler.
	//static void RegisterEventHandler(const Rocket::Core::String& handler_name);

	/// Processes an event coming through from Rocket.
	/// @param[in] event The Rocket event that spawned the application event.
	/// @param[in] value The application-specific event value.
	
	/// Loads a window and binds the event handler for it.
	/// @param[in] window_name The name of the window to load.
	//static bool LoadWindow(const Rocket::Core::String& window_name);

	

// The game's element context (declared in main.cpp).
//Rocket::Core::Context* context;

// The event handler for the current screen. This may be NULL if the current screen has no specific functionality.

//EventHandler* event_handler = NULL;

// The event handlers registered with the manager.
//typedef std::map< Rocket::Core::String, EventHandler* > EventHandlerMap;
//EventHandlerMap event_handlers;




	
	private:

	





		// OIS::Mouse*    mMouse;
       //  OIS::Keyboard* mKeyboard;

	
		 
		// Absolute path to the libRocket directory.
		//Rocket::Core::String rocket_path;
		// Absolute path to the Ogre3d sample directory;
		//Rocket::Core::String sample_path;
		// Ogre::RenderWindow* mWindow;
		//Rocket::Core::Context* context;

};

#endif
