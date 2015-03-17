#include "JugadorHumano.h"

JugadorHumano::JugadorHumano(ModeloTablero* modelo, std::string nombreJugador) :
Jugador(modelo, nombreJugador)
//Jugador::modelo = modelo;
{ 

}

JugadorHumano::~JugadorHumano()
{ 
}

//bool JugadorHumano::botonIzquierdo(ObjetoEscena* obj)
//{

    /*
    if (escena->getTablero()->getCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        Ficha* ficha = static_cast<Ficha*>(escena->getTablero()->getCasillaSeleccionada()->getHijo(0));
       //ficha->getNodoOgre()->showBoundingBox(false);
        escena->getTablero()->setCasillaSeleccionada(-1);
    }

    */



    //apagaCasillas();

 

    //if (escenaMV->getTablero()->getCasillaSeleccionada())

	//si la ficha esta elegida o no deberia verse en modelo
  
	
 //   return false;
//}








/*
bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
                 ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();


    if (nodoSeleccionado != NULL && Jugador::casillaSobrevolada(nombreCasilla))
    {
    if   (escenaMV->getTablero()->getCasillaSobrevolada()->numHijos() == 0 || escenaMV->getTablero()->getCasillaSobrevolada()->getHijo(0)->mask != nodoSeleccionado->getHijo(0)->mask)
    {


        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;

       // ObjetoEscena *mFicha = nodoSeleccionado->getHijo(0);

      //  tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   mainModelBoard->casillasInt = tablero->traduceTablero();



        modelo->mainModelBoard->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        modelo->mainModelBoard->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;

        //AUTORIZA
        int resultado = Autorizaciones::autorizaCasilla();

        if (resultado == 1)
        {
            modelo->jugadaElegida[0] = modelo->mainModelBoard->jugada[0];
            modelo->jugadaElegida[1] = modelo->mainModelBoard->jugada[1];


            // CASILLA AUTORIZADA
            escenaMV->getTablero()->getCasillaSobrevolada()->cambiaMaterial(1);
            return true;
        }
        else
        {

            // CASILLA PROHIBIDA
            modelo->mainModelBoard->jugada[0] = -1;
            modelo->mainModelBoard->jugada[1] = -1;
            modelo->jugadaElegida[0] = -1;
            modelo->jugadaElegida[1] = -1;


            if (resultado == 2)
            {
                //JAQUE AL SOBREVOLAR CASILLA
                escenaMV->muestraVentanaEmergente("Jaque");
            }
            return false;
        }

    }else
    {
            // CASILLA DEL MISMO TIPO
            modelo->mainModelBoard->jugada[0] = -1;
            modelo->mainModelBoard->jugada[1] = -1;
            modelo->jugadaElegida[0] = -1;
            modelo->jugadaElegida[1] = -1;
        return false;
    }

    }

}
*/
bool JugadorHumano::esHumano()
{
    return true;
}

