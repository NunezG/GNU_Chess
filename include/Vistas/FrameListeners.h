#ifndef __FrameListeners_
#define __FrameListeners_

#define OGRE_STATIC_OctreeSceneManager
#define STATIC_LIB


#define _RTSS_WRITE_SHADERS_TO_DISK
//#define ENABLE_SHADERS_CACHE_SAVE 1
//#define ENABLE_SHADERS_CACHE_LOAD 1
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISMultiTouch.h>
#include <OISJoyStick.h>


#include "ModeloVista.h"


#include <OgreRoot.h>
#include <OgreConfigFile.h>
//#include <Ogre.h>

//#include "MenuRocket.h"
//#include "VistaAjedrez.h"
//#include "VistaAjedrezSolo.h"

#include <OgreWindowEventUtilities.h>


#include "RTShaderSystem/OgreShaderGenerator.h"
#include "RTShaderSystem/OgreRTShaderSystem.h"


//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define USAROCKET
//#endif

#ifdef USAROCKET
#include <Rocket/Core/Context.h>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>

#include <Rocket/Core/String.h>

#include <Rocket/Core/Core.h>
#include <Rocket/Debugger.h>



#include "RenderInterfaceOgre3D.h"
#include "SystemInterfaceOgre3D.h"
#endif


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define OGRE_STATIC_GL
#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#define OGRE_STATIC_GLES2
#endif

#include <OgreStaticPluginLoader.h>



//#ifdef INCLUDE_RTSHADER_SYSTEM

/** This class demonstrates basic usage of the RTShader system.
        It sub class the material manager listener class and when a target scheme callback
        is invoked with the shader generator scheme it tries to create an equivalent shader
        based technique based on the default technique of the given material.
    */
class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
{
public:

    ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
    {
        mShaderGenerator = pShaderGenerator;
    }

    // This is the hook point where shader based technique will be created.
    //        It will be called whenever the material manager won't find appropriate technique
     //       that satisfy the target scheme name. If the scheme name is out target RT Shader System
    //        scheme name we will try to create shader generated technique for it.
    ///
    virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
                                                  const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex,
                                                  const Ogre::Renderable* rend)
    {
        Ogre::Technique* generatedTech = NULL;

        // Case this is the default shader generator scheme.
        if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
        {
            bool techniqueCreated;

            // Create shader generated technique for this material.
            techniqueCreated = mShaderGenerator->createShaderBasedTechnique(
                        originalMaterial->getName(),
                        Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
                        schemeName);

            // Case technique registration succeeded.
            if (techniqueCreated)
            {
                // Force creating the shaders for the generated technique.
                //MIRA A VER COMENTANDO ESTO!!!!
				mShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());

                // Grab the generated technique.
                Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

                while (itTech.hasMoreElements())
                {
                    Ogre::Technique* curTech = itTech.getNext();

                    if (curTech->getSchemeName() == schemeName)
                    {
                        generatedTech = curTech;
                        break;
                    }
                }
            }
        }

        return generatedTech;
    }

protected:
    Ogre::RTShader::ShaderGenerator*        mShaderGenerator;                       // The shader generator instance.
};
//#endif // INCLUDE_RTSHADER_SYSTEM





/*=============================================================================
	| Utility structure for passing OIS devices. Does not own them.
	=============================================================================*/
	struct InputContext
	{
		InputContext()
		{
			mKeyboard = 0;
			mMouse = 0;
			mMultiTouch = 0;
			mAccelerometer = 0;
		}

		void capture() const
		{
			if(mKeyboard)
				mKeyboard->capture();
			if(mMouse)
				mMouse->capture();
			if(mMultiTouch)
				mMultiTouch->capture();
			if(mAccelerometer)
	            mAccelerometer->capture();
		}

		bool isKeyDown(OIS::KeyCode key) const
		{
			return mKeyboard && mKeyboard->isKeyDown(key);
		}

		bool getCursorPosition(Ogre::Real& x, Ogre::Real& y) const
		{
			// prefer mouse
			if(mMouse)
			{
				x = (Ogre::Real)mMouse->getMouseState().X.abs;
				y = (Ogre::Real)mMouse->getMouseState().Y.abs;
				return true;
			}
			
			// than touch device
			if(mMultiTouch)
			{
	            std::vector<OIS::MultiTouchState> states = mMultiTouch->getMultiTouchStates();
		        if(states.size() > 0)
		        {
		        	x = (Ogre::Real)states[0].X.abs;
		        	y = (Ogre::Real)states[0].Y.abs;
		        	return true;
			    }
			}

			// fallback
			x = y = 0.0;
			return false;
		}

		OIS::Keyboard* mKeyboard;         // context keyboard device
		OIS::Mouse* mMouse;               // context mouse device
		OIS::MultiTouch* mMultiTouch;     // context multitouch device
		OIS::JoyStick* mAccelerometer;    // context accelerometer device
	};


class FrameListeners : public Ogre::RenderQueueListener, public Ogre::FrameListener
{
public:
	   FrameListeners(ModeloVista* modeloV);

    ~FrameListeners(void);


	void init();
    void locateResources();



	void createCamera(void);
    void createViewports(Ogre::RenderWindow* window);
     Ogre::SceneNode* mTarget;
    Ogre::Camera* mCamera;
	//Ogre::Ray getCameraToViewportRay();
	 ModeloVista* modeloVista;

	void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);

		// FrameListener interface.
		virtual bool frameStarted(const Ogre::FrameEvent& evt);


    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	 #ifdef USAROCKET
			/// Called from Ogre before a queue group is rendered.
	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
	/// Called from Ogre after a queue group is rendered.
    virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);
Rocket::Core::Context* context;

		bool configuraRocket();
		typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
			KeyIdentifierMap key_identifiers;
#endif
		    Ogre::RenderWindow* mWindow;
			//	 OIS::Mouse*    mMouse;
 //   OIS::Keyboard* mKeyboard;
		 
	    Ogre::Root *mRoot;
							InputContext mInputContext;		// all OIS devices are here
		Ogre::StaticPluginLoader*  mStaticPluginLoader;
   

	

		Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
								bool configuraOgre();
								bool configuraGraficos();

protected:
   
	 //   ModeloVista* modeloVista;

			

				    OIS::InputManager* mInputManager;

		 #ifdef USAROCKET
	// Configures Ogre's rendering system for rendering Rocket.
		void configureRenderSystem();

		#endif

		
	
		
						      Ogre::SceneManager* mSceneMgr;

		//void createFrameListener();

			void setupShaderSystem();

   bool initialiseRTShaderSystem(Ogre::SceneManager* sceneMgr);
	   void destroyRTShaderSystem();
		
private:
	  
	
		// Builds an OpenGL-style orthographic projection matrix.
		void buildProjectionMatrix(Ogre::Matrix4& matrix);

  //  int getFPS();
				bool configuraOIS();
		 #ifdef USAROCKET
			SystemInterfaceOgre3D* ogre_system;
		RenderInterfaceOgre3D* ogre_renderer;
			void BuildKeyMaps();
		int GetKeyModifierState();
#endif
		
		//	SystemInterfaceOgre3D* ogre_system;
	//	RenderInterfaceOgre3D* ogre_renderer;
	
		bool running;
		
	
	//	typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
	//	KeyIdentifierMap key_identifiers;

		
		//void destroyScene();
	
			      void windowResized();

				  
		   Ogre::RTShader::ShaderGenerator*   mShaderGenerator;                       // The Shader generator instance.
		   ShaderGeneratorTechniqueResolverListener*       mMaterialMgrListener;           // Shader generator material manager listener.
};

#endif
