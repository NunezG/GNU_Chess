#include "../../include/ModeloVista/ModeloVista.h"

ModeloVista::ModeloVista():
    numPantalla(0)
 // , escenaMV(0)
  , mShutDown(0)
  ,  numJugadores(0)
 // , modelo(0)
  , JugadorActivo(0)
 // , dificultad(1)
  , modoJuego(0)
  ,resolucion("1024 x 768")
  , pantallaCompleta(false)
  ,reiniciar(0)
  , jugadores(0)
   
 // , turnoNegras(false)
 
{

	modelo = Modelo::getSingletonPtr();
	escenaMV = new EscenaAjedrez();

	 nombres[0] = "Jugador 1";
	 nombres[1] = "Jugador 2";

}

ModeloVista::~ModeloVista(void)
{
    for (int i=0; i<jugadores.size();i++)
    {
        delete jugadores.at(i);
        jugadores.at(i) = NULL;
    }
    jugadores.clear();
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
    numPantalla = pantalla;
}

void ModeloVista::generaJugadores()
{


		    	 std::cout << "generaJuhuhuh "<<std::endl;
				 		    	 std::cout <<nombres[0]<<std::endl;

				  std::cout << "modelo "<<modelo->posInicial<<std::endl;




				   std::cout << "escenaMV "<< escenaMV->getModoCamara()<<std::endl;

	jugadores.push_back(new JugadorHumano(escenaMV, modelo, nombres[0]));
	
		    				    std::cout << "generaJu22 "<<std::endl;

    //HAY QUE CAMBIAR LO DE MODELOTABKERO PORQUE LOS JUGADORES ESTAN EN UN VECTOR Y ESE ES EL PROBLEMA
    if (getNumPantalla() == 1)
    {
        jugadores.push_back(new JugadorHumano(escenaMV, modelo, nombres[1]));
    }
    else
    {
        jugadores.push_back(new JugadorArtificial(escenaMV, modelo, nombres[1]));
		//modelo->dificultad = (2 * dificultad) + 1;
    }

    if (JugadorActivo == NULL)
    {
        JugadorActivo = jugadores.at(0);
      //  jugadores.at(num)->jugadorNegras = 0;
  }
    numJugadores++;
}

bool ModeloVista::jugadaElegida()
{
    return (modelo->jugadaElegida[1] != modelo->jugadaElegida[0]);
}

void ModeloVista::creaEscenaYModelo()
{
						    std::cout << "creaEscenaYModelo "<<std::endl;

					    // escenaMV->createSceneMV();

					    std::cout << "creaEscenaYModelo 222222222222222222"<<std::endl;

    if (modelo->tableroModelo != NULL)
    {
	    std::cout << "traduceTablero "<<std::endl;
       // traduceTablero();

			    std::cout << "traduceTablero1 111 "<<std::endl;

        modelo->tableroModelo->alPaso = escenaMV->getTablero()->getAlPaso();
					    std::cout << "traduceTablero1 111 22"<<std::endl;

        modelo->tableroModelo->turnoN = getTurnoNegras();
        std::cout << "traduceTablero 222"<<std::endl;

    }
						    std::cout << "finnnn creaEscenaYModelo "<<std::endl;

}


void ModeloVista::traduceTablero()
{
		    std::cout << "traduceTablero "<<std::endl;
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
					    //std::cout << "encuentraalgo "<<std::endl;

                modelo->tableroModelo->casillasInt[(i*12)+y] = 99;

            }else
            {
									    std::cout << "empiezacreacasilla "<<std::endl;

                ObjetoEscena* casilla= static_cast<ObjetoEscena*>(escenaMV->getTablero()->objetoPadre->getHijo(((i-2)*8)+y-2));
                int filaTemp = casilla->getPosicion().Fila;
                int columnaTemp = casilla->getPosicion().Columna;
                int numeroCasilla = 24+(filaTemp*12)+columnaTemp+2;
									    std::cout << "siguecreacasilla "<<std::endl;

                if (!casilla->sinHijos())
                {
														    std::cout << "sinhijjos "<<std::endl;

                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //ESTO ASEGURA QUE LAS FICHAS CORRESPONDIENTES AL TURNO SEAN POSITIVAS
                    if (ficha->esNegra && !getTurnoNegras() || !ficha->esNegra && getTurnoNegras())
                    {
																				    std::cout << "fifi "<<std::endl;

                        modelo->tableroModelo->casillasInt[numeroCasilla] = -ficha->tipo_Ficha;
                    }
                    else modelo->tableroModelo->casillasInt[numeroCasilla] = ficha->tipo_Ficha;
																			    std::cout << "pipipi "<<std::endl;

                }else modelo->tableroModelo->casillasInt[numeroCasilla] = 0;
                numCasilla++;
																		    std::cout << "numcas "<<std::endl;

            }
        }

    }*/

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );
 //  return casillasInt;
}


		void ModeloVista::cambiaOpciones(std::string difficulty, std::string resolution, bool fullsreen)
			{

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
    return modelo->tableroModelo->turnoN;
}
void ModeloVista::aplicaCambio()
{
	escenaMV->getTablero()->setCasillaSeleccionada(-1);

										   	std::cout << "aplicaCambio"<<std::endl;
    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    bool resultado = JugadorActivo->aplicaSeleccion();
											   	//std::cout << "resultado: "<<resultado<<std::endl;

    if (resultado == true)
    {//FICHA MOVIDA
        if (getNumPantalla() == 1)
		{
            escenaMV->rotaCamara = 180;
													   	std::cout << "rotacamara"<<std::endl;

		}

        //CAMBIA JUGADOR ACTIVO
        JugadorActivo = jugadores.at(getTurnoNegras());

        if (JugadorActivo->iniciaTurno())
        {
            aplicaCambio();
        }
    }

											   	std::cout << "FIN aplicaCambio"<<std::endl;

}
void ModeloVista::procesaNodoPulsado(std::string nombreNodo)
{
	ObjetoEscena* tablero = escenaMV->getTablero()->objetoPadre;
    ObjetoEscena* casilla = tablero->getHijo(nombreNodo);

   //ESTO PONDRA LA CASILLA SELECCIONADA
   JugadorActivo->botonIzquierdo(casilla);

}
