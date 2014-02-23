#ifndef __Casilla_
#define __Casilla_

#include <iostream>
#include <vector>

//#include "ObjetoEscena.h"


struct posicion{
    int Fila;
    int Columna;

};


class Casilla //: public ObjetoEscena
{
public:
    ~Casilla(void);
    Casilla(std::string nombre, std::string material);

    void setPosicion(int posFila, int posCol);
    posicion getPosicion();
    void apagaCasilla();
    void iluminaCasilla();

    bool esNegra;

   // std::string getNombre();
private:

    posicion posCasilla;
	
   // std::string nombreObjeto;
};

#endif
