#ifndef __ModeloTablero_
#define __ModeloTablero_

#include <algorithm>    // std::for_each
#include <deque>       // std::deque
#include <vector>       // std::list

#include <iostream>
#include <string>
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
    bool cambiaTurno();
	void generaTablero();
    //* movIniciales;

    // unsigned char* test[2];

    std::vector<std::string> vectorJugadas;
    std::vector<std::string> vectorJugadasPeores;
    std::vector<std::string> vectorJugadasNormales;

    //std::vector<unsigned char[]> vectorJugadas2;
	void borraJugadas();

    int numCasillasProtegidas;

    //HACER EN LISTA O VECTOR PARA QUE HAYA TAMAÑO??
    std::vector<char*> casillasProtegidas;
    char casillasInt[144];
    std::string jugadas;
	char jugadaPrincipal[2];
    unsigned char alPaso;
    bool turnoN;
    bool nodoInicial;
	

    // Ficha* fichasNegras[16];
    // Ficha* fichasBlancas[16];
    short valorAtaque; //ligado al movimiento, la suma de valores de las fichas implicadas
    short valorAmenaza; //por si amenaza a una pieza enemiga
    short valorDefensivo; //por si defiende una pieza amiga

	char* invierteTablero(char casillas[144]);


private:

};
#endif
