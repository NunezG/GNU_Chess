#include "Modelo.h"

Modelo::Modelo():
    //jugadaAutorizada(false)
    // ,nombreBlancas("Jugador 1")
    //, nombreNegras("Jugador 2")
    //,  jugadores(NULL)
    dificultad(3)
  , posInicial("bcdefdcbaaaaaaaa00000000000000000000000000000000zzzzzzzzyxwvuwxy")
  , jugadasElegidas("")

{   
    //mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");
    tableroModelo = new ModeloTablero(posInicial);
}

Modelo::~Modelo()
{
}

Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}



void Modelo::mueveTablero()
{

    tableroModelo->jugadas = jugadasElegidas;
    //  tableroModelo->jugadaPrincipal[1] = jugadaElegida[1];

    tableroModelo->cambiaTurno();

    //tableroModelo->jugada[0] = 143-jugadaElegida[0];
    //tableroModelo->jugada[1] = 143-jugadaElegida[1];




}
