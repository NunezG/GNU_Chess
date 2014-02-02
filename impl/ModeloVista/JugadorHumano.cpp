#include "../../headers/ModeloVista/JugadorHumano.h"

JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    Jugador(miEscena, modelo, nombreJugador)
{ 
		    				    std::cout << "JugadorHumano "<<std::endl;

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

        ObjetoEscena* ficha = obj->getHijo(0);
        if ((modelo->tableroModelo->turnoN
             && ficha->mask == NEGRAS)
                || (!modelo->tableroModelo->turnoN
                    && ficha->mask == BLANCAS))
        {
            escenaMV->getTablero()->setCasillaSeleccionada(obj);

            // ficha->getNodoOgre()->showBoundingBox(true);
            return true;
        }
    }
    return false;
}


bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
						std::cout << "casillaSobrevolada "<< nombreCasilla <<std::endl;
												//std::cout << escena->getTablero()->getCasillaSeleccionada()<<std::endl;
					//	std::cout << "casillaSobrevolada"<<std::endl;

    if (escenaMV->getTablero()->getCasillaSeleccionada() != NULL && Jugador::casillaSobrevolada(nombreCasilla))
    {
		std::cout << "casillaSobrevolada innnnnnnnn111"<<escenaMV->getTablero()->getCasillaSeleccionada()->getNombre()   <<std::endl;

        ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();

        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;
				  						std::cout << "cnodoSeleccionado: "<<   nodoSeleccionado->getNombre()  <<std::endl;

        ObjetoEscena *mFicha = nodoSeleccionado->getHijo(0);
		std::cout << "mFicha: "<<   mFicha->getNombre()  <<std::endl;

      //  tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   tableroModelo->casillasInt = tablero->traduceTablero();
		  					//	std::cout << "tipo111: "<< mFicha->tipo_Ficha<<std::endl;

  						//std::cout << "tipo: "<< tipo<<std::endl;



						  						std::cout << "filasel: "<< nodoSeleccionado->posInView.Fila <<std::endl;
											     std::cout << "colasel: "<< nodoSeleccionado->posInView.Columna <<std::endl;
												 std::cout << "filasobre: "<< escenaMV->getTablero()->getCasillaSobrevolada()->posInView.Fila<<std::endl;
											     std::cout << "colasobre: "<< escenaMV->getTablero()->getCasillaSobrevolada()->posInView.Columna <<std::endl;


        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->posInView.Fila * 12) + nodoSeleccionado->posInView.Columna + 2;
        modelo->tableroModelo->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->posInView.Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->posInView.Columna + 2;

        //AUTORIZA
        int resultado = Autorizaciones::autorizaCasilla();

        if (resultado == 1)
        {
            modelo->jugadaElegida[0] = modelo->tableroModelo->jugada[0];
            modelo->jugadaElegida[1] = modelo->tableroModelo->jugada[1];

			  						std::cout << "ASILLA AUTORIZADA"<<std::endl;

            // CASILLA AUTORIZADA
            escenaMV->getTablero()->getCasillaSobrevolada()->cambiaMaterial(1);
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
                escenaMV->muestraVentanaEmergente("Jaque");
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

