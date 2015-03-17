#ifndef __ModeloVista_
#define __ModeloVista_

//#include "JugadorArtificial.h"
//#include "JugadorHumano.h"
#include "EscenaAjedrez.h"
//#include "Casilla.h"

class  ModeloVista
{
public:
    ModeloVista();
    ~ModeloVista(void);

    void setNumPantalla(int pantalla);
    void setApagar(bool apaga);
    int getNumPantalla();
    bool getApagar();
	
 //   void creaEscenaYModelo();

	  //  ObjetoEscena* getScene();
	//virtual bool casillaSobrevolada(const std::string nombreCasilla);

    EscenaAjedrez* escenaMV;
    Modelo* modelo;
    std::string resolucion;
	bool pantallaCompleta;
   // int dificultad;
    int modoJuego;
	int voltea;

	void compruebaCambio();
		bool iniciaModelo();

		    bool getTurnoNegras();

			void cambiaOpciones(std::string difficulty, std::string resolution, bool fullsreen);

			bool procesaNodoPulsado(std::string nombreNodo);
		   // bool reiniciar;

		void borraTablero();
		bool apagaCasillas();
		//virtual bool botonIzquierdo(ObjetoEscena* obj) = 0;


private:   
    void traduceTablero();
  //  virtual bool aplicaSeleccion();

    bool mShutDown;
    int numPantalla;
		std::string posInicial;



    
   // bool turnoNegras;
};

#endif
