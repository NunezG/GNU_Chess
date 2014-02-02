#include "../../headers/ModeloVista/TableroMV.h"
TableroMV::TableroMV() : //ObjetoEscena(nombre, tipo, "Tablero", "MaterialTablero")
   // , esNegra(0),
    //muerta(0),
   // tipo_TableroMV(tipo),
	seleccionada(0)
   // salto(false)
    // ,casilla(0)
	 ,  casillaSobrevolada(0)
  , casillaSeleccionada(0)
    ,peonesPromocionados(0)
  ,    fichaSeleccionada(false)
  //, listaNodos(0)
{

	//tambien se puede hacer static o solo metodos que se llaman y llaman a tblero
	//objetoPadre = obj;
							    std::cout << "delo::getSingleto"<<std::endl;
								//listaNodos.push_back(this);
	modelo = Modelo::getSingletonPtr();
								    std::cout << "creaCasillas en TABLEROMV"<<std::endl;

	//creaCasillas();
								    std::cout << "creaPiezas"<<std::endl;

	//creaPiezas();
									    std::cout << "sale"<<std::endl;

}

TableroMV::~TableroMV()
{
}





ObjetoEscena* TableroMV::getCasillaSeleccionada()
{
    return casillaSeleccionada;
}

ObjetoEscena* TableroMV::getCasillaSobrevolada()
{
    return casillaSobrevolada;
}

int TableroMV::getAlPaso()
{
    return alPaso;
}

void TableroMV::setAlPaso(int casilla)
{
    alPaso = casilla;
}

void TableroMV::setCasillaSeleccionada(ObjetoEscena* nodo)
{
					   	std::cout << "setCasillaSeleccionada por NODO"<<std::endl;

    if (casillaSeleccionada != 0)
    {
        ObjetoEscena* ficha = casillaSeleccionada->getHijo(0);
        ficha->cambiaMaterial(0);
        // casillaSeleccionada->apagaCasilla();
        //          casillaSeleccionada = 0;
    }



    fichaSeleccionada = true;
    casillaSeleccionada = nodo;
    ObjetoEscena* ficha = nodo->getHijo(0);
    ficha->cambiaMaterial(1);

}
void TableroMV::setCasillaSobrevolada(ObjetoEscena* nodo)
{
    casillaSobrevolada = nodo;
}

void TableroMV::setCasillaSeleccionada(int posicion)
{
				   	std::cout << "setCasillaSeleccionada por posicion"<<std::endl;

    if (posicion < 0)
    {
        fichaSeleccionada = false;
        ObjetoEscena* ficha = casillaSeleccionada->getHijo(0);
        ficha->cambiaMaterial(0);
        // casillaSeleccionada->apagaCasilla();
        casillaSeleccionada = 0;
									   	std::cout << "fin setcasisis"<<std::endl;

    }
    else 
		
		{
			casillaSeleccionada =objetoPadre->getHijo(posicion);
    
    fichaSeleccionada = true;
    ObjetoEscena* ficha = casillaSeleccionada->getHijo(0);
    ficha->cambiaMaterial(1);

	}

}

void TableroMV::setCasillaSobrevolada(int posicion)
{
    if (posicion < 0)
    {
        casillaSobrevolada = 0;
    }
    else casillaSobrevolada = objetoPadre->getHijo(posicion);
}


void TableroMV::creaCasillas()
{
    std::string columnas ="ABCDEFGH";
												    std::cout << "popo"<<std::endl;

    int contFila = 0;
    enColummas contColumna = COL_A;
    std::stringstream saux;
    ObjetoEscena* objeto;
	std::string materials[2];

												    std::cout << "fopr"<<std::endl;

    for (int i = 0; i < 64; ++i)
    {

        saux.str("");

        saux  << ( contFila + 1 ) << columnas[contColumna];

       // objeto->creaModelo3D(mSceneMgr, "Casilla", CASILLA);

        //SI ES COLUMNA IMPAR Y FILA IMPAR: CASILLA NEGRA
        if ((i%2 != 0
             && contFila % 2 != 0)
                 || (i%2 == 0
                   && contFila % 2 == 0) )
        {

			materials[0] = "MaterialCasillaNegra";
			materials[1] = "MaterialCasillaNegraIluminada";

          //  objeto->esNegra = true;


           // objeto->cambiaMaterial("MaterialCasillaNegra");
        }else {
			materials[0] = "MaterialCasillaBlanca";
			materials[1] = "MaterialCasillaBlancaIluminada";

		}

		objetoPadre->creaHijo(saux.str(), CASILLA, "Casilla", materials);
		//objeto = new Casilla(saux.str(), material);
		objeto = objetoPadre->getHijo(saux.str());
		//if (materials[0] == "MaterialCasillaNegra")	objeto->esNegra = true;

        objeto->setPosicion(contFila, contColumna);
		objeto->yRel = -10*contFila;
		objeto->xRel = -10*contColumna;
       // objeto->trasladar(-10*contFila,-10*contColumna);
	//	listaNodos.push_back(objeto);
		listaNodos.push_back(objeto);
        objetoPadre->agregaHijo(objeto);

        if (contColumna == COL_H)
        {
            contFila++;
            contColumna = COL_A;
        }
        else contColumna = enColummas(static_cast<int>(contColumna)+1);
    }
}

void TableroMV::creaPiezas()
{
													    std::cout << "creaPiezas"<<std::endl;
	std::string posInicial = modelo->posInicial;
	 std::stringstream nombreObjeto;
    //Ogre::String posCasilla;
    int posCasilla;

	std::string meshName;
	std::string materials[2];
	int rotation;
	int move;
	 int mask;
	 int tipoFicha;
   // Ficha* objeto;
	//ObjetoOgre* objeto;
	 int i = 0;

	for(std::string::iterator it = posInicial.begin(); it != posInicial.end(); ++it) 
	{
		move = 0;
 	    rotation = 0;

		nombreObjeto.str("");
	if (*it != '0')
	{
			
	switch (*it)
	{	
	case 'a':
		nombreObjeto << ("(P)Peon_");       
		//new ¿Peon?
		mask = BLANCAS;
		meshName = "Peon";
		tipoFicha = 1;	
	break;
	case 'b':
        nombreObjeto << ("(T)Torre");       
		mask = BLANCAS;
		meshName = "Torre";
		tipoFicha = 4;
	break;
	case 'c':
		  nombreObjeto << ("(C)Caballo");       
		mask = BLANCAS;
		meshName = "Caballo";
		tipoFicha = 2;
	break;
	case 'd':
		  nombreObjeto << ("(T)Alfil");       
		mask = BLANCAS;
		meshName = "Alfil";
		tipoFicha = 3;
	break;
	case 'e':
		  nombreObjeto << ("(D)Reina");       
		mask = BLANCAS;
		meshName = "Reina";
		tipoFicha = 5;
	break;
	case 'f':
		  nombreObjeto << ("(R)Rey");       
		mask = BLANCAS;
		meshName = "Rey";
		tipoFicha = 6;

	break;
	case 'z':
		 nombreObjeto << ("(P)Peon_");       
		//new ¿Peon?
		mask = NEGRAS;
		meshName = "Peon";
		tipoFicha = 1;
	break;
	case 'y':
		nombreObjeto << ("(T)Torre");       
		mask = NEGRAS;
		meshName = "Torre";
		tipoFicha = 4;
	break;
	case 'x':
		nombreObjeto << ("(C)Caballo");       
		mask = NEGRAS;
		meshName = "Caballo";
		rotation = 180;
		move = 70;	 
		tipoFicha = 2;
	break;
	case 'w':
		 nombreObjeto << ("(T)Alfil");       
		mask = NEGRAS;
		meshName = "Alfil";
		rotation = 180;
		move = 70;	
		tipoFicha = 3;
	break;
	case 'v':
		 nombreObjeto << ("(D)Reina");       
		mask = NEGRAS;
		meshName = "Reina";
	   	tipoFicha = 5;
	break;
	case 'u':
		 nombreObjeto << ("(R)Rey");       
		mask = NEGRAS;
		meshName = "Rey";
	    tipoFicha = 6;
	break;
	}

	if (mask == BLANCAS)
	{
	    materials[0] = "MaterialFichaBlanca";
	    materials[1] = "MaterialFichaBlancaIluminada";
	}else{
	    materials[0] = "MaterialFichaNegra";
	    materials[1] = "MaterialFichaNegraIluminada";
	}

														    std::cout << "crea nuevaFicha"<<std::endl;
			 nombreObjeto << (i);       
			 														    std::cout << "crea nuevaFicha3333"<<std::endl;

		// Ficha* nuevaFicha = new Ficha(nombreObjeto.str(), mask, meshName, materialName);
													   
			std::cout << "agregaHijo3"<<std::endl;

	 objetoPadre->getHijo(i)->creaHijo(nombreObjeto.str(), mask, meshName, materials);
	 ObjetoEscena* nuevaFicha = objetoPadre->getHijo(i)->getHijo(nombreObjeto.str());


	//  nuevaFicha->tipo_Ficha= tipoFicha;
		 nuevaFicha->rotate = rotation;
		 nuevaFicha->xRel = move;	
		 	nuevaFicha->yRel = move;		 			


	//do_things_with(*it);
	}

	 i++;
	}
	
													    std::cout << "fin creaPiezas"<<std::endl;
	
}


void TableroMV::actualizaTablero()
{  
																   	std::cout << "actualizaTablero" <<std::endl;
	
																		setCasillaSeleccionada(-1);

																	ObjetoEscena* objEsc;

//	std::cout << "actualizaNodo: "<< nodo->getNombre()<<std::endl;
	 char casillasInt2 = modelo->tableroModelo->casillasInt[1];
	 // mira jugadaelegida para ver la posicion de las fichas

	 //inicial (la ficha a mover), posicion en el tablero de 144 casillas
	// modelo->jugadaElegida[0];
	 //	final (la ficha a eliminar o casilla vacia)
	// modelo->jugadaElegida[1];
	 
	 std::cout << "modelo->jugadaElegida[0]"<< (int)modelo->jugadaElegida[0] <<std::endl;
	 	 std::cout << "modelo->jugadaElegida[1]"<< (int)modelo->jugadaElegida[1] <<std::endl;


	  posicion inicial;
    posicion final;

    inicial.Fila = (modelo->jugadaElegida[0]/12)-2;
    inicial.Columna = (modelo->jugadaElegida[0]%12)-2;
    final.Fila = (modelo->jugadaElegida[1]/12)-2;
    final.Columna = (modelo->jugadaElegida[1]%12)-2;

	//POSICION INICIAL EN EL TABLERO NUEVO (inicial.Fila * 8) + inicial.Columna



			//for (std::vector<ObjetoEscena*>::iterator it = listaNodos.begin(); it!=listaNodos.end(); it++)
			//	 {
					 					  	std::cout << "foroforrr" <<std::endl;

					 //casilla anterior de la vista donde se encuentra el nodo a mover
			//	ObjetoEscena* nodo = *it;
											ObjetoEscena* nodo = objetoPadre->getHijo((inicial.Fila * 8) + inicial.Columna);
										objEsc = objetoPadre->getHijo((final.Fila * 8) + final.Columna);

			//	if (!nodo->sinHijos() && static_cast<Ficha*>(nodo->getHijo(0))->tipo_Ficha ==  modelo->tableroModelo->casillasInt[(i*12)+y])
			//	{

										 					  	std::cout << "parece que va a cambiar algo pachi" <<std::endl;

					ObjetoEscena* nodoFicha = nodo->getHijo(0);
															 					  	std::cout << "1" <<std::endl;

					nodo->eliminaHijo(0);
																				 					  	std::cout << "2" <<std::endl;

				if (!objEsc->sinHijos() )	objEsc->eliminaHijo(0);
																				 					  	std::cout << "3" <<std::endl;

					//nodo->eliminaHijo(0);
					objEsc->agregaHijo(nodoFicha);
																				 					  	std::cout << "4" <<std::endl;


			//	}


			// }





	for (int i = 2; i < 10; i++)
	{
		for (int y = 2; i < 10; i++)
		{
																		   	std::cout << "fofito" <<std::endl;
																	   	std::cout << ((i-2)*8)+y-2<<std::endl;
																					   	std::cout << "frente a" <<std::endl;
														   	std::cout << (i*12)+y<<std::endl;



				objEsc = objetoPadre->getHijo(((i-2)*8)+y-2);

				// (!objEsc->sinHijos() && objToRemove->sinHijos()) || (objEsc->sinHijos() && !objToRemove->sinHijos()) || (!objEsc->sinHijos() && !objToRemove->sinHijos() && objToRemove->getHijo(0)->getNombre() != objEsc->getHijo(0)->getNombre()))
		
			if ((objEsc->sinHijos() && modelo->tableroModelo->casillasInt[(i*12)+y] != 0) ||   (i*12)+y == objEsc->getHijo(0)->posInModel)
			{

																									   	std::cout << "ffffuuuuu" <<std::endl;

				
			if (modelo->tableroModelo->casillasInt[(i*12)+y] == 0)
			{
																					std::cout << "erp drp tatataababa"<<std::endl;

				objEsc->eliminaHijo(0);

			}


		}


																									   	std::cout << "nanaiii" <<std::endl;


//HAY QUE HACER PARA CAMBIO DE FORMA Y ESOOOO !!!!!!!!!!!!!!
			


}
}



	}





/*
void TableroMV::actualizaTablero()
{  
	
    Casilla* nodoCasillaTemporal = getCasillaSeleccionada();
    Casilla* casillaDestinoTemp =  getCasillaSobrevolada();

     setCasillaSobrevolada(-1);
     setCasillaSeleccionada(-1);

    if (!nodoCasillaTemporal->sinHijos())
    {
        casillaDestinoTemp->apagaCasilla();
        Ficha* ficha =  static_cast<Ficha*>(nodoCasillaTemporal->getHijo(0));

        //BORRA FICHA DE LA CASILLA
        nodoCasillaTemporal->eliminaHijo(0);

        //BORRA FICHA ENEMIGA DE LA CASILLA NUEVA
        if (!casillaDestinoTemp->sinHijos())
        {
            Ficha* ficha = static_cast<Ficha*>(casillaDestinoTemp->getHijo(0));
            casillaDestinoTemp->eliminaHijo(0);
            delete ficha;
            ficha = NULL;
        }
        casillaDestinoTemp->agregaHijo(ficha);

        if (ficha->tipo_Ficha == 6)
        {
            int difCol = casillaDestinoTemp->getPosicion().Columna - nodoCasillaTemporal->getPosicion().Columna;
            // if (difCol<0 ) difCol = -difCol;

            int fila =casillaDestinoTemp->getPosicion().Fila;

            if (difCol == 2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>( getHijo((fila*8)+7));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>( getHijo((fila*8) +casillaDestinoTemp->getPosicion().Columna-1));
                casillaTorre->agregaHijo(fichaTorre);
            }

            if (difCol == -2)
            {
                Casilla* casillaTorre = static_cast<Casilla*>( getHijo(fila*8));
                Ficha* fichaTorre = static_cast<Ficha*>(casillaTorre->getHijo(0));
                casillaTorre->eliminaHijo(0);

                casillaTorre = static_cast<Casilla*>(getHijo((fila*8) +casillaDestinoTemp->getPosicion().Columna+1));
                casillaTorre->agregaHijo(fichaTorre);
            }
        }

        if (ficha->tipo_Ficha == 1)
        {
            //MIRA SI PROMOCIONA PEON
            // Ficha* ficha = static_cast<Ficha*>(getCasillaSobrevolada()->getHijo(0));

            if((!getTurnoNegras()
                && casillaDestinoTemp->getPosicion().Fila == 7)
                    || (getTurnoNegras()
                        && casillaDestinoTemp->getPosicion().Fila == 0 ))
            {
                casillaDestinoTemp->eliminaHijo(0);

                // ficha = tablero->promocionaPeon(ficha);
                //  Ogre::Entity *entidadFicha;

                std::stringstream saux;

                saux.str("");
              //  saux << "ReinaPR_" <<  escenaMV->getTablero()->peonesPromocionados;

                delete ficha;
               //  escenaMV->peonesPromocionados++;

                FichaReina* nodoNuevo =new FichaReina(*ficha, saux.str());

                if (!getTurnoNegras())
                {
                   // nodoNuevo->creaModelo3D( escenaMV->getTablero()->manager,"Reina", escenaMV->getTablero()->BLANCAS);
                }
                else
                {
                   // nodoNuevo->creaModelo3D( escenaMV->getTablero()->manager,"Reina", escenaMV->getTablero()->NEGRAS);
                   // nodoNuevo->cambiaMaterial("MaterialFichaNegra");
                }
                casillaDestinoTemp->agregaHijo(nodoNuevo);
            }
            //return static_cast<FichaReina*>(nodoNuevo);


            //MIRA SI HAY O COME AL PASO
            int dif = casillaDestinoTemp->getPosicion().Fila - nodoCasillaTemporal->getPosicion().Fila;
            int difCol = casillaDestinoTemp->getPosicion().Columna - nodoCasillaTemporal->getPosicion().Columna;
            if (dif < 0 ) dif = -dif;
            if (difCol<0 ) difCol = -difCol;

            if( getAlPaso() > 0 && dif == 1 && difCol == 1)
            {
                //SOLO COMER AL PASO
                int fila =nodoCasillaTemporal->getPosicion().Fila;
                int columna =casillaDestinoTemp->getPosicion().Columna;

                if ( getAlPaso() == 24+(fila*12)+columna+2)
                {
                    Casilla* casillaAux = static_cast<Casilla*>( getHijo((fila*8)+columna));

                    if (!casillaAux->sinHijos())
                    {
                        casillaAux->eliminaHijo(0);
                    }
                }
            }
             setAlPaso(-1);

            if( dif == 2)
                 setAlPaso(24+(casillaDestinoTemp->getPosicion().Fila*12) +  casillaDestinoTemp->getPosicion().Columna+2);
        }
        else  setAlPaso(-1);

        //DESELECCIONA FICHA Y CASILLA
        //ficha->getNodoOgre()->showBoundingBox(false);
    }

//    turnoNegras = !turnoNegras;
}

*/