#include "../../include/ModeloVista/ModeloVista.h"

ModeloVista::ModeloVista():
    numPantalla(0)
  // , escenaMV(0)
  , mShutDown(0)
  // , modelo(0)
  // , dificultad(1)
  , modoJuego(0)
  ,resolucion("1024 x 768 @ 32-bit colour")
  , pantallaCompleta(false)
  //,reiniciar(1)

  ,voltea(0)

  //#endif


  // , turnoNegras(false)

{

    modelo = Modelo::getSingletonPtr();
    escenaMV = new EscenaAjedrez();


}

ModeloVista::~ModeloVista(void)
{
}

bool ModeloVista::getApagar()
{
    return mShutDown;
}

void ModeloVista::setApagar(bool apaga)
{
    mShutDown = apaga;
}

int ModeloVista::getNumPantalla()
{
    return numPantalla;
}

void ModeloVista::setNumPantalla(int pantalla)
{

	if (pantalla > 0) {
		modelo->setTipoJuego(pantalla);
		numPantalla = 1;
	}
	else numPantalla = 0;
    
}



void ModeloVista::borraTablero()
{


   
}

bool ModeloVista::iniciaModelo()


{

	modelo->generaJugadores();


	return true;
}



/*
void ModeloVista::creaEscenaYModelo()
{

    // escenaMV->createSceneMV();


    if (modelo->mainModelBoard != NULL)
    {
        // traduceTablero();

        modelo->mainModelBoard->alPaso = escenaMV->getTablero()->getAlPaso();

        modelo->mainModelBoard->turnoN = getTurnoNegras();

    }

}
*/

void ModeloVista::traduceTablero()
{
    /*
    int numCasilla = 0;

   // char* casillasInt = new char[144];

    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {
        for (int y = 0; y<12; y++)
        {
            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {

                modelo->mainModelBoard->casillasInt[(i*12)+y] = 99;

            }else
            {

                ObjetoEscena* casilla= static_cast<ObjetoEscena*>(escenaMV->getTablero()->objetoPadre->getHijo(((i-2)*8)+y-2));
                int filaTemp = casilla->getPosicion().Fila;
                int columnaTemp = casilla->getPosicion().Columna;
                int numeroCasilla = 24+(filaTemp*12)+columnaTemp+2;

                if (!casilla->sinHijos())
                {

                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //ESTO ASEGURA QUE LAS FICHAS CORRESPONDIENTES AL TURNO SEAN POSITIVAS
                    if (ficha->esNegra && !getTurnoNegras() || !ficha->esNegra && getTurnoNegras())
                    {

                        modelo->mainModelBoard->casillasInt[numeroCasilla] = -ficha->tipo_Ficha;
                    }
                    else modelo->mainModelBoard->casillasInt[numeroCasilla] = ficha->tipo_Ficha;

                }else modelo->mainModelBoard->casillasInt[numeroCasilla] = 0;
                numCasilla++;

            }
        }

    }*/

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );
    //  return casillasInt;
}


void ModeloVista::cambiaOpciones(std::string difficulty, std::string resolution, bool fullsreen)
{
	//unsigned char test::X = 1;
	//unsigned char test::Y = 2;

    resolucion = resolution;
    pantallaCompleta = fullsreen;
    if (difficulty == "easy")
        modelo->dificultad = 3;
    else
		modelo->dificultad = 5;

    //modelo-> resolu
    //escenaMV->


}


bool ModeloVista::getTurnoNegras()
{
    return modelo->mainModelBoard->turnoN;
}



void ModeloVista::compruebaCambio()
{
	if (modelo->jugadaElegida())
	{
		int resultado = modelo->JugadorActivo->ejecutaJugada();

		escenaMV->getTablero()->setCasillaSeleccionada(-1);

		std::cout << "aplicaCambio" << std::endl;

		//MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
		//bool resultado = aplicaSeleccion();

		escenaMV->apagaVentanaEmergente();
		escenaMV->getTablero()->actualizaTablero(modelo->JugadorActivo->jugadasElegidas);
	
		std::cout << "jaquemate" << std::endl;
		modelo->JugadorActivo->jugadasElegidas.clear();

		switch (resultado)
		{
		case 2:
			std::cout << "HAY JAQUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe" << std::endl;

			escenaMV->muestraVentanaEmergente("Jaque");
			//return true;
		case 3:
			std::cout << "JaqueMateEEESESEESE" << std::endl;

			//escena->nom
			escenaMV->muestraVentanaEmergente("JaqueMate");
			//return false;
		case 4:
			std::cout << "TablaAAAASASASDASDASDASD" << std::endl;

			escenaMV->muestraVentanaEmergente("Tablas");
			//return false;
		default: //MOVIMIENTO NORMAL
			std::cout << "MUEVE N AMMAL" << std::endl;
			//return true;
		}


		if (resultado == true)
		{//FICHA MOVIDA

			if (modelo->getTipoJuego() == 1)
			{

				if (getTurnoNegras()) escenaMV->rotaCamara = voltea;
				else
					escenaMV->rotaCamara = -voltea;

			}

			modelo->cambiaTurno();

		}
	}
}


bool ModeloVista::procesaNodoPulsado(std::string nombreNodo)
{
	apagaCasillas();

	ObjetoEscena* tablero = escenaMV->getTablero()->objetoPadre;
	ObjetoEscena* casilla = tablero->getHijo(nombreNodo);
	escenaMV->getTablero()->setCasillaSeleccionada(-1);

		//ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();


    //ESTO PONDRA LA CASILLA SELECCIONADA
  //  JugadorActivo->botonIzquierdo(casilla);
	std::cout << "NODO PULSADODODODODO" << std::endl;


	if (casilla != NULL)
	{

			std::cout << "CASILLA TIENE JIJO" << std::endl;
	
		//	if (modelo->jugadaElegida())
			//{

				bool movido = modelo->JugadorActivo->confirmaJugada(24 + (casilla->getPosicion().Fila * 12) + casilla->getPosicion().Columna + 2);

		//	}
				if (movido == false && casilla->numHijos() != 0)
				{
				std::cout << "SELECCIONA!!!!" << std::endl;

				//JugadorActivo->seleccionaCasilla();

				//if ((modelo->mainModelBoard->casillaSeleccionada())
				//{

				if (modelo->JugadorActivo->seleccionaFicha(24 + (casilla->getPosicion().Fila * 12) + casilla->getPosicion().Columna + 2))
				{

					escenaMV->getTablero()->setCasillaSeleccionada(casilla);


					//ENCIENDE CASILLAS
					if (!modelo->JugadorActivo->jugadasPermitidas.empty())
					{
						std::cout << "jugadasPermitidas: " << modelo->JugadorActivo->jugadasPermitidas.size() << std::endl;


						for (std::vector<int>::iterator it = modelo->JugadorActivo->jugadasPermitidas.begin(); it != modelo->JugadorActivo->jugadasPermitidas.end(); it++)
						{
							int jugada = *it;
							std::cout << "jugada: " << jugada << std::endl;

							ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada / 12) - 2) * 8 + ((jugada % 12) - 2));

							if (ob->numHijos() > 0)
								ob->cambiaMaterial(2);
							else ob->cambiaMaterial(1);

							// CASILLA AUTORIZADA
							//  escenaMV->getTablero()->getCasillaSobrevolada()->cambiaMaterial(1);

						}

						return true;
					}
					else return false;

					return true;

				}

			}

		//	std::cout << "seleccionado" << std::endl;

		//AUTORIZA
		//jugadasPermitidas = Autorizaciones::casillasAutorizadas(modelo->mainModelBoard, posicion);

		// int resultado = Autorizaciones::autorizaCasilla();

	}

	





}

/*
bool ModeloVista::casillaSobrevolada(const std::string nombreCasilla)
{
	ObjetoEscena* casillaSobre = escenaMV->getTablero()->objetoPadre->getHijo(nombreCasilla);
	ObjetoEscena* casillaSobreAnterior = escenaMV->getTablero()->getCasillaSobrevolada();

	//devulve true si ha cambiado de casilla
	if (!casillaSobreAnterior || casillaSobre->getNombre() != casillaSobreAnterior->getNombre())
	{

		//   if (casillaSobreAnterior )
		//   {
		//       escenaMV->apagaVentanaEmergente();

		//       casillaSobreAnterior->cambiaMaterial(0);
		//tablero->setNodoCasillaSobrevolada(-1);
		//    }

		escenaMV->getTablero()->setCasillaSobrevolada(casillaSobre);

		return true;
	}

	return false;
}
*/


bool ModeloVista::apagaCasillas()
{
	
	//Apaga casillas
	if (!modelo->JugadorActivo->jugadasPermitidas.empty())
	{
		for (std::vector<int>::iterator it = modelo->JugadorActivo->jugadasPermitidas.begin(); it != modelo->JugadorActivo->jugadasPermitidas.end(); it++)
		{
			int jugada = *it;

			ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada / 12) - 2) * 8 + ((jugada % 12) - 2));
			ob->cambiaMaterial(0);

		}
	}

	return true;
}

