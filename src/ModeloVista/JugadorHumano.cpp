#include "../../include/ModeloVista/JugadorHumano.h"

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



    if (obj != NULL)
	{
		//apagaCasillas();

	 if (!jugadasResaltadas.empty())
    {		
		bool movimiento = false;
    for (std::vector<int>::iterator it = jugadasResaltadas.begin(); it!=jugadasResaltadas.end(); it++)
    {
		int jugada = *it;

		//APAGA CASILLA
		ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada/12)-2)*8 + ((jugada%12)-2));
		ob->cambiaMaterial(0);          			 

		//LA JUGADA ESTA AUTORIZADA
		if(jugada == 24 + (obj->getPosicion().Fila * 12) + obj->getPosicion().Columna + 2)
		{

			modelo->jugadaElegida[0] = modelo->tableroModelo->jugada[0];
            modelo->jugadaElegida[1] = modelo->tableroModelo->jugada[1];	
			movimiento = true;
			  						
		}



	}

	if (movimiento)
	{
	

		std::cout << "ASILLA AUTORIZADA"<<std::endl;



									return true;
	}
	 }


		//if (escenaMV->getTablero()->getCasillaSeleccionada())
		


		if(!obj->numHijos() == 0)
    {

        ObjetoEscena* ficha = obj->getHijo(0);
        if ((modelo->tableroModelo->turnoN
             && ficha->mask == NEGRAS)
                || (!modelo->tableroModelo->turnoN
                    && ficha->mask == BLANCAS))
        {

								std::cout << "LA CASILLA HA QUEDADO SELECCIONADA Y PULSADA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;

            escenaMV->getTablero()->setCasillaSeleccionada(obj);

			fichaPulsada();


            // ficha->getNodoOgre()->showBoundingBox(true);
            return true;
        }
    }
    return false;
}


}



bool JugadorHumano::apagaCasillas()
{

		//Apaga casillas
    if (!jugadasResaltadas.empty())
    {				
    for (std::vector<int>::iterator it = jugadasResaltadas.begin(); it!=jugadasResaltadas.end(); it++)
    {
		        int jugada = *it;

				ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada/12)-2)*8 + ((jugada%12)-2));
				ob->cambiaMaterial(0);          			 

	}    
    }

return true;
}
		


bool JugadorHumano::fichaPulsada()
{
				
	ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();

	if (nodoSeleccionado != NULL)
	{

	
  
						  						std::cout << "filasel: "<< nodoSeleccionado->getPosicion().Fila <<std::endl;
											     std::cout << "colasel: "<< nodoSeleccionado->getPosicion().Columna <<std::endl;
												

        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
       // modelo->tableroModelo->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;

		


        //AUTORIZA
	jugadasResaltadas =  Autorizaciones::casillasAutorizadas();

       // int resultado = Autorizaciones::autorizaCasilla();

        if (!jugadasResaltadas.empty())
        {

				
    for (std::vector<int>::iterator it = jugadasResaltadas.begin(); it!=jugadasResaltadas.end(); it++)
    {
		        int jugada = *it;

			 	std::cout << "JUGAADADA ASILLA AUTORIZADA: "<< jugada<<std::endl;

	            std::cout << "FILA ASILLA AUTORIZADA: "<< (jugada/12)-2<<std::endl;
				std::cout << "COLUMNA ASILLA AUTORIZADA: "<< (jugada%12)-2<<std::endl;

			 	std::cout << "CASILLA TRADUCIDA?: "<< ((jugada/12)-2)*8 + ((jugada%12)-2) <<std::endl;

				ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada/12)-2)*8 + ((jugada%12)-2));
				ob->cambiaMaterial(1);
           			 	std::cout << "CASILLA ENCONTRADAADADA: "<< ob->getNombre() <<std::endl;
						std::cout << "FILALLALALA: "<< ob->getPosicion().Fila <<std::endl;
						std::cout << "COLUMNANANAN: "<< ob->getPosicion().Fila <<std::endl;

			
			// CASILLA AUTORIZADA
          //  escenaMV->getTablero()->getCasillaSobrevolada()->cambiaMaterial(1);

	}




            return true;
        }
        else
        {
            // CASILLA PROHIBIDA
            modelo->tableroModelo->jugada[0] = -1;
            
            return false;
        }
		
	}
   
}

/*
bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
						std::cout << "casillaSobrevolada "<< nombreCasilla <<std::endl;
												//std::cout << escena->getTablero()->getCasillaSeleccionada()<<std::endl;
					//	std::cout << "casillaSobrevolada"<<std::endl;
				 ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();


	if (nodoSeleccionado != NULL && Jugador::casillaSobrevolada(nombreCasilla))
	{
    if   (escenaMV->getTablero()->getCasillaSobrevolada()->numHijos() == 0 || escenaMV->getTablero()->getCasillaSobrevolada()->getHijo(0)->mask != nodoSeleccionado->getHijo(0)->mask)
    {
		std::cout << "casillaSobrevolada innnnnnnnn111"<<escenaMV->getTablero()->getCasillaSeleccionada()->getNombre()   <<std::endl;


        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;
				  						std::cout << "cnodoSeleccionado: "<<   nodoSeleccionado->getNombre()  <<std::endl;

       // ObjetoEscena *mFicha = nodoSeleccionado->getHijo(0);
		//std::cout << "mFicha: "<<   mFicha->getNombre()  <<std::endl;

      //  tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   tableroModelo->casillasInt = tablero->traduceTablero();
		  					//	std::cout << "tipo111: "<< mFicha->tipo_Ficha<<std::endl;

  						//std::cout << "tipo: "<< tipo<<std::endl;
	
		

						  						std::cout << "filasel: "<< nodoSeleccionado->getPosicion().Fila <<std::endl;
											     std::cout << "colasel: "<< nodoSeleccionado->getPosicion().Columna <<std::endl;
												 std::cout << "filasobre: "<< escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila<<std::endl;
											     std::cout << "colasobre: "<< escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna <<std::endl;


        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        modelo->tableroModelo->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;

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
						  						std::cout << "ASILLA PROHIBIDA"<<std::endl;

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
		
    }else
	{
            // CASILLA DEL MISMO TIPO
            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;
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

