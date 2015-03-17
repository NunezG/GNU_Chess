#include "ModeloTablero.h"

ModeloTablero::ModeloTablero(std::string posicion) :
    //numeroHijos(0),
    //Score(0),
    //fichaMovida(""),
    //vectorMov(NULL),
    turnoN(false),
    alPaso(0),
    nodoInicial(true)
  ,valorAtaque(0)
 // , valorDefensivo(0)
 // ,jugadas("")

{
   // jugadaPrincipal[0] = 0;
   // jugadaPrincipal[1] = 1;

    //jugadas.clear();
    //vectorJugadas = new vector
    //jugadaPrincipal = new char[2];
    // jugada = new unsigned char[2];

    // std::string nombreObjeto;

    int i = 0;
    int fichaInt;

    //AÑADE LOS BORDES
    for (int i = 0; i<12; i++)
    {
        for (int y = 0; y<12; y++)
        {
            if((i > 9)
                    || (y > 9)
                    || (i < 2)
                    || (y < 2))
            {

                casillasInt[(i*12)+y] = 99;

            }else
            {

                switch (posicion[((i-2)*8)+y-2])
                {
                case 'a':
                    fichaInt = Peon;

                    break;
                case 'b':
                    fichaInt = Torre;

                    break;
                case 'c':
                    fichaInt = Caballo;


                    break;
                case 'd':
                    fichaInt = Alfil;


                    break;
                case 'e':
                    fichaInt = Reina;


                    break;
                case 'f':
                    fichaInt = Rey;

                    break;
                case 'z':
                    fichaInt = -Peon;


                    break;
                case 'y':
                    fichaInt = -Torre;


                    break;
                case 'x':
                    fichaInt = -Caballo;


                    break;
                case 'w':
                    fichaInt = -Alfil;


                    break;
                case 'v':
                    fichaInt = -Reina;


                    break;
                case 'u':
                    fichaInt = 	-Rey;

                    break;
                default:
                    fichaInt = Vacio;
                    break;
                }



                casillasInt[(i*12)+y] =	fichaInt;


            }
        }
    }
    /*
    for(std::string::iterator it = posicion.begin(); it != posicion.end(); ++it)
    {
  i++;
             nombreObjeto = "";



}
*/
}



ModeloTablero::ModeloTablero( const ModeloTablero& original):
    //  numeroHijos(0),
    //Score(0),
    // fichaMovida(""),
    //  vectorMov(NULL),
    turnoN(original.turnoN)
  , alPaso(original.alPaso)
  , nodoInicial(false)
  ,valorAtaque(0)
 // , valorDefensivo(0)
  //,casillasInt(original.casillasInt.begin(), original.casillasInt.end())
   ,casillasProtegidas(original.casillasProtegidas)

{
    std::cout << "EMPEEZA" <<std::endl;
    //jugadaPrincipal = new char[2];

   // std::cout << "jugadaPrincipal,size " << jugadaPrincipal.l  <<std::endl;


//	casillaSeleccionada= original.casillaSeleccionada;

//	vectorJugada = original.vectorJugada;
  //  jugadaPrincipal[0] = original.jugadaPrincipal[0];
  //  jugadaPrincipal[1] = original.jugadaPrincipal[1];
    std::cout << "EMPEEZ2222222A" <<std::endl;
	//std::cout << "original.jugadas: " << original.vectorJugada.size() << std::endl;

	
//	std::cout << "jugadas.size: " << vectorJugada.size() << std::endl;

    for(int i=0; i<144;i++)
    {
        casillasInt[i] = original.casillasInt[i];
    }
    std::cout << "jugadapri" <<std::endl;
	//std::cout << jugadaPrincipal << std::endl;

   // std::cout <<(int)jugadaPrincipal<<std::endl;

   // std::cout <<jugadaPrincipal[1] <<std::endl;
	//cada nuevo tablero deberia tener una jugada lista
//	if (vectorJugada.size() > 1)
	//{
	//	std::cout << "int0: " << (int)vectorJugada[0] << std::endl;

	//	std::cout << "int1: " << (int)vectorJugada[1] << std::endl;

	//	std::cout << "vectorJugada.at(0);: " << vectorJugada.at(0) << std::endl;

	//	std::cout << "vectorJugada.at(1);: " << vectorJugada.at(1) << std::endl;





		//MIRO SI LA FICHA QUE ESTOY MOVIENDO ESTABA PROTEGIDA ANTES, no es optimo ya que se calcula por cada movimiento de la misma ficha.
		//Solucion: cuando muevo ficha mirar que fichas la protenger, mejor pero el primer turno no habra lista fichas protegidas
		//CUANTAS MAS CASILLAS PROTEGIA ANTES DE MOVER, PEOR ES EL MOVIMIENTO DESPUES





		//	int protegida = casillasProtegidas.find(casillaSeleccionada.;

		//std::vector<std::array<int, 2>> temp = casillasProtegidas;
		//	for (std::vector<std::array<int, 2>>::iterator it = temp.begin(); it != temp.end(); it++)
		//	{
		//		std::array<int, 2> protegida = *it;


		//if ( == vectorJugada[0])
		//{





		//}
		//	}


	//}

	
	std::cout << "FIN NUEVOTABLERO" <<std::endl;

    //  cambiaTurno();
    // jugada = new unsigned char[2];
}




ModeloTablero::~ModeloTablero()
{
    borraJugadas();
    
	std::cout << "~ModeloTablero" << std::endl;

    //delete jugada;
    //jugada = NULL;
}

//void ModeloTablero::borraJugadas(){


//}



void ModeloTablero::borraJugadas()
{
	std::cout << "borraJugadas" << std::endl;

    if (!testMapJugadas.empty())
    {

		for (std::map<int,std::vector<std::vector<int>>>::iterator it = testMapJugadas.begin(); it != testMapJugadas.end(); it++)
        {

			std::vector<std::vector<int>> vec = it->second;


						std::cout << "testmapjug" << vec.size()<< std::endl;




			for (std::vector<std::vector<int>>::iterator it2 = vec.begin(); it2 != vec.end(); it2++)
			{
				std::cout << "it2" << std::endl;


				std::vector<int> vecdos = *it2;

				vecdos.clear();
			
			}



			vec.clear();

			//std::vector<int> jugada = *it;
            std::cout << "BORRA JUGADAS FORRR1"<<std::endl;

            //	for (std::vector<unsigned char[2]>::iterator itt = jugada.begin(); itt!=jugada.end(); itt++)
            // {

            //unsigned char* movimiento = *itt;



            //delete []movimiento;


            //   movimiento = NULL;

            //}


            // jugada.clear();

        }

        //  numeroHijos=0;
		testMapJugadas.clear();

        std::cout << "ENDDD"<<std::endl;

    }



   // if (!casillasProtegidas.empty())
  //  {
		//for (std::unordered_map<int,int>::iterator it = casillasProtegidas.begin(); it != casillasProtegidas.end(); it++)
       // {
            //  char* jugada = *it;


            // if (casillasProtegidas.at(i) != NULL)
            //  {
            // delete jugada;
            //jugada = NULL;
            // }
      //  }
        //  numeroHijos=0;



	std::cout << "BOORA PROTEGIDAS" << std::endl;

        casillasProtegidas.clear();
  //  }
		std::cout << "ENDDD2" << std::endl;

}



void ModeloTablero::generaTablero()
{



}

bool ModeloTablero::cambiaTurno(std::vector<int> vectorJugada)
{
	//APLICA LA JUGADA


	std::cout << "CACACACACACACACACMBIATURNO" << std::endl;

    //ESTO PODRIA SEPARARSE E IRIA MEJOR EN MODELO!!!

    // MUEVE
    //	for(std::vector<unsigned char[2]>::iterator it = jugadas.begin(); it != jugadas.end(); ++it)

   // std::cout << "jugadas.size() "<< vectorJugada.size()   <<std::endl;
	bool movBueno = false;

	std::cout << "ANTES" << std::endl;
	for (int i = 11; i >= 0; i--){
		for (int y = 0; y < 12; y++){
			if ((int)casillasInt[(i * 12) + y] == 0){
				std::cout << " -" << std::ends;
			}
			else if ((int)casillasInt[(i * 12) + y] == 99){
				std::cout << " " << std::ends;
			}
			else if ((int)casillasInt[(i * 12) + y] >= 0){
				std::cout << " " << (int)casillasInt[(i * 12) + y] << std::ends;
			}
			else
				std::cout << (int)casillasInt[(i * 12) + y] << std::ends;
		}
		std::cout << "" << std::endl;
	}



	//siempre deberia ser true
	if (vectorJugada.size() > 1)
	{




		//for (int i = 0; i < vectorJugada.size() - 1; i = i + 2)
		//{
		//	std::cout << "jugada " << i << ": " << (int)vectorJugada[i] << "/" << (int)vectorJugada[i + 1] << std::endl;
			//	unsigned char* jugada = *it;


			//si es 0 es un mov especia?

		
		//}



		//PEON

		if (casillasInt[vectorJugada[0]] == 1)
		{

			std::cout << "PE" << std::endl;

			int dif = vectorJugada[1] - vectorJugada[0];
			if (turnoN)
				dif = -dif;

			//DOBLE SALTO (LO MARCA PARA CAPTURAR AL PASO)
			if (vectorJugada[1] == 0 && (dif == 24))
			{
				alPaso = /*143-*/vectorJugada[1];
			}
			else alPaso = 0;




			std::cout << "PEOONEENNENEN" << std::endl;
			
			//PROMOCION A REINA
			if (vectorJugada.size() > 2 && vectorJugada[2] == 100)
				casillasInt[vectorJugada[0]] = 5;
		

			/*

			int filaReina = 9;
			int difSalto = 24;
			if (turnoN)
			{
				filaReina = 2;
				difSalto = -difSalto;
			}

			//int filaPromocion = 9;

			if ((vectorJugada[1]) / 12 == filaReina)
			{

				



			}

			*/

			


			/* }



		else if (casillasInt[jugada[0]] == intRey)
		{    //ENROQUE!

		int intRey = Rey;
		if(turnoN)
		{
		intRey = -intRey;

		}


		std::cout << "MIRA ENROQUE !!!!!!!!!!!!!!!!"<< turnoN <<std::endl;

		int intTorre = Torre;
		int dif = jugada[1] - jugada[0];

		if(turnoN)

		std::cout << "ES TURNO NEGRA !!!!!!!!!!!!!!!!"<<std::endl;

		{
		intTorre = -Torre;
		//	dif = -dif;
		}

		std::cout << "jugadas! "<< jugada[0] <<    "/"  <<  jugada[1]<<std::endl;


		std::cout << "dif!! "<< dif <<std::endl;

		// if (difCol<0 ) difCol = -difCol;
		//int fila =casillaDestinoTemp->getPosicion().Fila;
		//enroque a la derecha (CORTO)
		if (dif == 2){
		std::cout << "ENTRA EN ENROQUE CORTO!!!!!!!!!!!!!!!!"<<std::endl;

		casillasInt[jugada[1] + 1] = 0;
		casillasInt[jugada[1] - 1] = intTorre;

		}



		else if	(dif == -2)
		{//enroque a la IZQUIERDA (LARGO)
		std::cout << "ENTRA EN ENROQUE LARGO!!!!!!!!!!!!!!!!"<<std::endl;
		casillasInt[jugada[1] - 2] = 0;
		casillasInt[jugada[1] + 1] = intTorre;
		}
		alPaso = 0;
		*/
		}
		else alPaso = 0;

			
		casillasInt[vectorJugada[1]] = casillasInt[vectorJugada[0]];
		casillasInt[vectorJugada[0]] = 0;


		//SOLO EN CASO DE ENROQUE DE LA REINA O COMER AL PASO
		if (vectorJugada.size() > 3)
		{
			casillasInt[vectorJugada[3]] = casillasInt[vectorJugada[2]];
		}

		//EVALUA JAQUE PARA EL TURNO EN JUEGO, (SI HAY JAQUE SERÁ ELIMINADO)
		if (!evaluaJaque())
		{
			movBueno = true;
		}
	}




    turnoN = !turnoN;

	std::cout << "DESPUES" << std::endl;

	for (int i = 11; i >= 0; i--){
		for (int y = 0; y < 12; y++){



			if ((int)casillasInt[(i * 12) + y] == 0){
				std::cout << " -" << std::ends;

			}else if ((int)casillasInt[(i * 12) + y] == 99){
				std::cout << " " << std::ends;

			}
			else if ((int)casillasInt[(i * 12) + y] >= 0){
				std::cout << " " << (int)casillasInt[(i * 12) + y] << std::ends;
			}
						
			else
			std::cout << (int)casillasInt[(i *12)+ y] << std::ends;


		}
		std::cout <<""<< std::endl;

	}
	vectorJugada.clear();
	testMapJugadas.clear();

	std::cout << "movBueno" << std::endl;

    return movBueno;
}

std::array<char, 144> ModeloTablero::invierteTablero(std::array<char, 144> casillas)
{
	std::array<char, 144> casillasTemp;
    //NORMALIZA EL TABLERO PARA EL CAMBIO DE TURNO
    for(int y=0; y<12;y++)
    {
        for(int i=0; i<12;i = i++)
        {
            //INVIERTE EL SIGNO DE LAS FICHAS Y LA POSICION DE LA FILA
            if (casillas[(i*12)+y] != 99)
            {
                casillasTemp[((11-i)*12)+11-y] = -casillas[(i*12)+y];
            }
            else casillasTemp[(i*12)+y] = 99;
        }
    }

    // for(int i=0; i<144;i++)
    //     casillas[i] = casillasTemp[i];

    return casillasTemp;

}


bool ModeloTablero::evaluaJaque()
{
    int posRey = 999;

    //int fichas[6];
    //    std::cout << "EVALUA JAQUturE : "<<turnoN  <<std::endl;


    int fichaRey = -6;
    int fichaReina = -5;
    int fichaPeon = -1;
    int fichaAlfil = -3;
    int fichaCaballo = -2;
    int fichaTorre = -4;

    if (turnoN)
    {
        fichaRey = 6;
        fichaReina = 5;
        fichaPeon = 1;
        fichaAlfil = 3;
        fichaCaballo = 2;
        fichaTorre = 4;
    }

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
                if(i==1 && (ficha == fichaRey || (!turnoN && ficha ==fichaPeon)))
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
                if(i==1 && (ficha == fichaRey ||(!turnoN && ficha ==fichaPeon)))
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
                //REY							//PEON BLANCO
                if(i==1 && (ficha == fichaRey || (turnoN && ficha ==fichaPeon)))
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
                //REY							//PEON BLANCO
                if(i==1 && (ficha == fichaRey || (turnoN && ficha ==fichaPeon)))
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


