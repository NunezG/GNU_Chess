#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
//#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:
    ~JugadorHumano();
	JugadorHumano(ModeloTablero* modelo, std::string nombreJugador);
//bool iniciaTurno();
//	bool confirmaJugada(int posicion);
private:  
    bool esHumano();
  // bool casillaSobrevolada(const std::string nombreCasilla);

  //bool botonIzquierdo(ObjetoEscena* obj);
   int jaqueMate();

 

};




#endif
