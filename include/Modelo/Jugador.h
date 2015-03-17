#ifndef __Jugador_
#define __Jugador_
#include <algorithm>    // std::for_each
//#include <deque>       // std::vector
#include <iostream>
#include <string>

#include "ModeloTablero.h"
#include "Autorizaciones.h"
//#include "EscenaAjedrez.h"
//#include ".h"


class Jugador
{
public:
    ~Jugador();
    virtual bool esHumano() = 0;
  //  bool jugadorNegras;
		int jaqueMate();
		bool confirmaJugada(int posicion);
		int Jugador::ejecutaJugada();

	bool seleccionaFicha(int posicion);

     virtual bool iniciaTurno();
	 static std::vector<int> jugadasElegidas;
	 std::vector<int> jugadasPermitidas;

protected:
	Jugador(ModeloTablero* modeloAnt, std::string nombreJugador);

	static ModeloTablero* modelo;
  // EscenaAjedrez* escenaMV;
private:
   //bool aplicaCambio();
    std::string getNombre();
    void setNombre( std::string unNombre);
    std::string nombre;
    int* resgistroTablero;
    int alPaso;

};

#endif
