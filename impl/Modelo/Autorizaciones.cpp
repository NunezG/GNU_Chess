#include "../../headers/Modelo/Autorizaciones.h"


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

 
				  						std::cout << "PUEDE MOVER"<<std::endl;

        switch (tipoo)
        {
        case Rey: //REY SELECCIONADO
			  						std::cout << "REY SELECCIONADO "<<std::endl;

            return Autorizaciones::autorizaRey(tableroModelo);
            break;

        case Reina: //REINA SELECCIONADO
				std::cout << "REINA SELECCIONADO "<<std::endl;
            return Autorizaciones::autorizaReina(tableroModelo);
            break;

        case Alfil: //ALFIL SELECCIONADO
							std::cout << "ALFIL SELECCIONADO "<<std::endl;

            return Autorizaciones::autorizaAlfil(tableroModelo);
            break;

        case Torre: //TORRE SELECCIONADA
										std::cout << "TORRE SELECCIONADO "<<std::endl;

            return Autorizaciones::autorizaTorre(tableroModelo);
            break;

        case Caballo: //CABALLO SELECCIONADO
													std::cout << "CABALLO SELECCIONADO "<<std::endl;

            return Autorizaciones::autorizaCaballo(tableroModelo);
            break;

        case Peon: //PEON SELECCIONADO
													std::cout << "PEON SELECCIONADO "<<std::endl;

            return Autorizaciones::autorizaPeon(tableroModelo);
            break;

        default:
																std::cout << "NAAAADA SELECCIONADO "<<std::endl;

            return 0;
            break;
        }
    
   
}

int Autorizaciones::autorizaPeon (ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0] ;

	int filaPeones = 3;

	if (miTablero->turnoN)
		filaPeones = 8;

    if (Dif < 0)
    {
         //Invierte el signo  de la diferencia de los peones negros
        Dif = -Dif;
    }
    // int filaSobreTraducida = 24 + (filaNueva * 12);
					std::cout << "autorizaPeon : " <<Dif <<std::endl;
										std::cout << "miTablero->turnoN : " <<miTablero->turnoN <<std::endl;

										std::cout << "miTablero->jugada[0]  22: " <<miTablero->jugada[0]  <<std::endl;

															std::cout << "miTablero->jugada[1]  : " <<miTablero->jugada[1]  <<std::endl;


    if (Dif == 12 ||
		( Dif== 24 && miTablero->jugada[0]/12 == filaPeones))
    {

		//std::cout << "miTablero->jugada[0]] : "  <<  (int)miTablero->jugada[0] <<std::endl;

			//std::cout << "miTablero->jugada[1]] : "  <<  (int)miTablero->jugada[1] <<std::endl;
				//	std::cout << "(miTablero->casillasInt[miTablero->jugada[0]] : "  <<  miTablero->casillasInt[miTablero->jugada[0]] <<std::endl;

			//std::cout << "(miTablero->casillasInt[miTablero->jugada[1]] : "  <<  miTablero->casillasInt[(int)miTablero->jugada[1]] <<std::endl;
					//	std::cout << "(miTablero->casil22222 : "  <<  miTablero->casillasInt[miTablero->jugada[1]] <<std::endl;

        //SALTA 2 CASILLAS (ESCAQUES) o PASA UNA CASILLA
        if (miTablero->casillasInt[miTablero->jugada[1]] != 0)
            return 0;
        else
        {
								std::cout << "pruebaCamino esteee : "  <<std::endl;


			if (miTablero->turnoN) 
			 return pruebaCamino(miTablero, -12);


			else
            return pruebaCamino(miTablero, 12);
        }
    }

    else if(( Dif == 11 || Dif == 13))
    {
	 std::cout << "ALPASO: "<< int(miTablero->alPaso) <<std::endl;

       // Dif = miTablero->jugada[1] - miTablero->jugada[0];
        //COME
        if (miTablero->casillasInt[miTablero->jugada[1]] < 0)
        { 
            return pruebaCamino(miTablero, Dif);
        }

        else if(miTablero->alPaso >= 0)
        {
            //AL PASO
            //CASILLA EN LA COLUMNA DE LA SOBREVOLADA Y EN LA FILA DEL PEON ATACANTE
				std::cout << "miTablero->jugada[0]/12 : " << miTablero->jugada[0]/12 <<std::endl;
				std::cout << "miTablero->jugada[0]%12 : " << miTablero->jugada[0]%12 <<std::endl;

				std::cout << "miTablero->jugada[1]/12: " << miTablero->jugada[1]/12<<std::endl;
				std::cout << "miTablero->jugada[1]%12: " << miTablero->jugada[1]%12<<std::endl;

                int  posCasilla  = (miTablero->jugada[0] - miTablero->jugada[0]%12) + (miTablero->jugada[1]%12);

				std::cout << "posCasilla (miTablero->jugada[0]/12 + miTablero->jugada[1]%12): " << posCasilla<<std::endl;

            if (miTablero->alPaso ==  posCasilla)
            {
					 std::cout << "ES AL PASO: " <<std::endl;

                return pruebaCamino(miTablero, Dif);
            }

        }
    }
    return 0;
}

int Autorizaciones::autorizaAlfil(ModeloTablero* miTablero)
{

    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    //diferencia multiplo de 11
    if (Dif % 11 == 0)
    {

        if(Dif > 0) //LETRAS DESCENDENTES Y NUMEROS ASCENDENTES (ARR IZQUIERDA)
            return pruebaCamino(miTablero, 11);

        else if(Dif < 0) //LETRAS ASCENDENTES Y NUMEROS DESCENDENTES (ABAJO DERECHA)
            return pruebaCamino(miTablero, -11);
    }
    //multiplo de 13
    else if (Dif % 13 == 0)
    {
        if(Dif  > 0) //LETRAS ASCENDENTES Y NUMEROS ASCENDENTES (ARRIBA DERECHA)
            return pruebaCamino(miTablero, 13);

        else if (Dif < 0) //Columnas DESCENDENTES Y Filas DESCENDENTES (ABAJO IZQUIERDA)
            return pruebaCamino(miTablero, -13);
    }else return 0;
}

int Autorizaciones::autorizaReina(ModeloTablero* miTablero)
{
    int result = autorizaAlfil(miTablero);
    if (result > 0)
        return result;
    else return autorizaTorre(miTablero);
}

int Autorizaciones::autorizaRey(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    int destino= miTablero->jugada[1];

    if (Dif== 1 || Dif== -1 ||Dif== 11 || Dif== -11 || Dif== 12 || Dif== -12|| Dif== 13 || Dif== -13)
        return pruebaCamino(miTablero, Dif);
    else{
        //ENROQUE
        if ( Dif/12 == 0 && destino/12 == 2 && (Dif == 2 || Dif == -2))
        {
            if(miTablero->casillasInt[destino+(Dif/2)] == Torre && miTablero->casillasInt[destino+Dif == 99])
                return pruebaCamino(miTablero, Dif/2);

            else if(miTablero->casillasInt[destino+Dif] == Torre
                    && miTablero->casillasInt[destino+(Dif/2)] == Vacio && miTablero->casillasInt[destino+Dif+(Dif/2) == 99])   // enroque largo
                return pruebaCamino(miTablero, Dif/2);
        }

        return 0;
    }
}

int Autorizaciones::autorizaTorre(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    //MULTIPLO DE 12, ARRIBA O ABAJO
    if (Dif%12 == 0)
    {
        if (Dif < 0) //MOVIMIENTO ABAJO
            return pruebaCamino(miTablero, -12);

        else if (Dif > 0 )  //MOVIMIENTO ARRIBA
            return pruebaCamino(miTablero, 12);
    }

    //misma fila
    else if (miTablero->jugada[1]/12 == miTablero->jugada[0]/12)
    {
        if (Dif > 0)
            //MOVIMIENTO DERECHA
            return pruebaCamino(miTablero, +1);

        else if (Dif < 0) //MOVIMIENTO IZQUIERDA
            return pruebaCamino(miTablero, -1);
    }
    return 0;
}

int Autorizaciones::autorizaCaballo(ModeloTablero* miTablero)
{
    int Dif = miTablero->jugada[1] - miTablero->jugada[0];

    if (Dif < 0) Dif = -Dif;
    //  int filaDif = Dif/12;
    //  int colDif = Dif%12;

    if (Dif == 23 || Dif == 25 || Dif == 10 || Dif == 14)
    {
        return pruebaCamino(miTablero, miTablero->jugada[1] - miTablero->jugada[0]);
    }
    else {
        return 0;
    }
}

int Autorizaciones::pruebaCamino(ModeloTablero* miTablero, int salto)
{
    //   int Dif = casillaFinal - casillaInicial;
    int resultado = 0;
    // int ocupado = false;
    int nuevaCasilla = miTablero->jugada[0];

    bool pasa = true;
					std::cout << "salto"  << salto <<std::endl;

    while(pasa)
    {
				std::cout << "nuevaCasilla"  << nuevaCasilla <<std::endl;
								std::cout << "miTablero->casillasInt[nuevaCasilla] "  << miTablero->casillasInt[nuevaCasilla]  <<std::endl;

        nuevaCasilla = nuevaCasilla+salto;
				std::cout << "nuevaCasilla2"  << nuevaCasilla <<std::endl;
				std::cout << "miTablero->casillasInt[nuevaCasilla] "  << miTablero->casillasInt[nuevaCasilla]  <<std::endl;
        pasa = miTablero->casillasInt[nuevaCasilla] == 0;

        if (nuevaCasilla == miTablero->jugada[1])
        {
            int fichavieja = miTablero->casillasInt[miTablero->jugada[0]];
            int fichaNueva = miTablero->casillasInt[nuevaCasilla];

            miTablero->casillasInt[nuevaCasilla] = fichavieja;
            miTablero->casillasInt[miTablero->jugada[0]] = 0;

            if (miTablero->evaluaJaque())
            {
                resultado = 2;
            }
            else
                resultado= 1;

            miTablero->casillasInt[nuevaCasilla] = fichaNueva;
            miTablero->casillasInt[miTablero->jugada[0]] = fichavieja;
					std::cout << "resultado"  << resultado <<std::endl;

            return resultado;
        }
    }
						std::cout << "resultado al final"  << resultado <<std::endl;

    return resultado;
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