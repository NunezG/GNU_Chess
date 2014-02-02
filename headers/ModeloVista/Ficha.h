#ifndef __Ficha_
#define __Ficha_
#include <iostream>
#include <string>
#include <stdlib.h>
//#include "ObjetoOgre.h"
#include "ObjetoEscena.h"

/*
struct FichaPrueba{
    Ogre::String Tipo;
    Ogre::Entity* entFicha;
    bool esNegra;
    bool muerta;
    int casilla[2];
};

struct ListaPosiciones{
    ListaPosiciones* anterior;
    int posicion[2];
};
*/

class Ficha //: public ObjetoEscena
{
public:

    ~Ficha(void);
    //constructor de copia
    Ficha(const Ficha& fichaOriginal, std::string nombre, int tipo);
    //void creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask);
    int tipo_Ficha;
    bool esNegra;
	bool seleccionada;
    void apaga();
    void ilumina();
	   // std::string getNombre();
    Ficha(std::string nombre, int tipo, std::string meshName, std::string materialName);

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
 //   short valorFicha;
   //  Stack<byte> ValidMoves; // lista de movimientos válidos
   // bool muerta;
    //int casilla[2];
	   // std::string nombreObjeto;


    //ObjetoOgre* objetoOgreAsociado;
};

#endif
