#ifndef __FichaReina_
#define __FichaReina_

#include "Ficha.h"


class FichaReina : public Ficha
{
public:

    ~FichaReina(void);
    FichaReina(std::string nombre, std::string materialName);

    //Copia los datos del peón para promocionarlo
    FichaReina( const Ficha& fichaOriginal, std::string nombre );


private:  


};

#endif
