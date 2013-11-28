#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>

#include <CEGUI/Vector.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/System.h>

#include "Tablero.h"

class  EscenaAjedrez
{
public:
    EscenaAjedrez();
    ~EscenaAjedrez(void);
    Tablero* getTablero();
    void setModoCamara(bool modo);
    bool getModoCamara();
    void noMueveCamara();
    bool getCamaraIzquierda();
    bool getCamaraDerecha();
    void setCamaraIzquierda();
    void setCamaraDerecha();

    std::string encuentraCasillaSobrevolada(CEGUI::Vector2<float> mCursorPosition);

    void DistanciaCamara(int distanciaRelativa);
    void rotacionCamara(Ogre::Degree angulo);
    void createScene();
    void createCamera(void);
    void createViewports(Ogre::RenderWindow* window);

    void apagaVentanaEmergente();
    void muestraVentanaEmergente(std::string nombreLayout);

    Ogre::SceneManager* mSceneMgr;
    bool modoVS;
		 std::string nombreActivo;

private:
    CEGUI::Window *ventanaEmergente;
    Ogre::RenderWindow* mWindow;
    bool camaraIzquierda;
    bool camaraDerecha;
    bool modoCamara;
    Ogre::SceneNode* mTarget;
    Ogre::Camera* mCamera;
    Tablero* tablero;
     Ogre::RaySceneQuery *mRaySceneQuery;
};

#endif
