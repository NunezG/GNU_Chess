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
#include "EscenaAjedrez.h"

#include "ObjetoOgre.h"
//#include "RocketFrameListener.h"

//#include "EscenaAjedrez.h"

class  Escena
{
public:
    Escena(EscenaAjedrez* sceneModel);
    ~Escena(void);
   // Tablero* getTablero();
    void setModoCamara(bool modo);
    bool getModoCamara();
    void noMueveCamara();
    bool getCamaraIzquierda();
    bool getCamaraDerecha();
    void setCamaraIzquierda();
    void setCamaraDerecha();


      //  Ogre::Camera* camera;

    void createScene();
    

    void apagaVentanaEmergente();
    void muestraVentanaEmergente(std::string nombreLayout);

    Ogre::SceneManager* sceneMgr;
    bool modoVS;
		 std::string nombreActivo;

		 
  //  void creaTableroYCasillas();
	//void creaPiezas();
	void generaEscena();
		
	//ModeloVista* modeloVista;
protected:
	//EscenaAjedrez* escenaMV;
	    ObjetoOgre* objetoInicio;
		
		std::vector<ObjetoOgre*> listaNodos;
		//[36] ;


private:

	EscenaAjedrez* modeloEscena;

  //  CEGUI::Window *ventanaEmergente;
  //  Ogre::RenderWindow* mWindow;
    bool camaraIzquierda;
    bool camaraDerecha;
    bool modoCamara;
   
	 //	ObjetoEscena* objEscena;

};

#endif
