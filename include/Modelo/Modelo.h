#ifndef __Modelo_
#define __Modelo_

//#include "ArbolBusqueda.h"
//#include "Autorizaciones.h"
#include "ModeloTablero.h"


class Modelo
{
public:
    ~Modelo(void);
    //Singleton
    static Modelo* getSingletonPtr();
			  		std::string posInicial;

    void mueveTablero();

    ModeloTablero* tableroModelo;

	std::string jugadasElegidas;
	std::string listaCambios;




	    int dificultad;

private:
	int jaqueMate();

    //Singleton;
    Modelo(void);
    void operator=(const Modelo& miModelo) ;
    Modelo(const Modelo& miModelo);
};

#endif
