#include "../../headers/Modelo/Movimientos.h"

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
            
           if (valorCasilla > 0)
           { 
                miTablero->jugada[0] = i;

				// bool fichamovida = false;  
				bool resultado = false;
				switch (tipoFicha(valorCasilla))
				{
				case Rey:

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
    unsigned char casilla  = miTablero->jugada[0];
    unsigned char nuevaCasilla = casilla+12;
    int casillaCome = casilla+11;
    int casillaComeSec = casilla+13;
    int salto = casilla+24;
    // int filaPeon = 3;
    //int filaPromocion = 9;
    
    //MOVIMIENTO NORMAL
    if(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = nuevaCasilla;
        nuevoMovimiento(miTablero);
        muevePeon = true;
    }
    
    //DOBLE SALTO
    if(casilla/12 == 3 && miTablero->casillasInt[nuevaCasilla] == 0 && miTablero->casillasInt[salto] == 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = salto;
        nuevoMovimiento(miTablero);
        muevePeon = true;

    }
    
    int numProtegidas = 0;
    
    //COME ENEMIGA
    if (miTablero->casillasInt[casillaCome] < 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = casillaCome;
        nuevoMovimiento(miTablero);
        muevePeon = true;

        //miTablero->casillasInt[casilla] = 1;
    }
    else if (miTablero->casillasInt[casillaCome] > 0 && miTablero->casillasInt[casillaCome] != 99)
    {
        unsigned char* protege = new unsigned char[2];
        protege[0] = miTablero->jugada[0];
        protege[1] = miTablero->casillasInt[casillaCome];
        //    miTablero->casillasProtegidas =
        miTablero->casillasProtegidas.push_back(protege);
        numProtegidas++;
        
    }
    
    //COME ENEMIGA 2
    if (miTablero->casillasInt[casillaComeSec] < 0)
    {
        // miTablero->jugada[0] = casilla;
        miTablero->jugada[1] = casillaComeSec;
        nuevoMovimiento(miTablero);
        muevePeon = true;
        // miTablero->casillasInt[casilla] = 1;
        
    }else if (miTablero->casillasInt[casillaComeSec] > 0 && miTablero->casillasInt[casillaComeSec] != 99)
    {
        unsigned char* protege = new unsigned char[2];
        protege[0] = miTablero->jugada[0];
        protege[1] = miTablero->casillasInt[casillaComeSec];
        //    miTablero->casillasProtegidas =
        miTablero->casillasProtegidas.push_back(protege);
        numProtegidas++;
    }
    
    //COME AL PASO PEON ENEMIGO (DERECHA)
    if(miTablero->alPaso == casilla+1 && miTablero->casillasInt[casillaCome] == 0)
    {
        if (miTablero->alPaso == casillaCome-12
                && casilla == casillaCome-11)
        {         
            miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;
            
            //  miTablero->jugada[0] = casilla;
            miTablero->jugada[1] = casillaCome;
            nuevoMovimiento(miTablero);
            muevePeon = true;

            miTablero->casillasInt[miTablero->alPaso] = -1;
        }
    }
    
    //COME AL PASO PEON ENEMIGO (IZQUIERDA)
    if(miTablero->alPaso == casilla-1 && miTablero->casillasInt[casillaComeSec] == 0)
    {
        if (miTablero->alPaso == casillaComeSec-12
                && casilla == casillaComeSec-13)
        {
            
            miTablero->casillasInt[miTablero->alPaso] = 0;
            //casillas[1] = 0;
            
            //  miTablero->jugada[0] = casilla;
            miTablero->jugada[1] = casillaComeSec;
            nuevoMovimiento(miTablero);
            muevePeon = true;

            miTablero->casillasInt[miTablero->alPaso] = -1;
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
    unsigned char nuevaCasilla = miTablero->jugada[0]+salto;
    // pasa = true;

    bool mueveFicha = false;

    while(miTablero->casillasInt[nuevaCasilla] == 0)
    {
        miTablero->jugada[1] = nuevaCasilla;
        nuevoMovimiento(miTablero);
        mueveFicha = true;
        nuevaCasilla = nuevaCasilla+salto;
    }
    
    if (miTablero->casillasInt[nuevaCasilla] != 99)
    {
        if(miTablero->casillasInt[nuevaCasilla] < 0)
        {     //encuentra ficha  enemiga
            miTablero->jugada[1] = nuevaCasilla;
            nuevoMovimiento(miTablero);
            mueveFicha = true;
        }
        else if(miTablero->casillasInt[nuevaCasilla] > 0)
        {

            //NO PONER NEGATIVO?? HACER EN LISTA O VECTOR PARA QUE HAYA TAMAÑO??
            //encuentra ficha  amiga
            miTablero->jugada[1] = nuevaCasilla;

            unsigned char* protege = new unsigned char[2];
            protege[0] = miTablero->jugada[0];
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
    unsigned char casilla  = miTablero->jugada[0];
    
    bool mueveCaballo = false;

    char movimientos[8] = {-25, 25, -23, 23, -14, 14, -10, 10};
    
    for (int i = 0; i < 8; i++)
    {
        if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {
            if (miTablero->casillasInt[casilla+movimientos[i]] <= 0)
            {
                miTablero->jugada[1] = casilla+movimientos[i];
                nuevoMovimiento(miTablero);
                mueveCaballo = true;
            }else if (miTablero->casillasInt[casilla+movimientos[i]] > 0)
            {
                unsigned char* protege = new unsigned char[2];
                protege[0] = miTablero->jugada[0];
                protege[1] = miTablero->casillasInt[casilla+movimientos[i]];
                //    miTablero->casillasProtegidas =
                miTablero->casillasProtegidas.push_back(protege);

            }
        }
    }
    
   return mueveCaballo;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero)
{  
    unsigned char casilla  = miTablero->jugada[0];
    
    // int Dif = destino - casilla;
    // unsigned char nuevaCasilla;blero->casillasProtegidas[miTablero->casill
    //   bool pasa = false;
    //  char filaRey = 2;

    bool mueveRey = false;

    //ENROQUE
    if (casilla/12 == 2)
    {
        unsigned char destino  = casilla + 2;
        
        if(destino/12 == 2 && miTablero->casillasInt[destino-1] == 0 && miTablero->casillasInt[destino] == 0 && (miTablero->casillasInt[destino+1] == Torre
                                                                                                                 || (miTablero->casillasInt[destino+2] == Torre
                                                                                                                     && miTablero->casillasInt[destino+1] == 0)))
        {
            miTablero->jugada[1] = destino;
            nuevoMovimiento(miTablero);
            mueveRey = true;
        }

        destino  = casilla - 2;
        if(destino/12 == 2 && miTablero->casillasInt[destino+1] == 0 && miTablero->casillasInt[destino] == 0 && (miTablero->casillasInt[destino-1] == Torre
                                                                                                                 || (miTablero->casillasInt[destino-2] == Torre
                                                                                                                     && miTablero->casillasInt[destino-1] == 0)))
        {
            miTablero->jugada[1] = destino;
            nuevoMovimiento(miTablero);
            mueveRey = true;

        }

    }
    
    char movimientos[8] = {-1, 1, -12, 12, -13, 13, -11, 11};
    
    for (int i = 0; i < 8; i++)
    {
        if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {
            if (miTablero->casillasInt[casilla+movimientos[i]] <= 0)
            {
                miTablero->jugada[1] = casilla+movimientos[i];
                nuevoMovimiento(miTablero);
                mueveRey = true;
            }else if (miTablero->casillasInt[casilla+movimientos[i]] > 0)
            {
                unsigned char* protege = new unsigned char[2];
                protege[0] = miTablero->jugada[0];
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

    unsigned char* jugada = new unsigned char[2];
    jugada[0] = miTablero->jugada[0];
    jugada[1] = miTablero->jugada[1];

    int valorAtaque = miTablero->casillasInt[miTablero->jugada[0]] + miTablero->casillasInt[miTablero->jugada[1]];

    //cuanto menor sea el valor, mejor
    if (miTablero->casillasInt[jugada[1]] != 0 && valorAtaque != 0)
    {       
        if (valorAtaque < 0){

            miTablero->vectorJugadas.push_back(jugada);
        }

        else if (valorAtaque > 0) {
            miTablero->vectorJugadasPeores.push_back(jugada);
        }
    }else miTablero->vectorJugadasNormales.push_back(jugada);
    
}

ModeloTablero* Movimientos::aplicaMovimiento(ModeloTablero &miTablero)
{
    
    ModeloTablero* TableroMovido = NULL;
    // TableroMovido->alPaso = -1;
    int casOrigen = miTablero.jugada[0];
    int casDestino = miTablero.jugada[1];
        
    //COME AL PASO
    // if (miTablero.casillasInt[casOrigen] == 1 && miTablero.alPaso == casDestino-12)
    // {
    //     miTablero.casillasInt[miTablero.alPaso] = 0;
    //  }
    
    // int fichavieja = miTablero.casillasInt[casOrigen];
    //  int fichaNueva = miTablero.casillasInt[casDestino];
    
    //APLICA EL MOVIMIENTO
    TableroMovido = new ModeloTablero(miTablero, casOrigen, casDestino);
    
    if (TableroMovido->turnoN == miTablero.turnoN)
    {
        delete TableroMovido;
        // miTablero.casillasInt[casDestino] = fichaNueva;
        //miTablero.casillasInt[casOrigen] = fichavieja;
        return NULL;
 
    }
    
    return TableroMovido;
    // miTablero.numeroHijos++;
}