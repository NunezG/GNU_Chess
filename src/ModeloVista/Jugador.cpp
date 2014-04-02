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

    // tablero = escena->tablero;
}

Jugador::~Jugador()
{
}

bool Jugador::casillaSobrevolada(const std::string nombreCasilla)
{
    ObjetoEscena* casillaSobre = escenaMV->getTablero()->objetoPadre->getHijo(nombreCasilla);
    ObjetoEscena* casillaSobreAnterior =  escenaMV->getTablero()->getCasillaSobrevolada();

    //devulve true si ha cambiado de casilla
    if (!casillaSobreAnterior || casillaSobre->getNombre() != casillaSobreAnterior-> getNombre())
    {

        //   if (casillaSobreAnterior )
        //   {
        //       escenaMV->apagaVentanaEmergente();

        //       casillaSobreAnterior->cambiaMaterial(0);
        //tablero->setNodoCasillaSobrevolada(-1);
        //    }

        escenaMV->getTablero()->setCasillaSobrevolada(casillaSobre);

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

    std::cout << "HAY JAUQUE ASECAS PARA EL ENEMIGO DESPUES DE MOVER? "<<Jaque <<std::endl;

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

    escenaMV->getTablero()->actualizaTablero();

    //PROMOCIONA PEÓN
    //  escena->getTablero()->promocionaPeon(escena->mSceneMgr);
    //COMPRUEBA JAQUE AL MOVER TABLERO EN MODELO

    int resultado = jaqueMate();

    std::cout << "RESULTAOD DE JAQUE DESPUES DE MOVER PARA VER SI AMENAZA"<<resultado <<std::endl;


    //HABRA QUE BORRAR BIEN LOS PUNTEROS O NO USARLOS
    modelo->jugadasElegidas = "";




    switch (resultado)
    {
    case 2:
        std::cout << "HAY JAQUEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe"<<std::endl;

        escenaMV->muestraVentanaEmergente("Jaque");
        return true;
    case 3:
        std::cout << "JaqueMateEEESESEESE"<<std::endl;

        //escena->nom
        escenaMV->muestraVentanaEmergente("JaqueMate");
        return false;
    case 4:
        std::cout << "TablaAAAASASASDASDASDASD"<<std::endl;

        escenaMV->muestraVentanaEmergente("Tablas");
        return false;
    default: //MOVIMIENTO NORMAL
        std::cout << "MUEVE N EREROROROARAMMAL"<<std::endl;

        return true;
    }
}
