#ifndef __MenuRocket_
#define __MenuRocket_

#include "BaseListeners.h"

class MenuRocket : public BaseListeners
{
public:
    MenuRocket(RocketListener* vistaOgre);//Ventana* mFrameListener);
    ~MenuRocket(void);

   // CEGUI::FrameWindow* createGUI(void);
    //bool salir();
    bool pantallaInicio();



			virtual bool keyReleased(const OIS::KeyEvent& e);


				void createOverlay();

	void ProcessEvent(Rocket::Core::Event& event);


	





private:
  
	/*
	bool botonSalir(const CEGUI::EventArgs    &e);
    bool botonJuegoTurnos(const CEGUI::EventArgs &e);
    bool botonJuegoSolo(const CEGUI::EventArgs &e);
    bool botonConfig(const CEGUI::EventArgs &e);
    bool botonVolver(const CEGUI::EventArgs &e);
    bool botonAplicarCambios(const CEGUI::EventArgs &e);
    bool sobrevuelaLista(CEGUI::Listbox *lista);
    bool seleccionaElementoLista(CEGUI::Listbox *lista);
   // bool sobrevuelaListaBlancas(const CEGUI::EventArgs &e);
   // bool sobrevuelaListaNegras(const CEGUI::EventArgs &e);
    bool sobrevuelaListaResoluciones(const CEGUI::EventArgs &e);
    bool seleccionaResolucion(const CEGUI::EventArgs &e);
    bool sobrevuelaListaDificultad(const CEGUI::EventArgs &e);
    bool seleccionaDificultad(const CEGUI::EventArgs &e);
    bool seleccionaBlancas(const CEGUI::EventArgs &e);
    bool seleccionaNegras(const CEGUI::EventArgs &e);

    void creaMenuDesplegable(CEGUI::Event::Subscriber eventoAlSobrevolar,CEGUI::Event::Subscriber eventoAlPulsar, std::vector<std::string> listaElementos, CEGUI::Listbox* listaReal, std::string preSeleccionado);

    CEGUI::Window* ventanaConfig;
    CEGUI::Listbox *listaResoluciones;
    CEGUI::Listbox *listaDificultades;
  //  CEGUI::Listbox *listaBlancas;
  //  CEGUI::Listbox *listaNegras;

	CEGUI::ToggleButton* pantallaCompleta;

	*/



	    bool pantallaConfig();

};

#endif
