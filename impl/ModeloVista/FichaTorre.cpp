#include "../../headers/ModeloVista/FichaTorre.h"



FichaTorre::FichaTorre(std::string nombre, std::string materialName) :
    Ficha(std::string("T_").append(nombre), 4, "Torre", materialName)



{
    //creaEntidad("Torre");

}
FichaTorre::~FichaTorre()
{


}
