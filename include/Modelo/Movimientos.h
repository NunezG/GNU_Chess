#ifndef __Movimientos_
#define __Movimientos_

#include "ModeloTablero.h"
#include <list>
#include <map>
class Movimientos
{
public:
	static bool generaMovimientos(ModeloTablero* miTablero); 
	static bool movimientosUnaFicha(ModeloTablero* miTablero, int posicion);

private:
	static int casillaSeleccionada;

	static std::vector<int> vectorJugada;
	static std::vector<std::vector<int>> vectorJugadas;
	static std::vector<std::vector<int>> vectorJugadasPeores;
	static std::vector<std::vector<int>> vectorJugadasNormales;
   // bool myfunction (unsigned char* primeraJugada, unsigned char* segundaJugada);

	  //0: para nada encontrado, 1: para ficha amiga encontrada, 2: para ficha enemiga encontrada
    static bool recorreCasillas(ModeloTablero* miTablero, int salto);
	static bool movUnico(ModeloTablero* miTablero, int salto);
	static bool soloMov(ModeloTablero* miTablero, int salto);

    static void nuevoMovimiento(ModeloTablero *miTablero);

  //  static bool mueveFicha(ModeloTablero* miTablero, char tipo);
    static bool mueveTorre(ModeloTablero* miTablero);
    static bool mueveAlfil(ModeloTablero* miTablero);
    static bool mueveCaballo(ModeloTablero* miTablero);
    static bool mueveReina(ModeloTablero* miTablero);
    static bool muevePeon(ModeloTablero* miTablero);
    static bool mueveRey(ModeloTablero* miTablero);

	static void updateHashMap(ModeloTablero* miTablero);

	static void  casillaProtegida(int casillaProtectora, ModeloTablero* miTablero);

};

#endif
