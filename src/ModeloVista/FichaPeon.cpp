#include "../../headers/ModeloVista/FichaPeon.h"



FichaPeon::FichaPeon(std::string nombre, std::string materialName) :
    Ficha(std::string("P_").append(nombre), 1, "Peon", materialName)



{


    //creaEntidad("Peon");

}
FichaPeon::~FichaPeon()
{


}

