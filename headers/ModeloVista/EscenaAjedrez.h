#ifndef __EscenaAjedrez_
#define __EscenaAjedrez_

//#include <OgreCamera.h>
//#include <OgreLogManager.h>
//#include <OgreViewport.h>
//#include <OgreRenderWindow.h>
//#include <OgreRoot.h>
/*
#include <CEGUI/Vector.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/System.h>
*/
#include "TableroMV.h"

class  EscenaAjedrez
{
public:
    EscenaAjedrez();
    ~EscenaAjedrez(void);
    void setModoCamara(bool modo);
    bool getModoCamara();
    void noMueveCamara();
    bool getCamaraIzquierda();
    bool getCamaraDerecha();
    void setCamaraIzquierda();
    void setCamaraDerecha();



	void createSceneMV();
    void createCamera(void);

    void apagaVentanaEmergente();
    void muestraVentanaEmergente(std::string nombreLayout);

    bool modoVS;
		 std::string nombreActivo;
		 		   int rotaCamara;

		  

	    TableroMV* getTablero();

private:
  //  CEGUI::Window *ventanaEmergente;
    bool camaraIzquierda;
    bool camaraDerecha;
    bool modoCamara;
    //ObjetoEscena* tablero;
	TableroMV* tablero;

};

#endif
