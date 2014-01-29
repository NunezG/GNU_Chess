#ifndef __TableroMV_
#define __TableroMV_
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
//#include "ObjetoEscena.h"
#include "Casilla.h"
#include "FichaAlfil.h"
#include "FichaCaballo.h"
#include "FichaTorre.h"
#include "FichaReina.h"
#include "FichaRey.h"
#include "FichaPeon.h"
#include "../Modelo/Modelo.h"

#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
/*
struct TableroMVPrueba{
    Ogre::String Tipo;
    Ogre::Entity* entTableroMV;
    bool esNegra;
    bool muerta;
    int casilla[2];
};

struct ListaPosiciones{
    ListaPosiciones* anterior;
    int posicion[2];
};
*/

enum enColummas{
    COL_A,
    COL_B,
    COL_C,
    COL_D,
    COL_E,
    COL_F,
    COL_G,
    COL_H

};


class TableroMV : public ObjetoEscena
{
public:

    ~TableroMV(void);
    //constructor de copia
    TableroMV(const TableroMV& TableroMVOriginal, std::string nombre, int tipo);
    //void creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask);
    int tipo_TableroMV;
    bool esNegra;
	bool seleccionada;
    void apaga();
    void ilumina();

	  int getAlPaso();
    void setAlPaso(int casilla);
    Casilla* getCasillaSeleccionada();
    Casilla* getCasillaSobrevolada();
    void setCasillaSeleccionada(Casilla* nodo);
    void setCasillaSobrevolada(Casilla* nodo);
    void setCasillaSeleccionada(int posicion);
    void setCasillaSobrevolada(int posicion);
	    TableroMV(std::string nombre, int tipo);
			void creaPiezas();
			Modelo* modelo;
			    void creaCasillas();

protected:
private: 
   // virtual bool setCasilla(int fila, int col);
   // bool salto;
  //  bool Selected;
    //PARA EVALUAR:
  //  bool Moved;
 //   short PieceActionValue;
  //  short AttackedValue;
 //   short DefendedValue;
 //   short valorTableroMV;
   //  Stack<byte> ValidMoves; // lista de movimientos válidos
   // bool muerta;
    //int casilla[2];
	int alPaso;
    Casilla* casillaSeleccionada;
    Casilla* casillaSobrevolada;

	    bool fichaSeleccionada;
		int peonesPromocionados;

	    std::string nombreObjeto;


    //ObjetoOgre* objetoOgreAsociado;
};

#endif
