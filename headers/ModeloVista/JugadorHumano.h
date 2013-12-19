#ifndef __JugadorHumano_
#define __JugadorHumano_

#include "Jugador.h"
//#include "../Modelo/Autorizaciones.h"


class JugadorHumano : public Jugador
{
public:
    ~JugadorHumano();
    JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador);
//bool iniciaTurno();
private:  
    bool esHumano();
   bool casillaSobrevolada(const std::string nombreCasilla);

   bool botonIzquierdo(CEGUI::Vector2<float> pos);
   int jaqueMate();


};




#endif
