#ifndef __Escena_
#define __Escena_

#include <OgreCamera.h>
#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
/*
#include <CEGUI/Vector.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/System.h>
*/
//#include "Tablero.h"
#include "ObjetoOgre.h"

#include "../ModeloVista/EscenaAjedrez.h"

class  Escena
{
public:
    Escena();
    ~Escena(void);
   // Tablero* getTablero();
    void setModoCamara(bool modo);
    bool getModoCamara();
    void noMueveCamara();
    bool getCamaraIzquierda();
    bool getCamaraDerecha();
    void setCamaraIzquierda();
    void setCamaraDerecha();

    std::string encuentraCasillaSobrevolada(int posx, int posy);

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

		 
    void creaTableroYCasillas(Ogre::SceneManager* sceneMgr);
	//void creaPiezas();
	void generaEscena(ObjetoEscena* nodoEscena, ObjetoOgre* nodoOgre);
		

protected:
	EscenaAjedrez* escenaMV;
	    ObjetoOgre* tablero;

private:
  //  CEGUI::Window *ventanaEmergente;
    Ogre::RenderWindow* mWindow;
    bool camaraIzquierda;
    bool camaraDerecha;
    bool modoCamara;
    Ogre::SceneNode* mTarget;
    Ogre::Camera* mCamera;
     Ogre::RaySceneQuery *mRaySceneQuery;
	 	ObjetoEscena* objEscena;

};

#endif
