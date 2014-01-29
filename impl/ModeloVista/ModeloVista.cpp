#include "../../headers/ModeloVista/ModeloVista.h"

ModeloVista::ModeloVista():
    numPantalla(0)
  //, escenaMV(0)
  , mShutDown(0)
  ,  numJugadores(0)
 // , modelo(0)
  , JugadorActivo(0)
  , dificultad(1)
  , modoJuego(0)
  ,resolucion("1024 x 768")
  , pantallaCompleta(false)
   
 // , turnoNegras(false)
 
{
	modelo = Modelo::getSingletonPtr();
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
	jugadores.push_back(new JugadorHumano(escenaMV, modelo, nombres[0]));
	

    //HAY QUE CAMBIAR LO DE MODELOTABKERO PORQUE LOS JUGADORES ESTAN EN UN VECTOR Y ESE ES EL PROBLEMA
    if (getNumPantalla() == 1)
    {
        jugadores.push_back(new JugadorHumano(escenaMV, modelo, nombres[1]));
    }
    else
    {
        jugadores.push_back(new JugadorArtificial(escenaMV, modelo, nombres[1]));
		modelo->dificultad = (2 * dificultad) + 1;
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

					     escenaMV->createSceneMV();

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

                Casilla* casilla= static_cast<Casilla*>(escenaMV->getTablero()->getHijo(((i-2)*8)+y-2));
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

                        modelo->tableroModelo->casillasInt[numeroCasilla] = -ficha->tipo_Ficha;;
                    }
                    else modelo->tableroModelo->casillasInt[numeroCasilla] = ficha->tipo_Ficha;
																			    std::cout << "pipipi "<<std::endl;

                }else modelo->tableroModelo->casillasInt[numeroCasilla] = 0;
                numCasilla++;
																		    std::cout << "numcas "<<std::endl;

            }
        }

    }

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );
 //  return casillasInt;
}




bool ModeloVista::getTurnoNegras()
{
    return modelo->tableroModelo->turnoN;
}
void ModeloVista::aplicaCambio()
{
    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    bool resultado = JugadorActivo->aplicaSeleccion();

    if (resultado == true)
    {//FICHA MOVIDA
        if (getNumPantalla() == 1)
            escenaMV->rotaCamara = 180;

        //CAMBIA JUGADOR ACTIVO
        JugadorActivo = jugadores.at(getTurnoNegras());

        if (JugadorActivo->iniciaTurno())
        {
            aplicaCambio();
        }
    }
}
	  	void ModeloVista::procesaNodoPulsado(std::string nombreNodo)
		{
			ObjetoEscena* tablero = escenaMV->getTablero();
			       ObjetoEscena* casilla = tablero->getHijo(nombreNodo);

				   //ESTO PONDRA LA CASILLA SELECCIONADA
			   JugadorActivo->botonIzquierdo(casilla);

		}

void ModeloVista::actualizaTablero()
{  
    Casilla* nodoCasillaTemporal = escenaMV->getTablero()->getCasillaSeleccionada();
    Casilla* casillaDestinoTemp =  escenaMV->getTablero()->getCasillaSobrevolada();

     escenaMV->getTablero()->setCasillaSobrevolada(-1);
     escenaMV->getTablero()->setCasillaSeleccionada(-1);

    if (!nodoCasillaTemporal->sinHijos())
    {
        casillaDestinoTemp->apagaCasilla();
        Ficha* ficha =  static_cast<Ficha*>(nodoCasillaTemporal->getHijo(0));

        //BORRA FICHA DE LA CASILLA
        nodoCasillaTemporal->eliminaHijo(0);

        //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
        if (!casillaDestinoTemp->sinHijos())
        {
            Ficha* ficha = static_cast<Ficha*>(casillaDestinoTemp->getHijo(0));
            casillaDestinoTemp->eliminaHijo(0);
            delete ficha;
            ficha = NULL;
        }
        casillaDestinoTemp->agregaHijo(ficha);

        if (ficha->tipo_Ficha == 6)
        {
            int difCol = casillaDestinoTemp->getPosicion().Columna - nodoCasillaTemporal->getPosicion().Columna;
            // if (difCol<0 ) difCol = -difCol;

            int fila =casillaDestinoTemp->getPosicion().Fila;

            if (difCol == 2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>( escenaMV->getTablero()->getHijo((fila*8)+7));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>( escenaMV->getTablero()->getHijo((fila*8) +casillaDestinoTemp->getPosicion().Columna-1));
                casillaTorre->agregaHijo(fichaTorre);
            }

            if (difCol == -2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>( escenaMV->getTablero()->getHijo(fila*8));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>( escenaMV->getTablero()->getHijo((fila*8) +casillaDestinoTemp->getPosicion().Columna+1));
                casillaTorre->agregaHijo(fichaTorre);
            }
        }

        if (ficha->tipo_Ficha == 1)
        {
            //MIRA SI PROMOCIONA PEON
            // Ficha* ficha = static_cast<Ficha*>(getCasillaSobrevolada()->getHijo(0));

            if((!getTurnoNegras()
                && casillaDestinoTemp->getPosicion().Fila == 7)
                    || (getTurnoNegras()
                        && casillaDestinoTemp->getPosicion().Fila == 0 ))
            {
                casillaDestinoTemp->eliminaHijo(0);

                // ficha = tablero->promocionaPeon(ficha);
                //  Ogre::Entity *entidadFicha;

                std::stringstream saux;

                saux.str("");
              //  saux << "ReinaPR_" <<  escenaMV->getTablero()->peonesPromocionados;

                delete ficha;
               //  escenaMV->peonesPromocionados++;

                FichaReina* nodoNuevo =new FichaReina(*ficha, saux.str());

                if (!getTurnoNegras())
                {
                   // nodoNuevo->creaModelo3D( escenaMV->getTablero()->manager,"Reina", escenaMV->getTablero()->BLANCAS);
                }
                else
                {
                   // nodoNuevo->creaModelo3D( escenaMV->getTablero()->manager,"Reina", escenaMV->getTablero()->NEGRAS);
                   // nodoNuevo->cambiaMaterial("MaterialFichaNegra");
                }
                casillaDestinoTemp->agregaHijo(nodoNuevo);
            }
            //return static_cast<FichaReina*>(nodoNuevo);


            //MIRA SI HAY O COME AL PASO
            int dif = casillaDestinoTemp->getPosicion().Fila - nodoCasillaTemporal->getPosicion().Fila;
            int difCol = casillaDestinoTemp->getPosicion().Columna - nodoCasillaTemporal->getPosicion().Columna;
            if (dif < 0 ) dif = -dif;
            if (difCol<0 ) difCol = -difCol;

            if( escenaMV->getTablero()->getAlPaso() > 0 && dif == 1 && difCol == 1)
            {
                //SOLO COMER AL PASO
                int fila =nodoCasillaTemporal->getPosicion().Fila;
                int columna =casillaDestinoTemp->getPosicion().Columna;

                if ( escenaMV->getTablero()->getAlPaso() == 24+(fila*12)+columna+2)
                {
                    Casilla* casillaAux = static_cast<Casilla*>( escenaMV->getTablero()->getHijo((fila*8)+columna));

                    if (!casillaAux->sinHijos())
                    {
                        casillaAux->eliminaHijo(0);
                    }
                }
            }
             escenaMV->getTablero()->setAlPaso(-1);

            if( dif == 2)
                 escenaMV->getTablero()->setAlPaso(24+(casillaDestinoTemp->getPosicion().Fila*12) +  casillaDestinoTemp->getPosicion().Columna+2);
        }
        else  escenaMV->getTablero()->setAlPaso(-1);

        //DESELECCIONA FICHA Y CASILLA
        //ficha->getNodoOgre()->showBoundingBox(false);
    }

//    turnoNegras = !turnoNegras;
}