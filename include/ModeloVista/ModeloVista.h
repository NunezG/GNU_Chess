#ifndef __ModeloVista_
#define __ModeloVista_

#include "JugadorArtificial.h"
#include "JugadorHumano.h"
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

    void generaJugadores();
 //   void creaEscenaYModelo();

	  //  ObjetoEscena* getScene();


    Jugador* JugadorActivo;
    EscenaAjedrez* escenaMV;
    Modelo* modelo;
    std::string resolucion;
	bool pantallaCompleta;
   // int dificultad;
    int modoJuego;
	int voltea;

    void aplicaCambio();
		std::string nombres[2];
		bool jugadaElegida();

		    bool getTurnoNegras();

			void cambiaOpciones(std::string difficulty, std::string resolution, bool fullsreen);

	  	void procesaNodoPulsado(std::string nombreNodo);
		   // bool reiniciar;

		void borraJugadores();
		void borraTablero();


private:   
    void traduceTablero();
  //  virtual bool aplicaSeleccion();

    std::vector<Jugador*> jugadores;
    int numJugadores;
    bool mShutDown;
    int numPantalla;
		std::string posInicial;



    
   // bool turnoNegras;
};

#endif
