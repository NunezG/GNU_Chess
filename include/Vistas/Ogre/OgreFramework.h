#ifndef __OgreFramework_
#define __OgreFramework_

#define OGRE_STATIC_OctreeSceneManager
#define STATIC_LIB


#define _RTSS_WRITE_SHADERS_TO_DISK
//#define ENABLE_SHADERS_CACHE_SAVE 1
//#define ENABLE_SHADERS_CACHE_LOAD 1


//#include "RocketEventListener.h"


#include <OgreRoot.h>
#include <OgreConfigFile.h>
//#include <Ogre.h>

//#include "MenuRocket.h"
//#include "VistaAjedrez.h"
//#include "VistaAjedrezSolo.h"

#include <OgreWindowEventUtilities.h>


#include "OgreShaderGenerator.h"
#include "OgreRTShaderSystem.h"

#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISMultiTouch.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

#include <OISInputManager.h>
#define OGRE_STATIC_Direct3D9 

#elif OGRE_PLATFORM == OGRE_PLATFORM_ANDROID

#define OGRE_STATIC_GLES2

#endif

#include <OgreStaticPluginLoader.h>


#include "ModeloVista.h"



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
		//	mAccelerometer = 0;
		}

		void capture() const
		{
			if(mKeyboard)
				mKeyboard->capture();
			if(mMouse)
				mMouse->capture();
			if(mMultiTouch)
				mMultiTouch->capture();
		//	if(mAccelerometer)
	     //       mAccelerometer->capture();
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
		//OIS::JoyStick* mAccelerometer;    // context accelerometer device
	};



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





class OgreFramework
{
public:
	   OgreFramework();

    ~OgreFramework(void);


	virtual void init();
	void startScene();

    void locateResources();



	void createCamera(void);
    void createViewports(Ogre::RenderWindow* window);
     Ogre::SceneNode* mTarget;
    Ogre::Camera* mCamera;
	Ogre::Viewport* vp;

	void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);

		
			  void empieza();

	 
		    Ogre::RenderWindow* mWindow;
			//	 OIS::Mouse*    mMouse;
 //   OIS::Keyboard* mKeyboard;
		 
	    Ogre::Root *mRoot;
		Ogre::StaticPluginLoader*  mStaticPluginLoader;
   

	

		Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
								bool configuraOgre();
								virtual bool configuraGraficos();
										 ModeloVista* modeloVista;
										 						      Ogre::SceneManager* mSceneMgr;
												InputContext mInputContext;		// all OIS devices are here

	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

				    OIS::InputManager* mInputManager;

#endif
	
protected:
   
	 //   ModeloVista* modeloVista;

		

		//void createFrameListener();

			void setupShaderSystem();

   bool initialiseRTShaderSystem(Ogre::SceneManager* sceneMgr);
	   void destroyRTShaderSystem();
		


private:
	  
		// Builds an OpenGL-style orthographic projection matrix.
		void buildProjectionMatrix(Ogre::Matrix4& matrix);

  //  int getFPS();
				bool configuraOIS();
	
		
		//	SystemInterfaceOgre3D* ogre_system;
	//	RenderInterfaceOgre3D* ogre_renderer;
	
		
	
	//	typedef std::map< OIS::KeyCode, Rocket::Core::Input::KeyIdentifier > KeyIdentifierMap;
	//	KeyIdentifierMap key_identifiers;

		
		//void destroyScene();
	
			      void windowResized();

				  
		   Ogre::RTShader::ShaderGenerator*   mShaderGenerator;                       // The Shader generator instance.
		   ShaderGeneratorTechniqueResolverListener*       mMaterialMgrListener;           // Shader generator material manager listener.
};

#endif
