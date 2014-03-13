#include "../../include/ModeloVista/JugadorHumano.h"

JugadorHumano::JugadorHumano(EscenaAjedrez* miEscena, Modelo* modelo, std::string nombreJugador) :
    Jugador(miEscena, modelo, nombreJugador)
{ 

}

JugadorHumano::~JugadorHumano()
{ 
}

bool JugadorHumano::botonIzquierdo(ObjetoEscena* obj)
{

    /*
    if (escena->getTablero()->getCasillaSeleccionada() != NULL)
    {  // Si habia alguno seleccionado...
        Ficha* ficha = static_cast<Ficha*>(escena->getTablero()->getCasillaSeleccionada()->getHijo(0));
       //ficha->getNodoOgre()->showBoundingBox(false);
        escena->getTablero()->setCasillaSeleccionada(-1);
    }

    */




    //apagaCasillas();

    if (!jugadasResaltadas.empty())
    {
        bool movimiento = false;
        for (std::vector<int>::iterator it = jugadasResaltadas.begin(); it!=jugadasResaltadas.end(); it++)
        {
            int jugada = *it;



            //LA JUGADA ESTA AUTORIZADA
            if(jugada == 24 + (obj->getPosicion().Fila * 12) + obj->getPosicion().Columna + 2)
            {


                char jug[2];
                jug[0] = modelo->tableroModelo->jugadaPrincipal[0];
                jug[1] = jugada;
                modelo->jugadasElegidas.append(jug);
                // modelo->jugadaElegida[1] = ;
                movimiento = true;

            }

            //APAGA CASILLA
            ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada/12)-2)*8 + ((jugada%12)-2));
            ob->cambiaMaterial(0);

        }


        //apaga objeto seleccionado
        //ObjetoEscena* ficha = escenaMV->getTablero()->objetoPadre->getHijo(((modelo->tableroModelo->jugada[0]/12)-2)*8 + ((modelo->tableroModelo->jugada[0]%12)-2))->getHijo(0);
        escenaMV->getTablero()->getCasillaSeleccionada()->getHijo(0)->cambiaMaterial(0);


        //Borra jugadas
        jugadasResaltadas.clear();

        if (movimiento)
        {





            return true;
        }
    }


    //if (escenaMV->getTablero()->getCasillaSeleccionada())



    if(!obj->numHijos() == 0)
    {

        ObjetoEscena* ficha = obj->getHijo(0);
        if ((modelo->tableroModelo->turnoN
             && ficha->mask == NEGRAS)
                || (!modelo->tableroModelo->turnoN
                    && ficha->mask == BLANCAS))
        {


            escenaMV->getTablero()->setCasillaSeleccionada(obj);

            fichaPulsada();


            // ficha->getNodoOgre()->showBoundingBox(true);
            return true;
        }
    }
    return false;
}






bool JugadorHumano::apagaCasillas()
{

    //Apaga casillas
    if (!jugadasResaltadas.empty())
    {
        for (std::vector<int>::iterator it = jugadasResaltadas.begin(); it!=jugadasResaltadas.end(); it++)
        {
            int jugada = *it;

            ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada/12)-2)*8 + ((jugada%12)-2));
            ob->cambiaMaterial(0);

        }
    }

    return true;
}



bool JugadorHumano::fichaPulsada()
{

    ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();

    if (nodoSeleccionado != NULL)
    {




        modelo->tableroModelo->jugadaPrincipal[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        // modelo->tableroModelo->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;




        //AUTORIZA
        jugadasResaltadas =  Autorizaciones::casillasAutorizadas();
        std::cout << "casca?"<<std::endl;

        // int resultado = Autorizaciones::autorizaCasilla();

        if (!jugadasResaltadas.empty())
        {

            for (std::vector<int>::iterator it = jugadasResaltadas.begin(); it!=jugadasResaltadas.end(); it++)
            {
                int jugada = *it;

                ObjetoEscena* ob = escenaMV->getTablero()->objetoPadre->getHijo(((jugada/12)-2)*8 + ((jugada%12)-2));



                if (ob->numHijos() > 0)
                    ob->cambiaMaterial(2);
                else ob->cambiaMaterial(1);


                // CASILLA AUTORIZADA
                //  escenaMV->getTablero()->getCasillaSobrevolada()->cambiaMaterial(1);

            }

            return true;
        }
        else
        {
            // CASILLA PROHIBIDA
            modelo->tableroModelo->jugadaPrincipal[0] = -1;
            
            return false;
        }

    }

}

/*
bool JugadorHumano::casillaSobrevolada(const std::string nombreCasilla)
{
                 ObjetoEscena* nodoSeleccionado = escenaMV->getTablero()->getCasillaSeleccionada();


    if (nodoSeleccionado != NULL && Jugador::casillaSobrevolada(nombreCasilla))
    {
    if   (escenaMV->getTablero()->getCasillaSobrevolada()->numHijos() == 0 || escenaMV->getTablero()->getCasillaSobrevolada()->getHijo(0)->mask != nodoSeleccionado->getHijo(0)->mask)
    {


        // if(diferencia.Fila != 0)   diferencia= diferencia;
        // else diferencia= diferenciaZ;

       // ObjetoEscena *mFicha = nodoSeleccionado->getHijo(0);

      //  tipoFicha tipo = tipoFicha(mFicha->tipo_Ficha);

        //   tableroModelo->casillasInt = tablero->traduceTablero();



        modelo->tableroModelo->jugada[0] = 24 + (nodoSeleccionado->getPosicion().Fila * 12) + nodoSeleccionado->getPosicion().Columna + 2;
        modelo->tableroModelo->jugada[1] = 24 + (escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Fila * 12) + escenaMV->getTablero()->getCasillaSobrevolada()->getPosicion().Columna + 2;

        //AUTORIZA
        int resultado = Autorizaciones::autorizaCasilla();

        if (resultado == 1)
        {
            modelo->jugadaElegida[0] = modelo->tableroModelo->jugada[0];
            modelo->jugadaElegida[1] = modelo->tableroModelo->jugada[1];


            // CASILLA AUTORIZADA
            escenaMV->getTablero()->getCasillaSobrevolada()->cambiaMaterial(1);
            return true;
        }
        else
        {

            // CASILLA PROHIBIDA
            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;
            modelo->jugadaElegida[0] = -1;
            modelo->jugadaElegida[1] = -1;


            if (resultado == 2)
            {
                //JAQUE AL SOBREVOLAR CASILLA
                escenaMV->muestraVentanaEmergente("Jaque");
            }
            return false;
        }

    }else
    {
            // CASILLA DEL MISMO TIPO
            modelo->tableroModelo->jugada[0] = -1;
            modelo->tableroModelo->jugada[1] = -1;
            modelo->jugadaElegida[0] = -1;
            modelo->jugadaElegida[1] = -1;
        return false;
    }

    }

}
*/
bool JugadorHumano::esHumano()
{
    return true;
}

