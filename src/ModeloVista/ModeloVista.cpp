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
  ,resolucion("854 x 480")
  , pantallaCompleta(false)
  //,reiniciar(1)
  , jugadores(0)
  ,voltea(0)

  //#endif


  // , turnoNegras(false)

{

    modelo = Modelo::getSingletonPtr();
    escenaMV = new EscenaAjedrez();

    nombres[0] = "Jugador 1";
    nombres[1] = "Jugador 2";

}

ModeloVista::~ModeloVista(void)
{
    borraJugadores();
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
        //modelo->dificultad = (2 * dificultad) + 1;
    }

    if (JugadorActivo == NULL)
    {
        JugadorActivo = jugadores.at(0);
        //  jugadores.at(num)->jugadorNegras = 0;
    }
    numJugadores++;
}


void ModeloVista::borraJugadores()
{


	 for (std::vector<Jugador*>::iterator it = jugadores.begin(); it!=jugadores.end(); it++)
        {
			Jugador* jugador = *it;
			delete jugador;
			jugador = NULL;
	 }



	jugadores.clear();

   
}


void ModeloVista::borraTablero()
{


   
}


bool ModeloVista::jugadaElegida()
{
    return modelo->jugadasElegidas.size() > 0;
}
/*
void ModeloVista::creaEscenaYModelo()
{

    // escenaMV->createSceneMV();


    if (modelo->tableroModelo != NULL)
    {
        // traduceTablero();

        modelo->tableroModelo->alPaso = escenaMV->getTablero()->getAlPaso();

        modelo->tableroModelo->turnoN = getTurnoNegras();

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

                modelo->tableroModelo->casillasInt[(i*12)+y] = 99;

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

                        modelo->tableroModelo->casillasInt[numeroCasilla] = -ficha->tipo_Ficha;
                    }
                    else modelo->tableroModelo->casillasInt[numeroCasilla] = ficha->tipo_Ficha;

                }else modelo->tableroModelo->casillasInt[numeroCasilla] = 0;
                numCasilla++;

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

    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    bool resultado = JugadorActivo->aplicaSeleccion();

    if (resultado == true)
    {//FICHA MOVIDA

        if (getNumPantalla() == 1)
        {

            if (getTurnoNegras()) escenaMV->rotaCamara = voltea;
            else
                escenaMV->rotaCamara = -voltea;

        }

        //CAMBIA JUGADOR ACTIVO
        JugadorActivo = jugadores.at(getTurnoNegras());

        //HABRA QUE USAR OTRO THREAD
        JugadorActivo->iniciaTurno();
        
    }


}
void ModeloVista::procesaNodoPulsado(std::string nombreNodo)
{
    ObjetoEscena* tablero = escenaMV->getTablero()->objetoPadre;
    ObjetoEscena* casilla = tablero->getHijo(nombreNodo);

    //ESTO PONDRA LA CASILLA SELECCIONADA
    JugadorActivo->botonIzquierdo(casilla);

}
