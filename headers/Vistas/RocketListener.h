#ifndef ROCKETFRAMELISTENER_H
#define ROCKETFRAMELISTENER_H

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreFrameListener.h>

#include <Rocket/Core/Context.h>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>

#include <Rocket/Core/String.h>

#include <Rocket/Core/Core.h>
#include <Rocket/Debugger.h>

//class RocketApplication;

#include <OgreRoot.h>
#include <OgreConfigFile.h>

#include "MenuRocket.h"
#include "VistaAjedrez.h"
#include "VistaAjedrezSolo.h"


#include <OgreWindowEventUtilities.h>

/**
	@author Peter Curry
 */

class RocketListener
{
	public:
		RocketListener();
		virtual ~RocketListener();

		

    Ogre::Root *mRoot;
    Ogre::RenderWindow* mWindow;
	    ModeloVista* modeloVista;
		  void empieza();

   

	void creaVista();

	
	private:
		    bool configuraGraficos(const char *desiredRenderer);

		BaseVistas* vista;


	
			SystemInterfaceOgre3D* ogre_system;
		RenderInterfaceOgre3D* ogre_renderer;
	



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
