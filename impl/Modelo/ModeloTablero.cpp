#include "../../headers/Modelo/ModeloTablero.h"

ModeloTablero::ModeloTablero() :
    //numeroHijos(0),
    //Score(0),
    //fichaMovida(""),
    //vectorMov(NULL),
    turnoN(false),
    alPaso(0),
    nodoInicial(true)
  ,valorAtaque(0)
  , valorDefensivo(0)
{
    // jugada = new unsigned char[2];
    jugada[0] = 0;
    jugada[1] = 0;


}

ModeloTablero::ModeloTablero( const ModeloTablero& original, int casInicial, int casFinal):
    //  numeroHijos(0),
    //Score(0),
    // fichaMovida(""),
    //  vectorMov(NULL),
    turnoN(original.turnoN)
  , alPaso(original.alPaso)
  , nodoInicial(false)
  ,valorAtaque(0)
  , valorDefensivo(0)
  //,casillasInt(original.casillasInt.begin(), original.casillasInt.end())
  // ,casillasProtegidas(original.casillasProtegidas)

{
    jugada[0] = original.jugada[0];
    jugada[1] = original.jugada[1];
  
    for(int i=0; i<144;i++)
    {
        casillasInt[i] = original.casillasInt[i];
    }

    //cuanto menor sea el valor, mejor
    if (casillasInt[jugada[1]] == 0) valorAtaque = 0;
    else
    {
        valorAtaque = casillasInt[jugada[0]] + casillasInt[jugada[1]];
    }

    //CUANTAS MAS CASILLAS PROTEGIA ANTES, PEOR ES EL MOVIMIENTO DESPUES
    std::vector<unsigned char*> temp = original.casillasProtegidas;
    for (std::vector<unsigned char*>::iterator it = temp.begin(); it!=temp.end(); it++)
    {
        unsigned char* protegida = *it;
			// std::cout << "PROTEGIDA 0: "<<int(protegida[0]) << "FICHA: "<< int(casillasInt[protegida[0]]) <<" Y 1: "<<int(protegida[1])<<std::endl;

        if (protegida[0] == jugada[0])
        {

            int dif = protegida[1] - casillasInt[protegida[0]];
		//	std::cout << "DIF "<<dif<<std::endl;

            //SOLO SI LA PROTEGIDA ES MAYOR QUE LA PRIMERA
            if (dif > 0)
            {
                valorDefensivo = valorDefensivo + dif;
            }         
        }
    }

    cambiaTurno();
    // jugada = new unsigned char[2];
}

ModeloTablero::~ModeloTablero()
{

    if (!vectorJugadas.empty())
    {

        for (std::vector<unsigned char*>::iterator it = vectorJugadas.begin(); it!=vectorJugadas.end(); it++)
        {
            unsigned char* jugada = *it;
            delete jugada;
            jugada = NULL;

        }
        //  numeroHijos=0;
        vectorJugadas.clear();
    }
    if (!casillasProtegidas.empty())
    {
        for (std::vector<unsigned char*>::iterator it = casillasProtegidas.begin(); it!=casillasProtegidas.end(); it++)
        {
            unsigned char* jugada = *it;


            // if (casillasProtegidas.at(i) != NULL)
            //  {
            delete jugada;
            jugada = NULL;
            // }
        }
        //  numeroHijos=0;
        casillasProtegidas.clear();
    }
    //delete jugada;
    //jugada = NULL;
}


void ModeloTablero::cambiaTurno()
{
    //PEON
    if (casillasInt[jugada[0]] == 1)
    {

        //COME AL PASO
        if (alPaso == jugada[1]-12)
        {
            casillasInt[alPaso] = 0;
        }

        //int filaPromocion = 9;

        //PROMOCION A REINA
        if ((jugada[1])/12 == 9)
        {

            casillasInt[jugada[0]] = 5;
        }

        //DOBLE SALTO (LO MARCA PARA CAPTURAR AL PASO)
        else if (jugada[1] - jugada[0]  == 24)
        {
            alPaso = 143-jugada[1];
        } else alPaso = 0;
    } 

    //ENROQUE!
    else if (casillasInt[jugada[0]] == 6)
    {
        int dif = jugada[1] - jugada[0];
        // if (difCol<0 ) difCol = -difCol;
        //int fila =casillaDestinoTemp->getPosicion().Fila;

        if (dif == 2 || dif == -2)
        {
            char pos;

            if (dif > 0)
                pos = 1;
            else pos = -1;

            // char fichaTorre = casillasInt[jugada[1] + 1];
            // Casilla* casillaTorre = static_cast<Casilla*>(getHijo((fila*8)+7));
            // Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
            if (casillasInt[jugada[1] + pos] == 4)
                casillasInt[jugada[1] + pos] = 0;
            else casillasInt[jugada[1] + dif] = 0;

            casillasInt[jugada[1] - pos] = 4;
        }
		alPaso = 0;
    } else alPaso = 0;

    // MUEVE
    casillasInt[jugada[1]]= casillasInt[jugada[0]];
    casillasInt[jugada[0]] = 0;

    //EVALUA JAQUE PARA EL TURNO EN JUEGO, (SI HAY JAQUE SERÁ ELIMINADO)
    if (!evaluaJaque())
    {

        turnoN = !turnoN;

        char casillasTemp[144];
        //NORMALIZA EL TABLERO PARA EL CAMBIO DE TURNO
        for(int y=0; y<12;y++)
        {
            for(int i=0; i<12;i = i++)
            {
                //INVIERTE EL SIGNO DE LAS FICHAS Y LA POSICION DE LA FILA
                if (casillasInt[(i*12)+y] != 99)
                {
                    casillasTemp[((11-i)*12)+11-y] = -casillasInt[(i*12)+y];
                }
                else casillasTemp[(i*12)+y] = 99;
            }
        }

        for(int i=0; i<144;i++) 
            casillasInt[i] = casillasTemp[i];
      
        jugada[0] = 0;
        jugada[1] = 0;
    }
}

bool ModeloTablero::evaluaJaque()
{
    int posRey = 999;
    int fichaRey = -6;

    int fichaReina = -5;
    int fichaPeon = -1;
    int fichaAlfil = -3;
    int fichaCaballo = -2;
    int fichaTorre = -4;
    for (int i=0; i<144;i++)
    {
	
        if (casillasInt[i] == -fichaRey)
        {

            posRey = i;

           // break;
        }
					
    }
    if (posRey != 999)
    {
        //N
        int ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*12)];
            if(ficha != 0)
            {


                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //cualquier otra ficha en medio

                break;
            }

        }

        //S
        ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*12)];

            if(ficha != 0)
            {

                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //ficha en medio
                break;
            }
        }

        //E
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+i];

            if(ficha != 0)
            {

                //REY
                if(i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                break;
            }

        }

        //O
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-i];

            if(ficha != 0)
            {

                //REY
                if (i==1 && ficha == fichaRey)
                    return true;

                //REINA                             //TORRE
                if(ficha == fichaReina || ficha == fichaTorre)
                    return true;

                //ficha en medio

                break;
            }
        }

        //NE
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*11)];
            if(ficha != 0)
            {
                //REY                               //PEON NEGRO
                if(i==1 && (ficha == fichaRey || ficha == fichaPeon))
                    return true;

                //REINA                             //ALFIL
                else if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //NO
        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey+(i*13)];
            if(ficha != 0)
            {
                //REY                               //PEON NEGRO
                if(i==1 && (ficha == fichaRey || ficha ==fichaPeon))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //SE

        ficha= 0;

        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*11)];

            if(ficha != 0)
            {
                //REY
                if(i==1 && (ficha == fichaRey))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }

        //SO
        ficha= 0;
        for (int i = 1;ficha != 99; i++)
        {
            ficha = casillasInt[posRey-(i*13)];

            if(ficha != 0)
            {
                //REY
                if(i==1 && (ficha == fichaRey))
                    return true;

                //REINA                             //ALFIL
                if(ficha == fichaReina || ficha == fichaAlfil)
                    return true;

                break;
            }
        }
        int caballo;

        caballo= posRey-10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey-14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;

        caballo= posRey-23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;

        caballo= posRey-25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;

        caballo= posRey+10;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+14;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+23;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;


        caballo= posRey+25;
        ficha = casillasInt[caballo];
        if(ficha == fichaCaballo)
            return true;
    }

    return false;
}


