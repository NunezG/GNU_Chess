#include "../../headers/ModeloVista/FichaRey.h"



FichaRey::FichaRey(std::string nombre, std::string materialName) :
    Ficha(std::string("R_").append(nombre), 6, "Rey", materialName)



{
    //creaEntidad("Rey");

}
FichaRey::~FichaRey()
{


}


