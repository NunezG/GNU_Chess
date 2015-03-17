#include "Modelo.h"
std::string Modelo::posInicial("bcdefdcbaaaaaaaa00000000000000000000000000000000zzzzzzzzyxwvuwxy");

ModeloTablero* Modelo::mainModelBoard = new ModeloTablero(posInicial);


Modelo::Modelo() :
    //jugadaAutorizada(false)
    // ,nombreBlancas("Jugador 1")
    //, nombreNegras("Jugador 2")
    //,  jugadores(NULL)
 
	 JugadorActivo(0)

	, jugadores(0)

{   
    //mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MIMANAGERDEESCENA");

	nombres[0] = "Jugador 1";
	nombres[1] = "Jugador 2";
}

Modelo::~Modelo()
{
	borraJugadores();

}

Modelo* Modelo::getSingletonPtr()
{
    static Modelo miModelo;
    static Modelo* miModeloPtr = &miModelo;
    return miModeloPtr;
}



bool Modelo::jugadaElegida()
{
	if (JugadorActivo->jugadasElegidas.size() > 1 ) std::cout << "jugadaElegida.size?: " << JugadorActivo->jugadasElegidas.size() << std::endl;

	return JugadorActivo->jugadasElegidas.size() > 1;
}

void Modelo::cambiaTurno()
{
	JugadorActivo->jugadasElegidas.clear();
	//CAMBIA JUGADOR ACTIVO
	JugadorActivo = jugadores.at(mainModelBoard->turnoN);

	//HABRA QUE USAR OTRO THREAD
	JugadorActivo->iniciaTurno();
	
    //mainModelBoard->jugada[0] = 143-jugadaElegida[0];
    //mainModelBoard->jugada[1] = 143-jugadaElegida[1];




}


int Modelo::getTipoJuego()
{
	return tipoJuego;
}


void Modelo::setTipoJuego(int tipo)
{
	tipoJuego = tipo;
}


void Modelo::generaJugadores()
{


	jugadores.push_back(new JugadorHumano(mainModelBoard, nombres[0]));


	//HAY QUE CAMBIAR LO DE MODELOTABKERO PORQUE LOS JUGADORES ESTAN EN UN VECTOR Y ESE ES EL PROBLEMA
	if (getTipoJuego() == 1)
	{
		jugadores.push_back(new JugadorHumano(mainModelBoard, nombres[1]));
	}
	else
	{
		jugadores.push_back(new JugadorArtificial(mainModelBoard, nombres[1]));
		//modelo->dificultad = (2 * dificultad) + 1;
	}

	if (JugadorActivo == NULL)
	{
		JugadorActivo = jugadores.at(0);
		//  jugadores.at(num)->jugadorNegras = 0;
	}

}


void Modelo::borraJugadores()
{


	for (std::vector<Jugador*>::iterator it = jugadores.begin(); it != jugadores.end(); it++)
	{
		Jugador* jugador = *it;
		delete jugador;
		jugador = NULL;
	}



	jugadores.clear();


}

