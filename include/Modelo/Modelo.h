#ifndef __Modelo_
#define __Modelo_

//#include "ArbolBusqueda.h"
//#include "Autorizaciones.h"
#include "JugadorArtificial.h"
#include "JugadorHumano.h"

class Modelo 
{
public:
    ~Modelo(void);
    //Singleton
    static Modelo* getSingletonPtr();
			  		static std::string posInicial;


    std::string nombres[2];

  //  void mueveTablero();

    static ModeloTablero* mainModelBoard;
	//static ModeloTablero* mainModelBoard;

	bool jugadaElegida();

	std::string listaCambios;

	void cambiaTurno();


	int getTipoJuego();
	void setTipoJuego(int tipo);

	int tipoJuego;

	Jugador* JugadorActivo;
	std::vector<Jugador*> jugadores;


	void borraJugadores();

	void generaJugadores();


	int dificultad;

private:
	int jaqueMate();

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);
};

#endif
