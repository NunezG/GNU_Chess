#include "../../headers/ModeloVista/FichaReina.h"

FichaReina::FichaReina(std::string nombre, std::string materialName) :
    Ficha(std::string("D_").append(nombre), 5, "Reina" , materialName)
{


}
FichaReina::~FichaReina()
{
}

FichaReina::FichaReina( const Ficha& fichaOriginal, std::string nombre):
    Ficha(fichaOriginal,std::string("D_").append(nombre), 5)
{
}
