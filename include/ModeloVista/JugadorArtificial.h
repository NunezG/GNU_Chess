#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include "../Modelo/ArbolBusqueda.h"


class JugadorArtificial : public Jugador
{
public:
    ~JugadorArtificial();
    JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador);
    bool aplicaSeleccion();

bool iniciaTurno();

private:
    bool botonIzquierdo(ObjetoEscena* obj);
    bool mueveRaton(std::string casilla);
    bool esHumano();
};


#endif
