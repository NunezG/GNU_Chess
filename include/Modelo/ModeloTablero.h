#ifndef __ModeloTablero_
#define __ModeloTablero_

#include <algorithm>    // std::for_each
#include <deque>       // std::deque
#include <vector>       // std::list
#include <array>
#include <unordered_map>

#include <iostream>
#include <string>
#include <map>
//#include "Autorizaciones.h"

/*
*
0 = Vacio
99 = Fuera del tablero
1 = (amiga) Peon
2 =(amiga) Caballo
3 =(amiga) Alfil
4 = (amiga) Torre
5 = (amiga) Reina
6 = (amiga) Rey

-1 = (enemiga) Peon
-2 =(enemiga) Caballo
-3 =(enemiga) Alfil
-4 = (enemiga) Torre
-5 = (enemiga) Reina
-6 = (enemiga) Rey
*/


enum tipoFicha
{
    Vacio,
    Peon,
    Caballo,
    Alfil,
    Torre,
    Reina,
    Rey
};


struct ModeloTablero
{   
    // StringClass(char *ptr);
    ModeloTablero(std::string posicion);
    ~ModeloTablero();

    //constructor de copia
    ModeloTablero( const ModeloTablero& original);
    bool evaluaJaque();

   // std::vector<ModeloTablero*> vectorMov;
	bool cambiaTurno(std::vector<int> vectorJugada);
	void generaTablero();
    //* movIniciales;

    // unsigned char* test[2];

	//int casillaSeleccionada;
	//std::vector<int> vectorJugada;

	//std::vector<std::vector<int>> vectorJugadas2;


	
	std::map < int, std::vector<std::vector<int>> > testMapJugadas;

    //std::vector<unsigned char[]> vectorJugadas2;
	void borraJugadas();

   // int numCasillasProtegidas;

    //HACER EN LISTA O VECTOR PARA QUE HAYA TAMAÑO??
	//std::vector<std::array<int, 2>> casillasProtegidas;
	std::unordered_map<int, int> casillasProtegidas;
	//std::array<int, 16> casillasProtegidas = std::array<int, 16>();

	std::array<char, 144> casillasInt;
    //std::string jugadas;
	//char jugadaPrincipal[2];
    unsigned char alPaso;
    bool turnoN;
    bool nodoInicial;
	

    // Ficha* fichasNegras[16];
    // Ficha* fichasBlancas[16];
    short valorAtaque; //ligado al movimiento, la suma de valores de las fichas implicadas
    short valorAmenaza; //por si amenaza a una pieza enemiga
    //short valorDefensivo; //por si defiende una pieza amiga

	std::array<char, 144> invierteTablero(std::array<char, 144> casillasInt);

	int score;
private:

};
#endif
