#ifndef __BaseVistas_
#define __BaseVistas_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

//#include <CEGUI-CEGUIUI/CEGUISystem.h>
//#include <CEGUI-CEGUIUI/CEGUIWindow.h>
//#include <CEGUI-CEGUIUI/CEGUIMinizipResourceProvider.h>
//#include <CEGUI-CEGUIUI/CEGUIEventSet.h>
//#include <CEGUI/RendererModulesCEGUIGL/CEGUIOpenGLRenderer.h>
#include <CEGUI/CEGUI.h>


#include <CEGUI/RendererModules/Ogre/Renderer.h>


#include "../ModeloVista/EscenaAjedrez.h"
#include "../ModeloVista/ModeloVista.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>


class BaseVistas: public OIS::KeyListener, public OIS::MouseListener, public Ogre::FrameListener
{
public:
    ~BaseVistas(void);
    void empieza();

    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;
    Ogre::Root *mRoot;
    Ogre::RenderWindow* mWindow;

protected:
    BaseVistas(ModeloVista* modeloV, std::string label);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    ModeloVista* modeloVista;
    CEGUI::System* sys;

private:
    void windowResized();
  //  int getFPS();
    bool configuraGraficos(const char *desiredRenderer);
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    OIS::InputManager* mInputManager;
    CEGUI::OgreRenderer* renderer;

};

#endif
