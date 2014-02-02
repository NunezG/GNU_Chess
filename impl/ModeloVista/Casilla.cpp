#include "../../headers/ModeloVista/Casilla.h"

Casilla::Casilla(std::string nombre, std::string material) :// ObjetoEscena(nombre, CASILLA, "Casilla", material, )
    esNegra(0)
  //, seleccionada(0)
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
      //  materialName = ("MaterialCasillaBlanca");
    }
	else {}//materialName = ("MaterialCasillaNegra");
	
}

void Casilla::iluminaCasilla()
{ 
 //   getNodoOgre()->showBoundingBox(true);
  
    if (esNegra)
    {
        //materialName = ("MaterialCasillaNegraIlum");
    }
	else{}// materialName = ("MaterialCasillaBlancaIlum");
	
}
