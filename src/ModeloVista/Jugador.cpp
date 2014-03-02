#include "Jugador.h"



Jugador::Jugador(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    //jugadorNegras(false),
    nombre(nombreJugador),
    // miTablero(0)
    //tableroModelo(modeloTablero)
    escenaMV(miEscena)
  //, tablero(miEscena->tablero)
  , modelo(modelo)
  //esperaEleccion(false)
{
			    				    std::cout << "Jugadorrr "<<std::endl;

    // tablero = escena->tablero;
}

Jugador::~Jugador()
{
}

bool Jugador::casillaSobrevolada(const std::string nombreCasilla)
{
      std::cout << "auto1: " << nombreCasilla<< std::endl;
	  ObjetoEscena* casillaSobre = escenaMV->getTablero()->objetoPadre->getHijo(nombreCasilla);
    ObjetoEscena* casillaSobreAnterior =  escenaMV->getTablero()->getCasillaSobrevolada();
      std::cout << "CasillaSobrevolada: "<<   casillaSobre->getNombre()  << std::endl;

    //devulve true si ha cambiado de casilla
    if (!casillaSobreAnterior || casillaSobre->getNombre() != casillaSobreAnterior-> getNombre())
    {
		      std::cout << "poozzzz: "<<    std::endl;

     //   if (casillaSobreAnterior )
     //   {
      //           std::cout << "CasillaSobrevolada ANTERIOR: "<<   casillaSobreAnterior->getNombre()  << std::endl;
      //       escenaMV->apagaVentanaEmergente();

     //       casillaSobreAnterior->cambiaMaterial(0);
            //tablero->setNodoCasillaSobrevolada(-1);
    //    }

           std::cout << "CAMBIA LA CASILLA SOBREVOLADA: " << std::endl;
         escenaMV->getTablero()->setCasillaSobrevolada(casillaSobre);
		            std::cout << "CAMBIA Lfin" << std::endl;

        return true;
    }

			  						std::cout << "no cambia de casilla"<<std::endl;

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
	 escenaMV->nombreActivo = nombre;
	return false;
}

bool Jugador::aplicaSeleccion()
{


    //ATUALIZA EL TABLERO DE LA VISTA
     escenaMV->apagaVentanaEmergente();
     modelo->mueveTablero();

	int resultado = jaqueMate();
	
     escenaMV->getTablero()->actualizaTablero();

    //PROMOCIONA PEÓN
    //  escena->getTablero()->promocionaPeon(escena->mSceneMgr);

    //COMPRUEBA JAQUE AL MOVER TABLERO EN MODELO
    modelo->jugadaElegida[0] = 0;
    modelo->jugadaElegida[1] = 0;


															   	std::cout << "result aplicaseleccion"<<  resultado <<std::endl;


    switch (resultado)
    {
    case 2:
												   	std::cout << "Jaque"<<std::endl;

        escenaMV->muestraVentanaEmergente("Jaque");
        return true;
    case 3:
												   	std::cout << "JaqueMate"<<std::endl;

		//escena->nom
        escenaMV->muestraVentanaEmergente("JaqueMate");
        return false;
    case 4:
												   	std::cout << "Tablas"<<std::endl;

        escenaMV->muestraVentanaEmergente("Tablas");
        return false;
    default: //MOVIMIENTO NORMAL
														   	std::cout << "normal"<<std::endl;

        return true;
    }  
}