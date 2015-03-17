#ifndef __Autorizaciones_
#define __Autorizaciones_

#include "Movimientos.h"

class Autorizaciones
{
public:
	    static bool pruebaJaqueMate(ModeloTablero* miTablero);


	  static int autorizaCasilla();
	  static std::vector<int> casillasAutorizadas(ModeloTablero* mainModelBoard, int posicion);
/*
    static int autorizaRey(ModeloTablero* miTablero);
    static int autorizaReina(ModeloTablero* miTablero);
    static int autorizaPeon(ModeloTablero* miTablero);
    static int autorizaAlfil(ModeloTablero* miTablero);
    static int autorizaTorre(ModeloTablero* miTablero);
    static int autorizaCaballo(ModeloTablero* miTablero);

*/
	//static bool pruebaJaqueMate(ModeloTablero* miTablero);




private:
    static int pruebaCamino(ModeloTablero* miTablero, int salto);

};

#endif
