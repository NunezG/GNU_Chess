#include "JugadorArtificial.h"
std::vector<int> JugadorArtificial::resultadoArbol;
int JugadorArtificial::dificultad = 3;

JugadorArtificial::JugadorArtificial(ModeloTablero* modelo, std::string nombreJugador) :
    Jugador( modelo, nombreJugador)
{    
}
JugadorArtificial::~JugadorArtificial()
{
}
/*
bool JugadorArtificial::botonIzquierdo(ObjetoEscena* obj)
{  
    return true;
}
*/


bool JugadorArtificial::iniciaTurno()
{
	std::cout << "INICIA ARTY" << std::endl;

    Jugador::iniciaTurno();

    //delete modelo->mainModelBoard->cambiaTurno()
	std::cout << "LANZARBOLLL" << std::endl;

	lanzaThread();
	std::cout << "RETORNA FALSE" << std::endl;

    return false;
}
/*
bool JugadorArtificial::aplicaSeleccion()
{



    // escenaMV->getTablero()->setCasillaSeleccionada((inicial.Fila * 8) + inicial.Columna);
    // escenaMV->getTablero()->setCasillaSobrevolada((final.Fila* 8) + final.Columna);

    return Jugador::aplicaSeleccion();
}

*/

bool JugadorArtificial::esHumano()
{
    return false;
}





void* JugadorArtificial::lanzaArbol()
{

	

	std::cout << "LANZAAAA ARBOLLLLLLLLLLL" << std::endl;

	//ArbolBusqueda::alphaBeta(mainModelBoard, -990000, 990000, dificultad, "0");
	jugadasElegidas.clear();

//	static 	ModeloTablero* modelo444;



	std::vector<int> jug;
	int resultado = ArbolBusqueda::alphaBeta(modelo, -990000, 990000, dificultad, jug);
	std::cout << "termina arbooollolol" << std::endl;

	// resultado = resultado;
	//std::cout << "JUGGG: " << jug << std::endl;
	std::cout << "JUGGG222: " << (int)jug[0] << " / " << (int)jug[1] << std::endl;

	if (jug.size() == 0)
	{//SIN RESULTADO
		std::cout << "SIN RESULTADO RESULTADO" << std::endl;

		//return false;
	}
	std::cout << "ACABAAAAAAATOTATAL en lanzaarbool" << std::endl;
	jugadasElegidas = jug;
	//join();
	return NULL;
}



void JugadorArtificial::lanzaThread()
{
	std::cout << "LANZAAAA THREAADDDD" << std::endl;


	//int resultado = ArbolBusqueda::alphaBeta(mainModelBoard, -990000, 990000, dificultad);

	// resultado = resultado;
	std::thread t1(lanzaArbol);

	t1.detach();

	if (jugadasElegidas.size() == 0)
	{//SIN RESULTADO
		//return false;
	}
	std::cout << "ACABAAAAAAATOTATAL en lanzathread" << std::endl;

}