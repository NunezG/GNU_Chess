#include "../../headers/ModeloVista/FichaReina.h"

FichaReina::FichaReina(std::string nombre) :
    Ficha("D_"+nombre, 5)
{


}
FichaReina::~FichaReina()
{
}

FichaReina::FichaReina( const Ficha& fichaOriginal, std::string nombre):
    Ficha(fichaOriginal, "D_"+nombre, 5)
{
}
