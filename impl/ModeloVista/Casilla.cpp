#include "../../headers/ModeloVista/Casilla.h"

Casilla::Casilla(std::string nombre) :
    esNegra(0)
  //, seleccionada(0)
  , ObjetoOgre("Casilla_"+nombre)
{
}

Casilla::~Casilla()
{   
}

posicion Casilla::getPosicion()
{
    return posCasilla;
}

void Casilla::setPosicion(int posFila, int posCol)
{
    posCasilla.Fila = posFila;
    posCasilla.Columna = posCol;
}

void Casilla::apagaCasilla()
{
  //  getNodoOgre()->showBoundingBox(false);
    if (!esNegra)
    {
        cambiaMaterial("MaterialCasillaBlanca");
    }
    else cambiaMaterial("MaterialCasillaNegra");
}

void Casilla::iluminaCasilla()
{ 
 //   getNodoOgre()->showBoundingBox(true);

    if (esNegra)
    {
        cambiaMaterial("MaterialCasillaNegraIlum");
    }
    else cambiaMaterial("MaterialCasillaBlancaIlum");
}
