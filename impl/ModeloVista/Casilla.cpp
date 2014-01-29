#include "../../headers/ModeloVista/Casilla.h"

Casilla::Casilla(std::string nombre, std::string material) : ObjetoEscena(nombre, CASILLA, "Casilla", material)
   , esNegra(0)
  //, seleccionada(0)
{
}

Casilla::~Casilla()
{   
}


std::string Casilla::getNombre()
{
    return nombreObjeto;
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
   /* if (!esNegra)
    {
        cambiaMaterial("MaterialCasillaBlanca");
    }
    else cambiaMaterial("MaterialCasillaNegra");
	*/
}

void Casilla::iluminaCasilla()
{ 
 //   getNodoOgre()->showBoundingBox(true);
  /*
    if (esNegra)
    {
        cambiaMaterial("MaterialCasillaNegraIlum");
    }
    else cambiaMaterial("MaterialCasillaBlancaIlum");
	*/
}
