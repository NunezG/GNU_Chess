#ifndef __JugadorArtificial_
#define __JugadorArtificial_

#include "Jugador.h"
#include <thread>
#include "ArbolBusqueda.h"


class JugadorArtificial : public Jugador
{
public:
    ~JugadorArtificial();
    JugadorArtificial(ModeloTablero* modelo, std::string nombreJugador);
    //bool aplicaSeleccion();
	static std::vector<int> JugadorArtificial::resultadoArbol;
	static int dificultad;
	static void *lanzaArbol();
	void lanzaThread();

bool iniciaTurno();

private:
   // bool botonIzquierdo(ObjetoEscena* obj);
    bool mueveRaton(std::string casilla);
    bool esHumano();
};


#endif
