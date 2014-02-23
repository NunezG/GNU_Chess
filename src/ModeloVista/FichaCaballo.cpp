#include "../../headers/ModeloVista/FichaCaballo.h"



FichaCaballo::FichaCaballo(std::string nombre, std::string materialName) :
    Ficha(std::string("C_").append(nombre), 2, "Caballo", materialName)




{
    // creaEntidad("Caballo");

}

FichaCaballo::~FichaCaballo()
{


}
