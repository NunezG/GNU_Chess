#include "Movimientos.h"
int Movimientos::casillaSeleccionada;
std::vector<int> Movimientos::vectorJugada;
std::vector<std::vector<int>> Movimientos::vectorJugadas;
std::vector<std::vector<int>> Movimientos::vectorJugadasPeores;
std::vector<std::vector<int>> Movimientos::vectorJugadasNormales;

bool Movimientos::generaMovimientos(ModeloTablero* miTablero)
{
	std::cout << "generaMovimientos" << std::endl;
	miTablero->casillasProtegidas.erase(miTablero->casillasProtegidas.begin(), miTablero->casillasProtegidas.end());
	miTablero->testMapJugadas.erase(miTablero->testMapJugadas.begin(), miTablero->testMapJugadas.end());

//	miTablero->testMapJugadas.clear();
    // ModeloTablero nuevoTablero;
    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS
	vectorJugadas.clear();
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

		if (valorCasilla > 0 && valorCasilla < 99)
		{
			std::cout << "MUEVE FICHA: " << (int)valorCasilla << std::endl;
			vectorJugada.clear();
			
			casillaSeleccionada = i;
			// bool fichamovida = false;
			bool resultado = false;
			switch (tipoFicha(valorCasilla))
			{
			case (Rey) :

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

			//iterador de jugadas para ordenar
			//tambien puede tenerse en cuenta si come fichas enemigas en un movimiento para ordenarlo en el mapa


			std::cout << "Mllelelelele" << std::endl;


			//std::cout << "METE EN VECTORES :" << miTablero->casillasProtegidas[miTablero->casillaSeleccionada] << std::endl;

			
			updateHashMap( miTablero);

				

			
		}
    }

	std::cout << "ACABA DE MOVER FICHJAH " << std::endl;

    return fichamovida;
}

void Movimientos::updateHashMap(ModeloTablero* miTablero)
{


	vectorJugadas.reserve(vectorJugadasNormales.size() + vectorJugadasPeores.size()); // preallocate memory
	vectorJugadas.insert(vectorJugadas.end(), vectorJugadasNormales.begin(), vectorJugadasNormales.end());
	vectorJugadas.insert(vectorJugadas.end(), vectorJugadasPeores.begin(), vectorJugadasPeores.end());

	vectorJugadasNormales.clear();
	vectorJugadasPeores.clear();

	std::cout << " miTablero->casillasProtegidas sizzs ANTES DE NADAAAAAAA en generamov " << miTablero->casillasProtegidas.size() << std::endl;

	std::cout << "METE EN VECTORES :" << miTablero->casillasProtegidas.count(casillaSeleccionada) << std::endl;

	std::cout << " miTablero->casillasProtegidas sizzs DESPUES DE PUTO OUT en generamov " << miTablero->casillasProtegidas.size() << std::endl;


	//	if (miTablero->casillasProtegidas[miTablero->casillaSeleccionada])

	if (vectorJugadas.size() != 0)
	{
		
		//el valor de ataque depnde de cada movimiento, se necesita otra lista pasa eso ya que una ficha puede atacar a varios enemigos
		std::map<int, std::vector<std::vector<int>>>::iterator itMap;
		int valorMovimiento = 0;
		if (miTablero->casillasProtegidas.count(casillaSeleccionada) > 0)
		{
			valorMovimiento = miTablero->casillasProtegidas[casillaSeleccionada];
		}

	//	valorMovimiento = valorMovimiento + miTablero->valorAtaque;

	

		//std::vector < std::vector<int>>*   vecc = new std::vector <std::vector<int>>(miTablero->vectorJugadas);
		std::cout << "valorMovimiento: " << valorMovimiento << std::endl;
		std::cout << "miTablero->valorAtaque: " << miTablero->valorAtaque << std::endl;

		for (std::vector < std::vector<int>>::iterator it = vectorJugadas.begin(); it != vectorJugadas.end(); it++)
		{
			std::vector<int> jugada = *it;

			itMap = miTablero->testMapJugadas.find(valorMovimiento);

			if (itMap != miTablero->testMapJugadas.end())
			{
				//	std::cout << "valor defensivo " << it->second << std::endl;
				//	std::cout << " casillaSeleccionada " << tablero->casillaSeleccionada << std::endl;
				std::cout << "VECT: " << vectorJugadas.size() << std::endl;

				std::cout << "INSERTA: " << itMap->second.size() << std::endl;




				//	std::copy(miTablero->vectorJugadas.begin(), miTablero->vectorJugadas.end(), std::back_inserter(it->second));


				itMap->second.push_back(jugada);

			//	itMap->second.insert(itMap->second.end(), jugada);

				//it->second = it->second.push_back(miTablero->vectorJugadas);

				std::cout << "FIN INSERTA: " << itMap->second.size() << std::endl;

				//	std::cout << "NUEVA SUMAAAAAAAAAAAAAA " << suma << std::endl;

				//tablero->valorDefensivo = it->second;

			}
			else
			{

				//std::copy(miTablero->vectorJugadas.begin(), miTablero->vectorJugadas.end(), vecc);
				std::cout << "NUEVO VALOR DEFENSIVO: " << valorMovimiento << std::endl;

				std::vector < std::vector<int>>   vecc;
				vecc.push_back(jugada);
				miTablero->testMapJugadas.insert(std::make_pair(valorMovimiento, vecc));

			}
			std::cout << "size vectorJugadas " << vectorJugadas.size() << std::endl;
			std::cout << " miTablero->casillasProtegidas sizzs final en generamov " << miTablero->casillasProtegidas.size() << std::endl;

		}
	}

	casillaSeleccionada = 0;
	vectorJugadas.clear();
	vectorJugada.clear();

}

bool Movimientos::movimientosUnaFicha(ModeloTablero* miTablero, int posicion)
{
    // ModeloTablero nuevoTablero;
    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS
	miTablero->casillasProtegidas.erase(miTablero->casillasProtegidas.begin(), miTablero->casillasProtegidas.end());

    bool fichamovida = false;
    
    //CADA VEZ QUE ENCUENTRA UNA FICHA APLICA SUS MOVIMIENTOS
    //  for (int i = 26; i< 118;i++)
    //  {

    // }
	casillaSeleccionada = posicion;

    //  int casilla = (i*12)+y;
	//vectorJugada.push_back(posicion);



	std::cout << "movvvvv" << std::endl;
	//std::cout << miTablero->casillaSeleccionada << std::endl;

	char valorCasilla = miTablero->casillasInt[casillaSeleccionada];

    if (miTablero->turnoN) valorCasilla = -valorCasilla;

	std::cout << "swich" << std::endl;
	std::cout << tipoFicha(valorCasilla) << std::endl;

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



	//Usar una list o un std::map para ordenar? añadir casillas protegidas.
	

	std::cout << "fin movvvvv" << std::endl;


	updateHashMap(miTablero);



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
	int casilla = casillaSeleccionada;
	int nuevaCasilla = casilla + 12;
	int casillaCome = casilla + 11;
	int casillaComeSec = casilla + 13;
	int salto = casilla + 24;

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
		std::cout << "movvvvv NORMAL" << std::endl;

        // miTablero->jugada[0] = casilla;
		vectorJugada.push_back(casillaSeleccionada);
		vectorJugada.push_back(nuevaCasilla);
       // miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
        //std::cout << "MUEVE NORMAL : "  <<  miTablero->jugadas  <<std::endl;

        //std::cout << "MUEVE NORMAL2 : "  <<  miTablero->jugadaPrincipal  <<std::endl;

       // std::cout << "MUEVE NORMAL4 : "  <<  miTablero->jugadaPrincipal[0]  << " / "<< miTablero->jugadaPrincipal[1]  <<std::endl;

        //std::cout << "MUEVE NORMAL4 : "  <<  (int)miTablero->jugadaPrincipal[0]  << " / "<< (int)miTablero->jugadaPrincipal[1]  <<std::endl;

		//PROMOCION DE PEON
		if ((miTablero->turnoN && vectorJugada[1] / 12 == 2) || (!miTablero->turnoN && vectorJugada[1] / 12 == 9))
		{
			std::cout << "movvvvv NORMAL PROM" << std::endl;

			vectorJugada.push_back(100);
		}


        nuevoMovimiento(miTablero);
        muevePeon = true;
    }
    
    //DOBLE SALTO
    if(((!miTablero->turnoN && casilla/12 == 3) || (miTablero->turnoN && casilla/12 == 8)) && miTablero->casillasInt[nuevaCasilla] == 0 && miTablero->casillasInt[salto] == 0)
    {
		std::cout << "MUEVE SALTO " << std::endl;

        // miTablero->jugada[0] = casilla;
		vectorJugada.push_back(casillaSeleccionada);
		vectorJugada.push_back(salto);
		//miTablero->jugadas = miTablero->jugadas + miTablero->jugadas[0] + miTablero->jugadas[1];

        nuevoMovimiento(miTablero);
        muevePeon = true;

    }
    
  
    
    //COME ENEMIGA
    if ((!miTablero->turnoN && miTablero->casillasInt[casillaCome] < 0) || (miTablero->turnoN && miTablero->casillasInt[casillaCome] > 0 && miTablero->casillasInt[casillaCome] != 99))
    {
		std::cout << "MUEVE COME 1 " << std::endl;

        // miTablero->jugada[0] = casilla;
		vectorJugada.push_back(casillaSeleccionada);
		vectorJugada.push_back(casillaCome);
        //miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
		if ((miTablero->turnoN && vectorJugada[1] / 12 == 2) || (!miTablero->turnoN && vectorJugada[1] / 12 == 9))
		{
			 vectorJugada.push_back(100);
		}
        nuevoMovimiento(miTablero);
        muevePeon = true;

        //miTablero->casillasInt[casilla] = 1;
    }
    else if ((!miTablero->turnoN && miTablero->casillasInt[casillaCome] > 0 && miTablero->casillasInt[casillaCome] != 99)  ||(miTablero->turnoN && miTablero->casillasInt[casillaCome] < 0))
    {
		std::cout << "MUEVE COME 1 prot " << std::endl;


		casillaProtegida(casillaCome, miTablero);

        
    }
    
    //COME ENEMIGA 2
    if ((!miTablero->turnoN && miTablero->casillasInt[casillaComeSec] < 0) || (miTablero->turnoN && miTablero->casillasInt[casillaComeSec] > 0  && miTablero->casillasInt[casillaComeSec] != 99))
    {
		std::cout << "MUEVE COME 2" << std::endl;

        // miTablero->jugada[0] = casilla;
		vectorJugada.push_back(casillaSeleccionada);
		vectorJugada.push_back(casillaComeSec);
      //  miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

		if ((miTablero->turnoN && vectorJugada[1] / 12 == 2) || (!miTablero->turnoN && vectorJugada[1] / 12 == 9))
		{
			vectorJugada.push_back(100);

			//miTablero->vectorJugada = miTablero->vectorJugada + (char)100;
		}

        nuevoMovimiento(miTablero);
        muevePeon = true;
        // miTablero->casillasInt[casilla] = 1;
        
    }else if ((!miTablero->turnoN && miTablero->casillasInt[casillaComeSec] > 0  && miTablero->casillasInt[casillaComeSec] != 99)  ||(miTablero->turnoN && miTablero->casillasInt[casillaComeSec] < 0))
    {
		std::cout << "MUEVE COME 2 prot " << std::endl;

		casillaProtegida(casillaComeSec, miTablero);

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

            int quitaEnemigo[2];
            quitaEnemigo[0] = miTablero->alPaso;
            quitaEnemigo[1] = 0;

			vectorJugada.push_back(casillaSeleccionada);
			vectorJugada.push_back(casillaCome);

           // miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
			vectorJugada.push_back(quitaEnemigo[0]);
			vectorJugada.push_back(quitaEnemigo[1]);
			//miTablero->vectorJugada = miTablero->vectorJugada + quitaEnemigo[0] + quitaEnemigo[1];


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

			int quitaEnemigo[2];
            quitaEnemigo[0] = miTablero->alPaso;
            quitaEnemigo[1] = 0;

			vectorJugada.push_back(casillaSeleccionada);
			vectorJugada.push_back(casillaComeSec);

          //  miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
			vectorJugada.push_back(quitaEnemigo[0]);
				vectorJugada.push_back(quitaEnemigo[1]);
			//miTablero->vectorJugada = miTablero->vectorJugada + quitaEnemigo[0] + quitaEnemigo[1];
				
            nuevoMovimiento(miTablero);
            muevePeon = true;

            // miTablero->casillasInt[miTablero->alPaso] = fichaEnemiga;
        }
    }
	std::cout << "RET PEON " << std::endl;

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

bool Movimientos::recorreCasillas(ModeloTablero* miTablero, int salto)
{
	int casilla = casillaSeleccionada;

	int nuevaCasilla = casillaSeleccionada + salto;
    // pasa = true;

    bool mueveFicha = false;
	std::cout << "recorre casillas(original) " << casillaSeleccionada << std::endl;
	std::cout << "recorre casillas " << nuevaCasilla << std::endl;

    while(miTablero->casillasInt[nuevaCasilla] == 0)
    {
		std::cout << "mueve a " << nuevaCasilla << std::endl;

		//vectorJugada.push_back(miTablero->casillaSeleccionada);
		//vectorJugada.push_back(nuevaCasilla);

		mueveFicha = movUnico(miTablero, nuevaCasilla);

		//  miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
       // nuevoMovimiento(miTablero);
       // mueveFicha = true;
        nuevaCasilla = nuevaCasilla+salto;
    }
    

	//LLEGA A OTRA FICHA O FINAL
  //  if (miTablero->casillasInt[nuevaCasilla] != 99)
   // {
      //  if((!miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] < 0) || (miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] > 0))
    //    {     //encuentra ficha  enemiga
		//	vectorJugada.push_back(miTablero->casillaSeleccionada);
		//	vectorJugada.push_back(nuevaCasilla);

           // miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
            nuevoMovimiento(miTablero);
			if(movUnico(miTablero, nuevaCasilla) == true)
				mueveFicha = true;
     //   }
    //    else if((!miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] > 0) || (miTablero->turnoN && miTablero->casillasInt[nuevaCasilla] < 0))
     //   {
            //encuentra ficha  amiga
		//	casillaProtegida(nuevaCasilla, miTablero);

			
     //   }
 //   }

    // miTablero->numCasillasProtegidas++;
    return mueveFicha;
}


bool Movimientos::movUnico(ModeloTablero* miTablero, int salto)
{


	if (miTablero->casillasInt[salto] != 99)
	{


		if (soloMov(miTablero, salto) == false)
		{
			std::cout << "protege" << std::endl;

			casillaProtegida(salto, miTablero);

			//este no se añadira al vector de jugadas pero hay que hacerlo para cambiar turno?
			//	nuevoMovimiento(miTablero);

			std::cout << " fin protege" << miTablero->casillasProtegidas.size() << std::endl;

		}

	}

	return false;
}


bool Movimientos::soloMov(ModeloTablero* miTablero, int salto)
{


	if (miTablero->casillasInt[salto] != 99)
	{


		if ((!miTablero->turnoN && miTablero->casillasInt[salto] <= 0) || (miTablero->turnoN && miTablero->casillasInt[salto] >= 0))
		{     //encuentra ficha  enemiga
			vectorJugada.push_back(casillaSeleccionada);
			vectorJugada.push_back(salto);

			// miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
			nuevoMovimiento(miTablero);
			return true;

		}
	

	}

	return false;
}



bool Movimientos::mueveCaballo(ModeloTablero* miTablero)
{
	std::cout << "muevecaballo111111" << std::endl;
	std::cout << "casillaSeleccionada" << casillaSeleccionada << std::endl;

	int casilla = casillaSeleccionada;

    bool mueveCaballo = false;

    int movimientos[8] = {-25, 25, -23, 23, -14, 14, -10, 10};
    
    for (int i = 0; i < 8; i++)
    {
       // if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
      //  {
			if (movUnico(miTablero, casilla + movimientos[i]) == true)
				mueveCaballo = true;
			




        //    if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] <= 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] >= 0))
        //    {
			//	std::cout << "muevecaballo " << movimientos[i] << std::endl;
				//	   vectorJugada.push_back(casilla);
					//   vectorJugada.push_back(casilla + movimientos[i]);
               // miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

            //    nuevoMovimiento(miTablero);
					//   std::cout << "fin muevecaballo"<<std::endl;

         //       mueveCaballo = true;
          //  }else if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] > 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] < 0))
         //   {
					  // std::cout << "protege caballo"<<std::endl;

			
					//   casillaProtegida(casilla + movimientos[i], miTablero);
			

				//este no se añadira al vector de jugadas pero hay que hacerlo para cambiar turno?
			//	nuevoMovimiento(miTablero);

			//	std::cout << " fin protege caballo" << miTablero->casillasProtegidas.size() << std::endl;

        //    }
      //  }
    }
    
    return mueveCaballo;
}

bool Movimientos::mueveRey(ModeloTablero* miTablero)
{  
	int casilla = casillaSeleccionada;
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
       //     miTablero->casillasInt[destino+1] = 0;
         //   miTablero->casillasInt[destino-1] = intTorre;
			char* jugEnroque;
			jugEnroque[0] = destino - 2;
			jugEnroque[1] = destino + 1;

			vectorJugada.push_back(casilla);
			vectorJugada.push_back(destino);

			vectorJugada.push_back(jugEnroque[0]);
			vectorJugada.push_back(jugEnroque[1]);    
			
			// miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

            nuevoMovimiento(miTablero);

         //   miTablero->casillasInt[destino+1] = intTorre;
      //      miTablero->casillasInt[destino-1] = 0;
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
			vectorJugada.push_back(casilla);
			vectorJugada.push_back(destino);
          //  miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];
			//std::vector<int> enroque;
			vectorJugada.push_back(jugEnroque[0]);
			vectorJugada.push_back(jugEnroque[1]);
			//miTablero->vectorJugada = miTablero->vectorJugada.push_back(enroque);

            nuevoMovimiento(miTablero);

            //miTablero->casillasInt[destino-2] == intTorre;
            //miTablero->casillasInt[destino+1] == 0;

            mueveRey = true;

        }

    }
    
    char movimientos[8] = {-1, 1, -12, 12, -13, 13, -11, 11};
    
    for (int i = 0; i < 8; i++)
    {
		if (movUnico(miTablero, casilla + movimientos[i]) == true)
			mueveRey = true;
      /*  if (miTablero->casillasInt[casilla+movimientos[i]] != 99)
        {
            if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] <= 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] >= 0))
            {
				vectorJugada.push_back(casilla);
				vectorJugada.push_back(casilla + movimientos[i]);
              //  miTablero->jugadas = miTablero->jugadas + miTablero->jugadaPrincipal[0] + miTablero->jugadaPrincipal[1];

                nuevoMovimiento(miTablero);
                mueveRey = true;
            }else if ((!miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] > 0) || (miTablero->turnoN && miTablero->casillasInt[casilla+movimientos[i]] < 0))
            {
				casillaProtegida(casilla + movimientos[i], miTablero);

                //miTablero->casillasProtegidas[miTablero->casillasInt[miTablero->jugada[0]]][miTablero->casillasInt[casilla+movimientos[i]]] = miTablero->casillasInt[casilla+movimientos[i]];

            }
        }

		*/
    }
    return mueveRey;
}


void  Movimientos::casillaProtegida(int casillaProtegida, ModeloTablero* miTablero)
{
	
	//protege[0] = miTablero->casillaSeleccionada;
	//protege[1] = miTablero->casillasInt[casillaProtegida];

	int valor = miTablero->casillasInt[casillaProtegida] - miTablero->casillasInt[casillaSeleccionada];
	if (miTablero->turnoN) valor = -valor;

	if (valor > 0)
	{
		std::cout << " casillaProtegida " << casillaProtegida << std::endl;
		std::cout << " fichaProtegida " << (int)miTablero->casillasInt[casillaProtegida] << std::endl;

		std::cout << " casillaProtectora " << casillaSeleccionada << std::endl;
		std::cout << " fichaProtectora " << (int)miTablero->casillasInt[casillaSeleccionada] << std::endl;
		std::cout << " valor " << valor << std::endl;

		std::unordered_map<int, int>::iterator it = miTablero->casillasProtegidas.find(casillaSeleccionada);

		if (it != miTablero->casillasProtegidas.end())
		{
			std::cout << " YA ExISTIAit->second " << it->second << std::endl;

			//int temp = it->second;
			it->second = it->second + valor;
			std::cout << " YA ExISTIAit->second despues " << it->second << std::endl;


		}
		else miTablero->casillasProtegidas.insert({ casillaSeleccionada, valor });
		//sera mejor actualizar en tiempo real las listas preferidas ya que si no se acaban calculando las protegidas solo al final del arbol y esto no es bueno 
		//ya que hay que priorizar las que estan protegidas en el momento

		std::cout << " miTablero->casillasProtegidas sizzs " << miTablero->casillasProtegidas.size() << std::endl;




	//	if (miTablero->casillasProtegidas.count(casillaProtegida) > 1)
		//	std::cout << "casillaProtegida!!!!: " << miTablero->casillasProtegidas.count(casillaProtegida) << std::endl;
	}


}


void  Movimientos::nuevoMovimiento(ModeloTablero *miTablero)
{



    // miTablero->vectorJugadas.sort();

    // unsigned char* jugada = new unsigned char[2];
    //  jugada[0] = miTablero->jugadaPrincipal[0];
    //jugada[1] = miTablero->jugadaPrincipal[1];

    // mainModelBoard->jugada[0] = jugadaElegida[0];
    // mainModelBoard->jugada[1] = jugadaElegida[1];

    //miTablero->jugadas.push_back(miTablero->jugadaPrincipal);
    std::cout << "NUEVOTABLERO" <<std::endl;
	std::cout << "table->jugadas.size: " << vectorJugada.size() << std::endl;

	std::cout << "table->jugadas: " << (int)vectorJugada[0] << "/" << (int)vectorJugada[1] << std::endl;

    ModeloTablero *tableroMovido = new ModeloTablero(*miTablero);


	int valorAtaque = 0;
	//cuanto menor sea el valor ANTES DE MOVER, mejor
	if (miTablero->casillasInt[vectorJugada[1]] == 0) valorAtaque = 0;
	else
	{
		std::cout << "jjjuu1:" << (int)tableroMovido->casillasInt[vectorJugada[0]] << std::endl;
		std::cout << "jjjuu2:" << (int)tableroMovido->casillasInt[vectorJugada[1]] << std::endl;

		valorAtaque = miTablero->casillasInt[vectorJugada[0]] + miTablero->casillasInt[vectorJugada[1]];
		if (miTablero->turnoN) valorAtaque = -valorAtaque;

		std::cout << "valorAtaque:" << valorAtaque << std::endl;

	}


	std::cout << "CAMBIATURNO" << std::endl;



	bool cambiado = tableroMovido->cambiaTurno(vectorJugada);
	std::cout << " FIN CAMBIATURNO" << std::endl;

    //SI NO HAY JAQUE A SU REY AL MOVER
    if (cambiado)
    {
		std::cout << "HA MOVIDO FICHA Y CAMBIADO TURNO CORRECTAMENTE : " << vectorJugada.size()<< std::endl;
		//int valorAtaque = miTablero->casillasInt[miTablero->vectorJugada[0]] + miTablero->casillasInt[miTablero->vectorJugada[1]];

       // if (miTablero->turnoN) valorAtaque = -valorAtaque;
        //cuanto menor sea el valor, mejor
		if (miTablero->casillasInt[vectorJugada[1]] != 0 && tableroMovido->valorAtaque != 0)
        {
			if (tableroMovido->valorAtaque < 0)
            {

				vectorJugadas.push_back(vectorJugada);
            }

			else if (tableroMovido->valorAtaque > 0)
            {
				vectorJugadasPeores.push_back(vectorJugada);
            }
		}
		else vectorJugadasNormales.push_back(vectorJugada);
    } else 		std::cout << "NO MUEVE  FICHA PORQUE EVALUA JAQUE??" <<std::endl;


	vectorJugada.clear();

	std::cout << "JUGAADSSSS?: " << vectorJugada.size() << std::endl;

    
    delete tableroMovido;
    tableroMovido = NULL;
}

