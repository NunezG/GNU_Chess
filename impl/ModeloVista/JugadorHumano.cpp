#include "../../headers/ModeloVista/JugadorHumano.h"

JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    Jugador(miEscena, modelo, nombreJugador)
{   
}

JugadorHumano::~JugadorHumano()
{ 
}

bool JugadorHumano::botonIzquierdo(CEGUI::Vector2<float> pos)
{

    Tablero* tablero = escena->getTablero();

 //   if (tablero->getCasillaSeleccionada() != NULL)
   // {  // Si habia alguno seleccionado...
        //Ficha* ficha = static_cast<Ficha*>(tablero->getCasillaSeleccionada()->getHijo(0));
        // ficha->getNodoOgre()->showBoundingBox(false);
   //     tablero->setCasillaSeleccionada(-1);
 //   }

    Casilla* casilla = static_cast<Casilla*>(tablero->getHijo(escena->encuentraCasillaSobrevolada(pos)));

    if (casilla != NULL && !casilla->sinHijos())
    {
        Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));
        if ((tablero->getTurnoNegras()
             && ficha->esNegra)
                || (!tablero->getTurnoNegras()
                    && !ficha->esNegra))
        {
            tablero->setCasillaSeleccionada(casilla);

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

