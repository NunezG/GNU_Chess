#include "../../headers/ModeloVista/ModeloVista.h"

ModeloVista::ModeloVista():
    numPantalla(0)
  , escena(0)
  , mShutDown(0)
  ,  numJugadores(0)
 // , modelo(0)
  , JugadorActivo(0)
  , dificultad(1)
  , modoJuego(0)
  ,resolucion("1024 x 768")
  , pantallaCompleta(false)
 
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
	jugadores.push_back(new JugadorHumano(escena, modelo, nombres[0]));
	

    //HAY QUE CAMBIAR LO DE MODELOTABKERO PORQUE LOS JUGADORES ESTAN EN UN VECTOR Y ESE ES EL PROBLEMA
    if (getNumPantalla() == 1)
    {
        jugadores.push_back(new JugadorHumano(escena, modelo, nombres[1]));
    }
    else
    {
        jugadores.push_back(new JugadorArtificial(escena, modelo, nombres[1]));
		modelo->dificultad = (2 * dificultad) + 1;
    }

    if (JugadorActivo == NULL)
    {
        JugadorActivo = jugadores.at(0);
      //  jugadores.at(num)->jugadorNegras = 0;
  }
    numJugadores++;
}


void ModeloVista::creaEscenaYModelo()
{
    escena->createScene();

    if (modelo->tableroModelo != NULL)
    {
        traduceTablero();
        modelo->tableroModelo->alPaso = escena->getTablero()->getAlPaso();
        modelo->tableroModelo->turnoN = escena->getTablero()->getTurnoNegras();
    }
}


void ModeloVista::traduceTablero()
{
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
                Casilla* casilla= static_cast<Casilla*>(escena->getTablero()->getHijo(((i-2)*8)+y-2));
                int filaTemp = casilla->getPosicion().Fila;
                int columnaTemp = casilla->getPosicion().Columna;
                int numeroCasilla = 24+(filaTemp*12)+columnaTemp+2;

                if (!casilla->sinHijos())
                {
                    Ficha* ficha = static_cast<Ficha*>(casilla->getHijo(0));

                    //ESTO ASEGURA QUE LAS FICHAS CORRESPONDIENTES AL TURNO SEAN POSITIVAS
                    if (ficha->esNegra && !escena->getTablero()->getTurnoNegras() || !ficha->esNegra && escena->getTablero()->getTurnoNegras())
                    {
                        modelo->tableroModelo->casillasInt[numeroCasilla] = -ficha->tipo_Ficha;;
                    }
                    else modelo->tableroModelo->casillasInt[numeroCasilla] = ficha->tipo_Ficha;

                }else modelo->tableroModelo->casillasInt[numeroCasilla] = 0;
                numCasilla++;
            }
        }

    }

    // Ogre::SceneNode* nodoTemporal = static_cast<Ogre::SceneNode*>( tablero->nodoCasillero->getChildIterator() );
 //  return casillasInt;
}




void ModeloVista::aplicaCambio()
{
    //MUEVE FICHA Y A LA VEZ COMPRUEBA EL FIN DE PARTIDA O SI EL JUGADOR CONTRARIO ESTA EN JAQUE JUSTO DESPUES DE MOVER FICHA
    bool resultado = JugadorActivo->aplicaSeleccion();

    if (resultado == true)
    {//FICHA MOVIDA
        if (getNumPantalla() == 1)
            escena->getTablero()->rotacionCamara = Ogre::Real(180.0f);

        //CAMBIA JUGADOR ACTIVO
        JugadorActivo = jugadores.at(escena->getTablero()->getTurnoNegras());

        if (JugadorActivo->iniciaTurno())
        {
            aplicaCambio();
        }
    }
}
