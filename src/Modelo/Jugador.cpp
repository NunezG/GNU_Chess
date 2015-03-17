#include "Jugador.h"

std::vector<int> Jugador::jugadasElegidas;
ModeloTablero* Jugador::modelo;

Jugador::Jugador(ModeloTablero* modeloAnt, std::string nombreJugador) :
    //jugadorNegras(false),
    nombre(nombreJugador)
    // miTablero(0)
    //mainModelBoard(modeloTablero)
  //  escenaMV(miEscena)
  //, tablero(miEscena->tablero)
  //, modelo(modeloAnt)
  //esperaEleccion(false)
{
	modelo = modeloAnt;
    // tablero = escena->tablero;
}

Jugador::~Jugador()
{
}


std::string Jugador::getNombre()
{
    return nombre;
}

void Jugador::setNombre( std::string unNombre)
{
    nombre = unNombre;
}

int Jugador::jaqueMate()
{
    // tablero->cambiaTurno();
    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);
    //  ModeloTablero* turnoSiguiente = new ModeloTablero(*modelo->mainModelBoard);
    bool Jaque = false;
    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);
    Jaque = modelo->evaluaJaque();  //JAQUE AL REY

    std::cout << "HAY JAUQUE ASECAS PARA EL ENEMIGO DESPUES DE MOVER? "<<Jaque <<std::endl;

    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Autorizaciones::pruebaJaqueMate(modelo))
    {
        //  delete turnoSiguiente;

        //SE EVALUA EL JAQUE Y SI EL REY NO ESTA EN JAQUE ES QUE ES AHOGADO
        //EVALUA JAQUE
        if (Jaque)
        {            //JAQUE MATE
			std::cout << "JAQUE MATE "  << std::endl;

            return 3;
        }
        else
        { //NO HAY JAQUE, AHOGADO, RESULTADO EN TABLAS
			std::cout << "AHOGADO " << std::endl;
            return 4;
        }
    }
    else
    {
        //  delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
			std::cout << "JAQUE " << std::endl;

            return 2;
        }
		std::cout << "Mueve " << std::endl;

        //Mueve
        return 1;
    }
    //FINDE PARTIDA
}


bool Jugador::iniciaTurno()
{
   // escenaMV->nombreActivo = nombre;
    return false;
}


int Jugador::ejecutaJugada()
{
	std::cout << "jaquemate" << std::endl;

	if (modelo->cambiaTurno(jugadasElegidas))
	return jaqueMate();
	else return false;

	//std::cout << "RESULTAOD DE JAQUE DESPUES DE MOVER PARA VER SI AMENAZA" << resultado << std::endl;

}


bool Jugador::confirmaJugada(int posicion)
{
	//jugadasElegidas.clear();

	std::cout << "confirmaJugada" << jugadasPermitidas.size() << std::endl;
	bool movimiento = false;
	if (!jugadasPermitidas.empty())
	{
		
		for (std::vector<int>::iterator it = jugadasPermitidas.begin(); it != jugadasPermitidas.end(); it++)
		{
			int jugada = *it;

			std::cout << "forjugadaspermitidas" << std::endl;


			//LA JUGADA ESTA ENTRE LAS RESALTADAS (AUTORIZADA)
			if (jugada == posicion)
			{
				std::cout << "JUGADA AUTORIZADA " << jugada << std::endl;


				//std::vector<int> jug;
				jugadasElegidas.push_back(jugada);
				std::cout << "jugadasElegidas.siz " << jugadasElegidas.size() << std::endl;

				movimiento = true;

			}

			//APAGA CASILLA, ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿?????????????????????????????????????????????????????necesario?
			//ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada / 12) - 2) * 8 + ((jugada % 12) - 2));
			//ob->cambiaMaterial(0);

		}

		//apaga objeto seleccionado
		//ObjetoEscena* ficha = escenaMV->getTablero()->objetoPadre->getHijo(((modelo->mainModelBoard->jugada[0]/12)-2)*8 + ((modelo->mainModelBoard->jugada[0]%12)-2))->getHijo(0);
		//escenaMV->getTablero()->getCasillaSeleccionada()->getHijo(0)->cambiaMaterial(0);

		//Borra jugadas

		//modelo->mainModelBoard->vectorJugada = jugadasElegidas;

		// modelo->mueveTablero();

		//  escenaMV->getTablero()->actualizaTablero();

		//PROMOCIONA PEÓN
		//  escena->getTablero()->promocionaPeon(escena->mSceneMgr);
		//COMPRUEBA JAQUE AL MOVER TABLERO EN MODELO

		//HABRA QUE BORRAR BIEN LOS PUNTEROS O NO USARLOS
		//jugadasElegidas.clear();

		jugadasPermitidas.clear();

	}
	return movimiento;

}



//esto en jugador humnano?
bool Jugador::seleccionaFicha(int posicion)

{
	jugadasPermitidas.clear();
	jugadasElegidas.clear();
//	ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();

//	if (nodoSeleccionado != NULL)
//	{


		std::cout << "seleccionado" << std::endl;


		//posicion inicial

		//modelo->mainModelBoard->casillaSeleccionada = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;





		//	modelo->mainModelBoard->vectorJugada.push_back(24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2);
		// modelo->mainModelBoard->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;



		std::cout << "AUTORIZA" << std::endl;

		//AUTORIZA
		jugadasPermitidas = Autorizaciones::casillasAutorizadas(modelo, posicion);


		jugadasElegidas.push_back(posicion);


		// int resultado = Autorizaciones::autorizaCasilla();

		if (!jugadasPermitidas.empty())
		{
			std::cout << "jugadasPermitidas: " << jugadasPermitidas.size() << std::endl;



			return true;
		}
		else
		{
			

			return false;
		}

	//}

}