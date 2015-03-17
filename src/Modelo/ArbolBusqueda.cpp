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


int ArbolBusqueda::alphaBeta(ModeloTablero* table, int alpha, int beta, const int depthleft, std::vector<int>& result)
{
	std::cout << "ARBOLLLLLLLLLLL"  << std::endl;


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
    
	std::cout << "FINMOVARBOL" << std::endl;

    //  unsigned char jugadaElegida[2];
    int score;
	for (std::map<int, std::vector<std::vector<int>>>::iterator it = table->testMapJugadas.begin(); it != table->testMapJugadas.end(); it++)
    {
		std::cout << "FIIF" << it->first << std::endl;

		//recorre los valores del mapa que menos protegen
		std::vector<std::vector<int>> jugadas = it->second;

		std::cout << "FOOF: " << jugadas.size() << std::endl;

		for (std::vector<std::vector<int>>::iterator it = jugadas.begin(); it != jugadas.end(); it++)
		{


			//dentro de esos valores elige las que atacan, esto se puede añadir al valor de defensa como valor (hasmhap) en el mapa tambien
			std::vector<int> jugada = *it;


			std::cout << "QUE PASA CN FORARBOL?" << std::endl;

			std::cout << "ESTO? " << jugada.size() << std::endl;

			std::cout << "FOOFORRVARBOL: " << (int)jugada[0] << "/" << (int)jugada[1] << std::endl;

			//table->vectorJugada = jugada;



			//table->jugadas[0] = jugada[0];
			//table->jugadas[1] = jugada[1];

			//std::cout << "table->jugadas: " << (int)table->jugadas[0] << "/" << (int)table->jugadas[1] << std::endl;

			//table->jugadaPrincipal[1] = jugada[0][1];

			ModeloTablero* tablero = new ModeloTablero(*table);
			bool cambiado = tablero->cambiaTurno(jugada);

			if (cambiado)
			{


				//    int valorAtaqueAcumulado;
				score = -alphaBeta(tablero, -beta, -alpha, depthleft - 1, result);
				delete tablero;
				tablero = NULL;
				std::cout << "sigue alphaBeta " << std::endl;
				std::cout << "score: " << score << std::endl;

				if (score >= beta)
				{
					std::cout << "break-dance!!! " << std::endl;

					return beta;
					//  fail hard beta-cutoff
				}
				else if (score > alpha)
				{
					alpha = score;
					//LE PASA EL MOVIMIENTO A SU PADRE SOLO SI EL PADRE ES EL INICIAL
					if (table->nodoInicial)
					{//RELLENA LA JUGADA DEL NODO INICIAL
						std::cout << "resulta que resul" << std::endl;
						result = jugada;
						std::cout << "result = jugada; " << (int)jugada[0] << " / " << (int)jugada[1] << std::endl;

						//  Modelo::getSingletonPtr()->jugadasElegidas[0][1] = jugada[1];
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


	std::cout << "EVALUA TABVLERO" << std::endl;
	/*
	for (int i = 11; i >= 0; i--){
		for (int y = 0; y < 12; y++){



			if ((int)tablero->casillasInt[(i * 12) + y] == 0){
				std::cout << " -" << std::ends;

			}
			else if ((int)tablero->casillasInt[(i * 12) + y] == 99){
				std::cout << " " << std::ends;

			}
			else if ((int)tablero->casillasInt[(i * 12) + y] >= 0){
				std::cout << " " << (int)tablero->casillasInt[(i * 12) + y] << std::ends;
			}

			else
				std::cout << (int)tablero->casillasInt[(i * 12) + y] << std::ends;


		}
		std::cout << "" << std::endl;

	}
	*/







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
	std::cout << "suma: " << suma << std::endl;

	std::cout << "tablero->casillasProtegidas.size(): " << tablero->casillasProtegidas.size() << std::endl;

	//tablero->casillasProtegidas.
	std::unordered_map<int, int>::iterator itt = tablero->casillasProtegidas.begin();
	//int i = 0;
	for (itt; itt != tablero->casillasProtegidas.end(); itt++){

		std::cout << "CASILLA PROTECTOR "  << " " << itt->first << std::endl;

		std::cout << "NUM PROTECTOR "  << " " << itt->second << std::endl;

		//std::cout << "CASILLA ARRAY " << " " << tablero->casillasProtegidas[i]<< std::endl;

		//	i++;
	}



//	if (tablero->casillasProtegidas.size() != 0)
 //   {
		
	//		std::unordered_map<int, int>::iterator it = tablero->casillasProtegidas.find(tablero->casillaSeleccionada);

		//	if (it != tablero->casillasProtegidas.end())
		//	{
			//	std::cout << "valor defensivo " << it->second << std::endl;
			//	std::cout << "valor primero " << it->first << std::endl;

			//	std::cout <<" casillaSeleccionada " << tablero->casillaSeleccionada << std::endl;

			//	suma = suma + (it->second*100);


		//		std::cout << "NUEVA SUMAAAAAAAAAAAAAA " << suma << std::endl;

				//tablero->valorDefensivo = it->second;

		//	}


		
        //EL VALOR DEFENSIVO SE PIERDE SI SE MUEVE FICHA
        //suma = suma - (tablero->valorDefensivo);


		
        //if (suma < 0)
        //suma = 0;

   // }
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


