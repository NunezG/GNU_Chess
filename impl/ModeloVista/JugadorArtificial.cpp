#include "../../headers/ModeloVista/JugadorArtificial.h"

JugadorArtificial::JugadorArtificial(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    Jugador(miEscena, modelo, nombreJugador)
{    
}
JugadorArtificial::~JugadorArtificial()
{
}

bool JugadorArtificial::botonIzquierdo(CEGUI::Vector2<float> pos)
{  
	return true;
}

bool JugadorArtificial::botonDerecho()
{ 
	return true;
}

bool JugadorArtificial::iniciaTurno()
{
	Jugador::iniciaTurno();

    //delete modelo->tableroModelo->cambiaTurno()

    int resultado = ArbolBusqueda::alphaBeta(modelo->tableroModelo,-990000, 990000, modelo->dificultad );

    // resultado = resultado;

    if (modelo->jugadaElegida[0] == modelo->jugadaElegida[1])
    {//SIN RESULTADO
        return false;
    }

    return true;
}

bool JugadorArtificial::aplicaSeleccion()
{
    posicion inicial;
    posicion final;

    inicial.Fila = (modelo->jugadaElegida[0]/12)-2;
    inicial.Columna = (modelo->jugadaElegida[0]%12)-2;
    final.Fila = (modelo->jugadaElegida[1]/12)-2;
    final.Columna = (modelo->jugadaElegida[1]%12)-2;

    if (modelo->tableroModelo->turnoN)
    {//INVIERTE
          inicial.Fila = 7-inicial.Fila;
          inicial.Columna =  7-inicial.Columna;
          final.Fila = 7-final.Fila;
          final.Columna =  7-final.Columna;  
      }

    escena->getTablero()->setCasillaSeleccionada((inicial.Fila * 8) + inicial.Columna);
    escena->getTablero()->setCasillaSobrevolada((final.Fila* 8) + final.Columna);

    return Jugador::aplicaSeleccion();
}

bool JugadorArtificial::esHumano()
{
    return false;
}
