#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
//#include <deque>       // std::vector
#include <iostream>
#include <string>

#include "../Modelo/Modelo.h"
#include "../Modelo/Autorizaciones.h"
#include "EscenaAjedrez.h"

class Jugador
{
public:
    ~Jugador();
    virtual bool casillaSobrevolada(const std::string nombreCasilla);
    virtual bool esHumano() = 0;
  //  bool jugadorNegras;
    virtual bool botonDerecho() = 0;
    virtual bool botonIzquierdo(CEGUI::Vector2<float> pos) = 0;
		int jaqueMate();
	virtual bool aplicaSeleccion();


     virtual bool iniciaTurno();

protected:
    Jugador(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador);

    Modelo* modelo;
   EscenaAjedrez* escena;
private:
   //bool aplicaCambio();
    std::string getNombre();
    void setNombre( std::string unNombre);
    std::string nombre;
    int* resgistroTablero;
    int alPaso;

};

#endif
