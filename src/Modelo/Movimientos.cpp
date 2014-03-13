#include "Movimientos.h"

bool Movimientos::generaMovimientos(ModeloTablero* miTablero)
{
    // ModeloTablero nuevoTablero;
    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    bool fichamovida = false;
    
    //CADA VEZ QUE ENCUENTRA UNA FICHA APLICA SUS MOVIMIENTOS
    //  for (int i = 26; i< 118;i++)
    //  {

    // }

    for (int i = 117; i > 25;i--)
    {
        //  int casilla = (i*12)+y;
        char valorCasilla = miTablero->casillasInt[i];

        if (miTablero->turnoN) valorCasilla = -valorCasilla;

        if (valorCasilla > 0)
        {
            miTablero->jugadaPrincipal[0] = i;

            // bool fichamovida = false;
            bool resultado = false;
            switch (tipoFicha(valorCasilla))
            {
            case (Rey):

                //ENCUENTRA REY
                resultado = mueveRey(miTablero);
                break;
            case Reina:
                //ENCUENTRA REINA
                resultado = mueveReina(miTablero);
                break;
            case Torre:
                //ENCUENTRA TORRE
                resultado = mueveTorre(miTablero);
                break;
            case Alfil:
                //ENCUENTRA ALFIL

                resultado = mueveAlfil(miTablero);
                break;
            case Caballo:
                //ENCUENTRA CABALLO

                resultado = mueveCaballo(miTablero);
                break;
            case Peon:
                //ENCUENTRA PEON

                resultado = muevePeon(miTablero);
                break;
            default:
                break;
            }
            // bool resultado = mueveFicha(miTablero, );
            if (fichamovida == false) fichamovida = resultado;
        }
    }

    miTablero->vectorJugadas.reserve( miTablero->vectorJugadasNormales.size() + miTablero->vectorJugadasPeores.size() ); // preallocate memory
    miTablero->vectorJugadas.insert( miTablero->vectorJugadas.end(), miTablero->vectorJugadasNormales.begin(), miTablero->vectorJugadasNormales.end() );
    miTablero->vectorJugadas.insert( miTablero->vectorJugadas.end(), miTablero->vectorJugadasPeores.begin(), miTablero->vectorJugadasPeores.end() );

    miTablero->vectorJugadasNormales.clear();
    miTablero->vectorJugadasPeores.clear();

    return fichamovida;
}


bool Movimientos::movimientosUnaFicha(ModeloTablero* miTablero)
{
    // ModeloTablero nuevoTablero;
    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    bool fichamovida = false;
    
    //CADA VEZ QUE ENCUENTRA UNA FICHA APLICA SUS MOVIMIENTOS
    //  for (int i = 26; i< 118;i++)
    //  {

    // }


    //  int casilla = (i*12)+y;


    char valorCasilla = miTablero->casillasInt[miTablero->jugadaPrincipal[0]];

    if (miTablero->turnoN) valorCasilla = -valorCasilla;


    // bool fichamovida = false;
    bool resultado = false;
    switch (tipoFicha(valorCasilla))
    {
    case (Rey):

        //ENCUENTRA REY
        resultado = mueveRey(miTablero);
        break;
    case Reina:
        //ENCUENTRA REINA
        resultado = mueveReina(miTablero);
        break;
    case Torre:
        //ENCUENTRA TORRE
        resultado = mueveTorre(miTablero);
        break;
    case Alfil:
        //ENCUENTRA ALFIL

        resultado = mueveAlfil(miTablero);
        break;
    case Caballo:
        //ENCUENTRA CABALLO

        resultado = mueveCaballo(miTablero);
        break;
    case Peon:
        //ENCUENTRA PEON

        resultado = muevePeon(miTablero);
        break;
    default:
        break;
    }
    // bool resultado = mueveFicha(miTablero, );
    if (fichamovida == false) fichamovida = resultado;


    miTablero->vectorJugadas.reserve( miTablero->vectorJugadasNormales.size() + miTablero->vectorJugadasPeores.size() ); // preallocate memory
    miTablero->vectorJugadas.insert( miTablero->vectorJugadas.end(), miTablero->vectorJugadasNormales.begin(), miTablero->vectorJugadasNormales.end() );
    miTablero->vectorJugadas.insert( miTablero->vectorJugadas.end(), miTablero->vectorJugadasPeores.begin(), miTablero->vectorJugadasPeores.end() );

    miTablero->vectorJugadasNormales.clear();
    miTablero->vectorJugadasPeores.clear();

    return fichamovida;
}


/*
bool Movimientos::myfunction (unsigned char* primeraJugada, unsigned char* segundaJugada)
{
    return (segundaJugada[1] < primeraJugada[1]);
}

*/


//HABRA QUE REALIZAR TODOS LOS MOVIMIENTOS CON LA TABLA ACTUAL Y PONERLOS EN UN ARBOL? HACERLO RECURSIVO?
bool Movimientos::mueveReina(ModeloTablero* miTablero)
{
    // bool reinaMovida = false;

    bool torre = mueveTorre(miTablero);
    bool alfil = mueveAlfil(miTablero);
    
    // if (testJaque)
    //{
    return (torre || alfil);
    // }
    
}

bool Movimientos::muevePeon(ModeloTablero* miTablero)
{
    bool muevePeon = false;
    char casilla  = miTablero->jugadaPrincipal[0];
    char nuevaCasilla = casilla+12;
    char casillaCome = casilla+11;
    char casillaComeSec = casilla+13;
    char salto = casilla+24;

    if (miTablero->turnoN)
    {
        nuevaCasilla = casilla-12;
        casillaCome = casilla-11;
        casillaComeSec = casilla-13;
        salto = casilla-24;

    }
    // int filaPeon = 3;
    //int filaPromocion = 9;
    
    //MOVIMIENTO NORMAL
    if(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugadaPrincipal[1] = nuevaCasilla;
        miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
        std::cout << "MUEVE NORMAL : "  <<  miTablero->jugadas  <<std::endl;

        std::cout << "MUEVE NORMAL2 : "  <<  miTablero->jugadaPrincipal  <<std::endl;

        std::cout << "MUEVE NORMAL4 : "  <<  miTablero->jugadaPrincipal[0]  << " / "<< miTablero->jugadaPrincipal[1]  <<std::endl;

        std::cout << "MUEVE NORMAL4 : "  <<  (int)miTablero->jugadaPrincipal[0]  << " / "<< (int)miTablero->jugadaPrincipal[1]  <<std::endl;


        nuevoMovimiento(miTablero);
        muevePeon = true;
    }
    
    //DOBLE SALTO
    if(((!miTablero->turnoN && casilla/12 == 3) || (miTablero->turnoN && casilla/12 == 8)) && miTablero->casillasInt[nuevaCasilla] == 0 && miTablero->casillasInt[salto] == 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugadaPrincipal[1] = salto;
        miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
        std::cout << "MUEVE SALTO " <<std::endl;

        nuevoMovimiento(miTablero);
        muevePeon = true;

    }
    
    int numProtegidas = 0;
    
    //COME ENEMIGA
    if ((!miTablero->turnoN && miTablero->casillasInt[casillaCome] < 0) || (miTablero->turnoN && miTablero->casillasInt[casillaCome] > 0 && miTablero->casillasInt[casillaCome] != 99))
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugadaPrincipal[1] = casillaCome;
        miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
        nuevoMovimiento(miTablero);
        muevePeon = true;

        //miTablero->casillasInt[casilla] = 1;
    }
    else if ((!miTablero->turnoN && miTablero->casillasInt[casillaCome] > 0 && miTablero->casillasInt[casillaCome] != 99)  ||(miTablero->turnoN && miTablero->casillasInt[casillaCome] < 0))
    {
        char protege[2];
        protege[0] = miTablero->jugadaPrincipal[0];
        protege[1] = miTablero->casillasInt[casillaCome];
        //    miTablero->casillasProtegidas =
        miTablero->casillasProtegidas.push_back(protege);
        numProtegidas++;
        
    }
    
    //COME ENEMIGA 2
    if ((!miTablero->turnoN && miTablero->casillasInt[casillaComeSec] < 0) || (miTablero->turnoN && miTablero->casillasInt[casillaComeSec] > 0  && miTablero->casillasInt[casillaComeSec] != 99))
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugadaPrincipal[1] = casillaComeSec;
        miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
        nuevoMovimiento(miTablero);
        muevePeon = true;
        // miTablero->casillasInt[casilla] = 1;
        
    }else if ((!miTablero->turnoN && miTablero->casillasInt[casillaComeSec] > 0  && miTablero->casillasInt[casillaComeSec] != 99)  ||(miTablero->turnoN && miTablero->casillasInt[casillaComeSec] < 0))
    {
        char protege[2];
        protege[0] = miTablero->jugadaPrincipal[0];
        protege[1] = miTablero->casillasInt[casillaComeSec];
        //    miTablero->casillasProtegidas =
        miTablero->casillasProtegidas.push_back(protege);
        numProtegidas++;
    }
    int fichaEnemiga = Peon;

    if (miTablero->turnoN)fichaEnemiga = -fichaEnemiga;
    //COME AL PASO PEON ENEMIGO (DERECHA)
    if(miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0)
    {
        if (miTablero->alPaso == casillaCome-12
                && casilla == casillaCome-11)
        {


            // miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;
            


            //  miTablero->jugada[0] = casilla;

            char quitaEnemigo[2];
            quitaEnemigo[0] = miTablero->alPaso;
            quitaEnemigo[1] = 0;

            miTablero->jugadaPrincipal[1] = casillaCome;

            miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
            miTablero->jugadas = miTablero->jugadas + quitaEnemigo[0] + quitaEnemigo[1];


            //miTablero->jugadas.append(quitaEnemigo);

            nuevoMovimiento(miTablero);
            muevePeon = true;

            //   miTablero->casillasInt[miTablero->alPaso] = fichaEnemiga;
        }
    }
    
    //COME AL PASO PEON ENEMIGO (IZQUIERDA)
    if(miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0)
    {
        if (miTablero->alPaso == casillaComeSec-12
                && casilla == casillaComeSec-13)
        {
            
            //  miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;
            
            //  miTablero->jugada[0] = casilla;

            char quitaEnemigo[2];
            quitaEnemigo[0] = miTablero->alPaso;
            quitaEnemigo[1] = 0;

            miTablero->jugadaPrincipal[1] = casillaComeSec;

            miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
            miTablero->jugadas = miTablero->jugadas + quitaEnemigo[0] + quitaEnemigo[1];

            nuevoMovimiento(miTablero);
            muevePeon = true;

            // miTablero->casillasInt[miTablero->alPaso] = fichaEnemiga;
        }
    }
    
    return muevePeon;
}

bool Movimientos::mueveTorre(ModeloTablero* miTablero)
{
    
    //mueve a todas las casillas posibles
    //mira si esta ocupada
    bool izquierda = recorreCasillas(miTablero, -1);
    
    bool derecha =  recorreCasillas(miTablero, +1);
    
    bool abajo =   recorreCasillas(miTablero, -12);
    
    bool arriba =   recorreCasillas(miTablero, +12);

    return (izquierda || derecha || abajo || arriba);
    
}

bool Movimientos::mueveAlfil(ModeloTablero* miTablero)
{    
    bool SO = recorreCasillas(miTablero, -13);
    
    bool SE = recorreCasillas(miTablero, -11);
    
    bool NE  =recorreCasillas(miTablero, +13);
    
    bool NO = recorreCasillas(miTablero, +11);

    return (NE || NO || SE || SO);
}

bool Movimientos::recorreCasillas(ModeloTablero* miTablero, unsigned char salto)
{
    unsigned char nuevaCasilla = miTablero->jugadaPrincipal[0]+salto;
    // pasa = true;

    bool mueveFicha = false;

    while(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        miTablero->jugadaPrincipal[1] = nuevaCasilla;
        miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
        nuevoMovimiento(miTablero);
        mueveFicha = true;
        nuevaCasilla = nuevaCasilla+salto;
    }
    
    if (miTablero->casillasInt[nuevaCasilla] != 99)
    {
        if((!miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] < 0) || (miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] > 0))
        {     //encuentra ficha  enemiga
            miTablero->jugadaPrincipal[1] = nuevaCasilla;
            miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
            nuevoMovimiento(miTablero);
            mueveFicha = true;
        }
        else if((!miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] > 0) || (miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] < 0))
        {
            //encuentra ficha  amiga
            miTablero->jugadaPrincipal[1] = nuevaCasilla;

            char protege[2];
            protege[0] = miTablero->jugadaPrincipal[0];
            protege[1] = miTablero->casillasInt[nuevaCasilla];
            //    miTablero->casillasProtegidas =
            miTablero->casillasProtegidas.push_back(protege);
        }
    }

    // miTablero->numCasillasProtegidas++;
    return mueveFicha;
}

bool Movimientos::mueveCaballo(ModeloTablero* miTablero)
{
    unsigned char casilla  = miTablero->jugadaPrincipal[0];
    
    bool mueveCaballo = false;

    char movimientos[8] = {-25, 25, -23, 23, -14, 14, -10, 10};
    
    for (int i = 0; i < 8; i++)
    {
        if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {

            if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] <= 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] >= 0))
            {
					   std::cout << "muevecaballo"<<std::endl;

                miTablero->jugadaPrincipal[1] = casilla+movimientos[i];
                miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

                nuevoMovimiento(miTablero);
					   std::cout << "fin muevecaballo"<<std::endl;

                mueveCaballo = true;
            }else if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] > 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] < 0))
            {
					   std::cout << "protege caballo"<<std::endl;

                char protege[2];
                protege[0] = miTablero->jugadaPrincipal[0];
                protege[1] = miTablero->casillasInt[casilla+movimientos[i]];
                //    miTablero->casillasProtegidas =
                miTablero->casillasProtegidas.push_back(protege);
					   std::cout <<" fin protege caballo"<<std::endl;

            }
        }
    }
    
    return mueveCaballo;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero)
{  
    int casilla  = (int)miTablero->jugadaPrincipal[0];
    int filaRey=2;
    int intTorre = Torre;
    if (miTablero->turnoN)
    {
        filaRey = 9;
        intTorre = -Torre;
    }

    // int Dif = destino - casilla;
    // unsigned char nuevaCasilla;blero->casillasProtegidas[miTablero->casill
    //   bool pasa = false;
    //  char filaRey = 2;

    //std::cout << "MUEVEREY: "<<casilla <<std::endl;

    //std::cout << "MUEVE2: "<<filaRey <<std::endl;


    bool mueveRey = false;

    //ENROQUE
    if (casilla/12 == filaRey)
    {

        int destino  = casilla + 2;
        std::cout << "FILA BUENA, destino  "<<destino <<  " TORRE "<< intTorre<<std::endl;

        std::cout << "miTablero->casillasInt[casilla+1] "<<(int)miTablero->casillasInt[casilla+1] <<  " miTablero->casillasInt[destino] "<< (int)miTablero->casillasInt[destino]<< " miTablero->casillasInt[destino+1] "    << (int)miTablero->casillasInt[destino+1]<<std::endl;

        if(destino/12 == filaRey && miTablero->casillasInt[casilla+1] == 0 && miTablero->casillasInt[destino] == 0 && miTablero->casillasInt[destino+1] == intTorre )
        {
            std::cout << "ENROQUE CORTO BUENA " <<std::endl;

            //AQUI AÑADIR AL VECTOR!!!
            miTablero->casillasInt[destino+1] == 0;
            miTablero->casillasInt[destino-1] == intTorre;

            miTablero->jugadaPrincipal[1] = destino;
            miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

            nuevoMovimiento(miTablero);

            miTablero->casillasInt[destino+1] == intTorre;
            miTablero->casillasInt[destino-1] == 0;
            mueveRey = true;
        }

        destino  = casilla - 2;
        if(destino/12 == filaRey && miTablero->casillasInt[casilla-1] == 0 && miTablero->casillasInt[destino] == 0 &&  miTablero->casillasInt[destino-2] == intTorre
                && miTablero->casillasInt[destino-1] == 0)
        {
            std::cout << "ENROQUE LARGO BUENA " <<std::endl;
            char* jugEnroque;
            jugEnroque[0] = destino-2;
            jugEnroque[1] = destino+1;

            //miTablero->casillasInt[destino-2] == 0;
            //miTablero->casillasInt[destino+1] == intTorre;

            miTablero->jugadaPrincipal[1] = destino;
            miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
            miTablero->jugadas = miTablero->jugadas + jugEnroque[0] + jugEnroque[1];

            nuevoMovimiento(miTablero);

            //miTablero->casillasInt[destino-2] == intTorre;
            //miTablero->casillasInt[destino+1] == 0;

            mueveRey = true;

        }

    }
    
    char movimientos[8] = {-1, 1, -12, 12, -13, 13, -11, 11};
    
    for (int i = 0; i < 8; i++)
    {
        if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {
            if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] <= 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] >= 0))
            {
                miTablero->jugadaPrincipal[1] = casilla+movimientos[i];
                miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

                nuevoMovimiento(miTablero);
                mueveRey = true;
            }else if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] > 0) && (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] < 0))
            {
                char protege[2];
                protege[0] = miTablero->jugadaPrincipal[0];
                protege[1] = miTablero->casillasInt[casilla+movimientos[i]];
                //    miTablero->casillasProtegidas =
                miTablero->casillasProtegidas.push_back(protege);

                //miTablero->casillasProtegidas[miTablero->casillasInt[miTablero->jugada[0]]][miTablero->casillasInt[casilla+movimientos[i]]] = miTablero->casillasInt[casilla+movimientos[i]];

            }
        }
    }
    return mueveRey;
}

void  Movimientos::nuevoMovimiento(ModeloTablero *miTablero)
{
    // miTablero->vectorJugadas.sort();

    // unsigned char* jugada = new unsigned char[2];
    //  jugada[0] = miTablero->jugadaPrincipal[0];
    //jugada[1] = miTablero->jugadaPrincipal[1];

    // tableroModelo->jugada[0] = jugadaElegida[0];
    // tableroModelo->jugada[1] = jugadaElegida[1];

    //miTablero->jugadas.push_back(miTablero->jugadaPrincipal);
    std::cout << "NUEVOTABLERO" <<std::endl;

    ModeloTablero *tableroMovido = new ModeloTablero(*miTablero);
    std::cout << "CAMBIATURNO" <<std::endl;

    bool cambiado = tableroMovido->cambiaTurno();
    //SI NO HAY JAQUE A SU REY AL MOVER
    if (cambiado)
    {
        std::cout << "HA MOVIDO FICHA Y CAMBIADO TURNO CORRECTAMENTE" <<std::endl;
        int valorAtaque = miTablero->casillasInt[miTablero->jugadaPrincipal[0]] + miTablero->casillasInt[miTablero->jugadaPrincipal[1]];

        if (miTablero->turnoN) valorAtaque = -valorAtaque;
        //cuanto menor sea el valor, mejor
        if (miTablero->casillasInt[miTablero->jugadaPrincipal[1]] != 0 && valorAtaque != 0)
        {
            if (valorAtaque < 0)
            {

                miTablero->vectorJugadas.push_back(miTablero->jugadas);
            }

            else if (valorAtaque > 0)
            {
                miTablero->vectorJugadasPeores.push_back(miTablero->jugadas);
            }
        }else miTablero->vectorJugadasNormales.push_back(miTablero->jugadas);
    } else 		std::cout << "NO MUEVE  FICHA PORQUE EVALUA JAQUE??" <<std::endl;


    miTablero->jugadas = "";

    std::cout << "JUGAADSSSS?: "<<miTablero->jugadas.size() <<std::endl;

    
    delete tableroMovido;
    tableroMovido = NULL;
}

