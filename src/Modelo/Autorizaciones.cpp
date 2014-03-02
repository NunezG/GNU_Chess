#include "Autorizaciones.h"


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int Autorizaciones::autorizaCasilla()
{   

	ModeloTablero* tableroModelo = Modelo::getSingletonPtr()->tableroModelo;

	if (Modelo::getSingletonPtr()->tableroModelo->turnoN)
    {
						  						std::cout << "TURNOONNNNNN"<<std::endl;

      //  tableroModelo->jugada[0] = 143-tableroModelo->jugada[0];
       // tableroModelo->jugada[1] = 143-tableroModelo->jugada[1];
    }
					  						std::cout << "MIRA SI ES COMESTIBLE"<<std::endl;
											std::cout << (int)tableroModelo->casillasInt[tableroModelo->jugada[1]]<<std::endl;


											//el tipo es la ficha de casillasint
		int tipoo =  tableroModelo->casillasInt[tableroModelo->jugada[0]];

							  						std::cout << "TIPO: "<< tipoo<<std::endl;
if (tipoo<0)tipoo = -tipoo;

 
               return 0;

}


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
std::vector<int> Autorizaciones::casillasAutorizadas()
{   

	ModeloTablero* tableroModelo = Modelo::getSingletonPtr()->tableroModelo;

	if (Modelo::getSingletonPtr()->tableroModelo->turnoN)
    {
						  						std::cout << "TURNOONNNNNN"<<std::endl;

      //  tableroModelo->jugada[0] = 143-tableroModelo->jugada[0];
       // tableroModelo->jugada[1] = 143-tableroModelo->jugada[1];
    }
					  					//	std::cout << "MIRA SI ES COMESTIBLE"<<std::endl;
										//	std::cout << (int)tableroModelo->casillasInt[tableroModelo->jugada[1]]<<std::endl;





	  //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS
  
    bool movimiento = false;
  // Movimientos::generaMovimientos(miTablero);
    

											//el tipo es la ficha de casillasint
		//int tipoo =  tableroModelo->casillasInt[tableroModelo->jugada[0]];

							  						//std::cout << "TIPO: "<< tipoo<<std::endl;
//if (tipoo<0)tipoo = -tipoo;

 
				  						std::cout << "PUEDE MOVER"<<std::endl;

     bool resus=   Movimientos::movimientosUnaFicha(tableroModelo);
    
	 std::vector<int> listaJugadas;

		
    for (std::vector<unsigned char*>::iterator it = tableroModelo->vectorJugadas.begin(); it!=tableroModelo->vectorJugadas.end(); it++)
    {
        
        unsigned char* jugada = *it;
        
       listaJugadas.push_back(jugada[1]);
            
       //     ModeloTablero* tablero = Movimientos::aplicaMovimiento(*tableroModelo);
            
        
        delete jugada;
        jugada = NULL;
        
    }
    tableroModelo->vectorJugadas.clear();



	return listaJugadas;


   
}

bool Autorizaciones::pruebaJaqueMate(ModeloTablero* miTablero)
{    
    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS
  
    bool movimiento = false;
   Movimientos::generaMovimientos(miTablero);
    
    for (std::vector<unsigned char*>::iterator it = miTablero->vectorJugadas.begin(); it!=miTablero->vectorJugadas.end(); it++)
    {
        
        unsigned char* jugada = *it;
        
        if (!movimiento)
        {
            miTablero->jugada[0] = jugada[0];
            miTablero->jugada[1] = jugada[1];
            
            ModeloTablero* tablero = Movimientos::aplicaMovimiento(*miTablero);
            
            if (tablero != NULL)
            {
                //movimiento encontrado
                movimiento = true;
            }
            delete tablero;
            tablero = NULL;
        }
        delete jugada;
        jugada = NULL;
        
    }
    miTablero->vectorJugadas.clear();
    
    for (int i = 0; i <  miTablero->casillasProtegidas.size(); i++)
    {        
        // unsigned char* casilla = *it;
        
        delete miTablero->casillasProtegidas.at(i);
        miTablero->casillasProtegidas.at(i) = NULL;    
    }
    
    miTablero->casillasProtegidas.clear();
    
    if (movimiento)  return false;
    //else return true;
    
    return true; //JAQUE MATE O AHOGADO
    }