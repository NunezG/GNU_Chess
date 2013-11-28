#ifndef __Casilla_
#define __Casilla_

#include "ObjetoOgre.h"


struct posicion{
    int Fila;
    int Columna;

};


class Casilla : public ObjetoOgre
{
public:
    ~Casilla(void);
    Casilla(std::string nombre);

    void setPosicion(int posFila, int posCol);
    posicion getPosicion();
    void apagaCasilla();
    void iluminaCasilla();

    bool esNegra;


private:

    posicion posCasilla;

};

#endif
