#include "../../headers/ModeloVista/FichaAlfil.h"



FichaAlfil::FichaAlfil(std::string nombre, std::string materialName) :
    Ficha(std::string("A_").append(nombre), 3, "Alfil", materialName)

   // ,casilla(0)

{

   // creaEntidad("Alfil");
}

FichaAlfil::~FichaAlfil()
{


}



