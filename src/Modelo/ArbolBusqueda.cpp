#include "ArbolBusqueda.h"



short ArbolBusqueda::CalculatePieceActionValue(int pieceType)
{
    switch (pieceType)
    {
    case Peon:
    {
        return 6;
    }
    case Caballo:
    {
        return 3;
    }
    case Alfil:
    {
        return 3;
    }
    case Torre:
    {
        return 2;
    }
    case Reina:
    {
        return 1;
    }
    case Rey:
    {
        return 1;
    }
    default:
    {
        return 0;
    }
    }
}



//void JugadorArtificial::sobreVuelaNodoCasilla(Ogre::SceneNode* casillaSobrevolada)
//{

//}


int ArbolBusqueda::alphaBeta(ModeloTablero* table,int alpha,int beta,const int depthleft )
{
    if( depthleft == 0)
    {
        //CALCULA LA HEURISTICA
        int ev = evaluaTablero(table);
        // table->Score = ev;
        //   delete  table;
        // table = NULL;
        return ev;
    }

    if (!Movimientos::generaMovimientos(table)) 
        return 0;
    

    //  unsigned char jugadaElegida[2];
    int score;
    for (std::vector<unsigned char*>::iterator it = table->vectorJugadas.begin(); it!=table->vectorJugadas.end(); it++)
    {       
        unsigned char* jugada = *it;
        table->jugada[0] = jugada[0];
        table->jugada[1] = jugada[1];

        ModeloTablero* tablero = Movimientos::aplicaMovimiento(*table);

        if (tablero != NULL)
        {
            //    int valorAtaqueAcumulado;
            score = -alphaBeta(tablero, -beta,-alpha, depthleft - 1 );
            delete tablero;
            tablero = NULL;

            if( score >= beta )
            {      
                return beta;
                //  fail hard beta-cutoff
            }
            else if( score > alpha )
            {            
                alpha = score;
                //LE PASA EL MOVIMIENTO A SU PADRE SOLO SI EL PADRE ES EL INICIAL
                if (table->nodoInicial)
                {//RELLENA LA JUGADA DEL NODO INICIAL
                    Modelo::getSingletonPtr()->jugadaElegida[0] = jugada[0];
                    Modelo::getSingletonPtr()->jugadaElegida[1] = jugada[1];
                }        
            }        
            // delete tablero;
            // tablero = NULL;
        }

       // if (table->nodoInicial)
        //{
       //   delete tablero;
        //  tablero = NULL;
       // }
    }

    //for(int i = 0; i < table->vectorMov.size(); i++)
    //  {
    //     if (table->vectorMov.at(i) != NULL)
    //      {
    //         delete table->vectorMov.at(i);
    //         table->vectorMov.at(i) = NULL;
    //        }
    //    }

    //  delete table;
    //  table = NULL;
    //table->vectorMov.clear();
    return alpha;
}

int ArbolBusqueda::evaluaTablero(ModeloTablero* tablero)
{
    int suma = 0;
    //   BlackCheck = false;


    //EMPIEZA CONTANDO LAS FICHAS DEL TABLERO Y HACIENDO UNA SUMA SIMPLE...

    for (int i = 2; i<10;i++)
    {
        for (int y = 2; y<10;y++)
        {
            //Busca las fichas del mismo color del turno
            if (tablero->casillasInt[(i*12)+y] < 0)
            {
                //if(casillasInt[(i*12)+y] == -6){
                //   BlackCheck = false;
                //   }

               if (tablero->turnoN) suma =  suma + valorFicha(tipoFicha(-tablero->casillasInt[(i*12)+y]));
				   else suma =  suma - valorFicha(tipoFicha(-tablero->casillasInt[(i*12)+y]));

            }else if (tablero->casillasInt[(i*12)+y] > 0)
            {
                if (tablero->turnoN) suma =  suma - valorFicha(tipoFicha(tablero->casillasInt[(i*12)+y]));
					else suma =  suma + valorFicha(tipoFicha(tablero->casillasInt[(i*12)+y]));
            }
            //MVV (Most valuable victim)/LVA (Least valuable attacker)

        }
    }

    if (tablero->valorDefensivo != 0)
    {
        //EL VALOR DEFENSIVO SE PIERDE SI SE MUEVE FICHA
        suma = suma - (tablero->valorDefensivo);
		//if (suma < 0)
		//suma = 0;				
	//	std::cout << "tablero->valorDefensivo"<<tablero->valorDefensivo<<std::endl;
	//	std::cout << "SUMA CON VALOR DEFENSIVO "<<suma<<std::endl;
    }
    //if(!turnoN)
    //suma = -suma;

    return suma;
}




short ArbolBusqueda::valorFicha(const tipoFicha tipo)
{

    switch (tipo)
    {
    case Peon:
    {
        return 100;
    }
    case Caballo:
    {
        return 320;
    }
    case Alfil:
    {
        return 325;
    }
    case Torre:
    {
        return 500;
    }
    case Reina:
    {
        return 750;
    }
    case Rey:
    {
        return 3000;
    }
    default:
    {
        return 0;
    }
    }
}


