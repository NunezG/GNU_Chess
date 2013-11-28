#include "../../headers/Modelo/Modelo.h"

Modelo::Modelo():
    //jugadaAutorizada(false)
  // ,nombreBlancas("Jugador 1")
  //, nombreNegras("Jugador 2")
  //,  jugadores(NULL)
     dificultad(3)

{   
    //mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");
    tableroModelo = new ModeloTablero();
    jugadaElegida[0] = 0;
    jugadaElegida[1] = 0;
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

void Modelo::agregaJugada(int inicio, int fin)
{
    tableroModelo->jugada[0] = inicio;
    tableroModelo->jugada[1] = fin;
}


void Modelo::mueveTablero()
{

    tableroModelo->jugada[0] = jugadaElegida[0];
    tableroModelo->jugada[1] = jugadaElegida[1];

    tableroModelo->cambiaTurno();

    //tableroModelo->jugada[0] = 143-jugadaElegida[0];
    //tableroModelo->jugada[1] = 143-jugadaElegida[1];

   // for(int i=12; i>0;i--)
 //   {
   //     std::cout << int(tableroModelo->casillasInt[(i*12)-12])<<"    "  << int(tableroModelo->casillasInt[(i*12)-11])<<"    " << int(tableroModelo->casillasInt[(i*12)-10])<<"    "<<int(tableroModelo->casillasInt[(i*12)-9])<<"    "<<int(tableroModelo->casillasInt[(i*12)-8])<<"    "<<int(tableroModelo->casillasInt[(i*12)-7])<<"    "<<int(tableroModelo->casillasInt[(i*12)-6])<<"    "<<int(tableroModelo->casillasInt[(i*12)-5]) <<"    " <<int(tableroModelo->casillasInt[(i*12)-4])<<"    " << int(tableroModelo->casillasInt[(i*12)-3])<<"    " << int(tableroModelo->casillasInt[(i*12)-1])<<"    " << int(tableroModelo->casillasInt[(i*12)-1])<<"    " << std::endl;
   // }


}
