#include "Autorizaciones.h"


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int Autorizaciones::autorizaCasilla()
{   

  //  ModeloTablero* mainModelBoard = Modelo::getSingletonPtr()->mainModelBoard;

 //   if (Modelo::getSingletonPtr()->mainModelBoard->turnoN)
  //  {

        //  mainModelBoard->jugada[0] = 143-mainModelBoard->jugada[0];
        // mainModelBoard->jugada[1] = 143-mainModelBoard->jugada[1];
  //  }


    //el tipo es la ficha de casillasint
   // int tipoo =  mainModelBoard->casillasInt[mainModelBoard->jugadaPrincipal[0]];

  //  if (tipoo<0)tipoo = -tipoo;


    return 0;

}


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
std::vector<int> Autorizaciones::casillasAutorizadas(ModeloTablero* mainModelBoard, int posicion)
{   

  //  ModeloTablero* mainModelBoard = Modelo::getSingletonPtr()->mainModelBoard;

  //  if (Modelo::getSingletonPtr()->mainModelBoard->turnoN)
 //   {

        //  mainModelBoard->jugada[0] = 143-mainModelBoard->jugada[0];
        // mainModelBoard->jugada[1] = 143-mainModelBoard->jugada[1];
  //  }




    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    bool movimiento = false;
    // Movimientos::generaMovimientos(miTablero);
    

    //el tipo es la ficha de casillasint
    //int tipoo =  mainModelBoard->casillasInt[mainModelBoard->jugada[0]];

    //if (tipoo<0)tipoo = -tipoo;


    std::cout << "PUEDE MOVER??"<<std::endl;

	bool resus = Movimientos::movimientosUnaFicha(mainModelBoard, posicion);
    

    std::cout << "fingeneramov?"<<std::endl;


    std::vector<int> listaJugadas;


	std::cout << "for?AUTORIZAAA: " << mainModelBoard->testMapJugadas.size() << std::endl;



	for (std::map<int, std::vector<std::vector<int>>>::iterator it = mainModelBoard->testMapJugadas.begin(); it != mainModelBoard->testMapJugadas.end(); it++)
	{
		//std::cout << "for?" << std::endl;


		std::vector<std::vector<int>> jugadas = it->second;

		std::cout << "for22222?: " << jugadas.size() << std::endl;


		for (std::vector<std::vector<int>>::iterator it = jugadas.begin(); it != jugadas.end(); it++)
		{
			//dentro de esos valores elige las que atacan, esto se puede añadir al valor de defensa como valor (hasmhap) en el mapa tambien
			std::vector<int> jugada = *it;

			//	 for (std::vector<unsigned char*>::iterator itt = jugada.begin(); itt!=jugada.end(); itt++)
			//{

			for (int i = 0; i < jugada.size(); i = i + 2)
			{
				std::cout << "JUGADA RESALTADA? " << (int)jugada[i + 1] << std::endl;

				//punot inicial
				//jugada[i]

				listaJugadas.push_back((int)jugada[i + 1]);

				//punto final


			}
			// unsigned char* mov = *jugada.begin();

			//std::cout << "MOV0? "<<  (int)mov[0]   <<std::endl;

			//	std::cout << "MOV1? "<<  (int)mov[1]   <<std::endl;



			//     ModeloTablero* tablero = Movimientos::aplicaMovimiento(*mainModelBoard);


			//  delete mov;
			//   mov = NULL;

			// }
		}

	}

    // mainModelBoard->vectorJugadas.clear();

    std::cout << "BORRA JUGADASSSS?"<<std::endl;

    mainModelBoard->borraJugadas();
    std::cout << "RET?"<<std::endl;


    return listaJugadas;



}

bool Autorizaciones::pruebaJaqueMate(ModeloTablero* miTablero)
{    
    //VA GENERANDO LOS MOVIMIENTOS

    bool movimiento = false;
	std::cout << "pruebaJaqueMate "  << std::endl;

    Movimientos::generaMovimientos(miTablero);
	std::cout << "FIN generaMovimientos de pruebajaquemate" << std::endl;

    if(miTablero->testMapJugadas.size() > 0)
    {
        movimiento = true;
        

        miTablero->borraJugadas();

		std::cout << "FIN  pruebajaquemate" << std::endl;

        if (movimiento)  return false;
        //else return true;

        return true; //JAQUE MATE O AHOGADO
    }
}
