#ifndef __ModeloVista_
#define __ModeloVista_

#include "JugadorArtificial.h"
#include "JugadorHumano.h"


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
    void creaEscenaYModelo();

    Jugador* JugadorActivo;
    EscenaAjedrez* escena;
    Modelo* modelo;
    std::string resolucion;
	bool pantallaCompleta;
    int dificultad;
    int modoJuego;

    void aplicaCambio();
		std::string nombres[2];

private:   
    void traduceTablero();
  //  virtual bool aplicaSeleccion();

    std::vector<Jugador*> jugadores;
    int numJugadores;
    bool mShutDown;
    int numPantalla;
    bool reiniciar;
};

#endif
