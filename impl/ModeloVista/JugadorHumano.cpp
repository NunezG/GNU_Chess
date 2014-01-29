#include "../../headers/ModeloVista/JugadorHumano.h"

JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    Jugador(miEscena, modelo, nombreJugador)
{   
}

JugadorHumano::~JugadorHumano()
{ 
}

bool JugadorHumano::botonIzquierdo(ObjetoEscena* obj)
{

					std::cout << "botonIzquierdo de jugadorhumano "<<std::endl;
/*
    if (escena->getTablero()->getCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        Ficha* ficha = static_cast<Ficha*>(escena->getTablero()->getCasillaSeleccionada()->getHijo(0));
       //ficha->getNodoOgre()->showBoundingBox(false);
        escena->getTablero()->setCasillaSeleccionada(-1);
    }
	
	*/
    if (obj != NULL && !obj->sinHijos())
    {

        Ficha* ficha = static_cast<Ficha*>(obj->getHijo(0));
        if ((modelo->tableroModelo->turnoN
             && ficha->mask == NEGRAS)
                || (!modelo->tableroModelo->turnoN
                    && ficha->mask == BLANCAS))
        {
            escena->getTablero()->setCasillaSeleccionada(static_cast<Casilla*>(obj));

            // ficha->getNodoOgre()->showBoundingBox(true);
            return true;
        }
    }
    return false;
}


bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
    if (escena->getTablero()->getCasillaSeleccionada() != NULL && Jugador::casillaSobrevolada(nombreCasilla))
    {
        Casilla* nodoSeleccionado = escena->getTablero()->getCasillaSeleccionada();

        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;

        Ficha *mFicha = static_cast<Ficha*>(nodoSeleccionado->getHijo(0));
        tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   tableroModelo->casillasInt = tablero->traduceTablero();
  
        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        modelo->tableroModelo->jugada[1] = 24 + (escena->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escena->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;

        //AUTORIZA
        int resultado = Autorizaciones::autorizaCasilla(tipo);

        if (resultado == 1)
        {
            modelo->jugadaElegida[0] = modelo->tableroModelo->jugada[0];
            modelo->jugadaElegida[1] = modelo->tableroModelo->jugada[1];

            // CASILLA AUTORIZADA
            escena->getTablero()->getCasillaSobrevolada()->iluminaCasilla();
            return true;
        }
        else
        {
            // CASILLA PROHIBIDA
            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;
            modelo->jugadaElegida[0] = -1;
            modelo->jugadaElegida[1] = -1;


            if (resultado == 2)
            {
                //JAQUE AL SOBREVOLAR CASILLA
                escena->muestraVentanaEmergente("Jaque");
            }
            return false;
        }
    }
    else return false;
}

bool JugadorHumano::esHumano()
{
    return true;
}

