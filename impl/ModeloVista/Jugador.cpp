#include "../../headers/ModeloVista/Jugador.h"



Jugador::Jugador(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    //jugadorNegras(false),
    nombre(nombreJugador),
    // miTablero(0)
    //tableroModelo(modeloTablero)
    escena(miEscena)
  //, tablero(miEscena->tablero)
  , modelo(modelo)
  //esperaEleccion(false)
{
    // tablero = escena->tablero;
}

Jugador::~Jugador()
{
}

bool Jugador::casillaSobrevolada(const std::string nombreCasilla)
{
    //  std::cout << "auto1: " << nombreCasilla<< std::endl;
    Casilla* casillaSobrevolada = static_cast<Casilla*>(escena->getTablero()->getHijo(nombreCasilla));
    Casilla* casillaSobreAnterior = escena->getTablero()->getCasillaSobrevolada();
    //   std::cout << "CasillaSobrevolada: "<<   casillaSobrevolada->getNombre()  << std::endl;

    //devulve true si ha cambiado de casilla
    if (!casillaSobreAnterior || casillaSobrevolada->getNombre() != casillaSobreAnterior-> getNombre())
    {
        if (casillaSobreAnterior )
        {
            //     std::cout << "CasillaSobrevolada ANTERIOR: "<<   casillaSobreAnterior->getNombre()  << std::endl;
            escena->apagaVentanaEmergente();

            casillaSobreAnterior->apagaCasilla();
            //tablero->setNodoCasillaSobrevolada(-1);
        }

        //   std::cout << "CAMBIA LA CASILLA SOBREVOLADA: " << std::endl;
        escena->getTablero()->setCasillaSobrevolada(casillaSobrevolada);

        return true;
    }
    return false;
}

std::string Jugador::getNombre()
{
    return nombre;
}

void Jugador::setNombre( std::string unNombre)
{
    nombre = unNombre;
}

int Jugador::jaqueMate()
{
    // tablero->cambiaTurno();
    //    if(tablero->turnoN) tablero->casillasInt = Movimientos::normalizaTablero(tablero->casillasInt);
  //  ModeloTablero* turnoSiguiente = new ModeloTablero(*modelo->tableroModelo);
    bool Jaque = false;
    //   if (turnoNegras)tablero = Calculos::normalizaTablero(tablero);
    Jaque = modelo->tableroModelo->evaluaJaque();  //JAQUE AL REY
    //MIRA TODOS LOS MOVIMIENTOS POSIBLES DEL TURNO CONTRARIO
    if (Autorizaciones::pruebaJaqueMate(modelo->tableroModelo))
    {
      //  delete turnoSiguiente;

        //SE EVALUA EL JAQUE Y SI EL REY NO ESTA EN JAQUE ES QUE ES AHOGADO
        //EVALUA JAQUE
        if (Jaque)
        {            //JAQUE MATE
            return 3;
        }
        else
        { //NO HAY JAQUE, AHOGADO, RESULTADO EN TABLAS
            return 4;
        }
    }
    else
    {
      //  delete turnoSiguiente;
        if (Jaque)
        {//Jaque asecas
            return 2;
        }

        //Mueve
            return 1;
    }
    //FINDE PARTIDA


}



bool Jugador::iniciaTurno()
{
	escena->nombreActivo = nombre;
	return false;
}

bool Jugador::aplicaSeleccion()
{
    //ATUALIZA EL TABLERO DE LA VISTA
    escena->apagaVentanaEmergente();
     modelo->mueveTablero();

	int resultado = jaqueMate();

    escena->getTablero()->actualizaTablero(escena->mSceneMgr);

    //PROMOCIONA PEÓN
    //  escena->getTablero()->promocionaPeon(escena->mSceneMgr);

    //COMPRUEBA JAQUE AL MOVER TABLERO EN MODELO
    modelo->jugadaElegida[0] = 0;
    modelo->jugadaElegida[1] = 0;

    switch (resultado)
    {
    case 2:

        escena->muestraVentanaEmergente("Jaque");
        return true;
    case 3:

		//escena->nom
        escena->muestraVentanaEmergente("JaqueMate");
        return false;
    case 4:

        escena->muestraVentanaEmergente("Tablas");
        return false;
    default: //MOVIMIENTO NORMAL

        return true;
    }  
}