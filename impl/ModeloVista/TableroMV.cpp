#include "../../headers/ModeloVista/TableroMV.h"
TableroMV::TableroMV(std::string nombre, int tipo) : ObjetoEscena(nombre, tipo, "Tablero", "MaterialTablero")
    , esNegra(0),
    //muerta(0),
    tipo_TableroMV(tipo),
	seleccionada(0)
   // salto(false)
    // ,casilla(0)
	 ,  casillaSobrevolada(0)
  , casillaSeleccionada(0)
    ,peonesPromocionados(0)
  ,    fichaSeleccionada(false)
{
							    std::cout << "delo::getSingleto"<<std::endl;

	modelo = Modelo::getSingletonPtr();
								    std::cout << "creaCasillas"<<std::endl;

	creaCasillas();
								    std::cout << "creaPiezas"<<std::endl;

	creaPiezas();
									    std::cout << "sale"<<std::endl;

}

TableroMV::~TableroMV()
{
}

TableroMV::TableroMV( const TableroMV& TableroMVOriginal, std::string nombre, int tipo ): ObjetoEscena(nombre, tipo, "Tablero", "MaterialTablero")
    , esNegra(TableroMVOriginal.esNegra),
   // muerta(0),
    tipo_TableroMV(tipo),
	seleccionada(0)
   // ObjetoOgre(nombre)
   // salto(false)
  //  tipo_TableroMV = TableroMVOriginal
{
}




Casilla* TableroMV::getCasillaSeleccionada()
{
    return casillaSeleccionada;
}

Casilla* TableroMV::getCasillaSobrevolada()
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

void TableroMV::setCasillaSeleccionada(Casilla* nodo)
{
					   	std::cout << "setCasillaSeleccionada por NODO"<<std::endl;

    if (casillaSeleccionada != 0)
    {
        Ficha* ficha = static_cast<Ficha*>(casillaSeleccionada->getHijo(0));
        ficha->apaga();
        // casillaSeleccionada->apagaCasilla();
        //          casillaSeleccionada = 0;
    }



    fichaSeleccionada = true;
    casillaSeleccionada = nodo;
    Ficha* ficha = static_cast<Ficha*>(nodo->getHijo(0));
    ficha->ilumina();

}
void TableroMV::setCasillaSobrevolada(Casilla* nodo)
{
    casillaSobrevolada = nodo;
}

void TableroMV::setCasillaSeleccionada(int posicion)
{
				   	std::cout << "setCasillaSeleccionada por posicion"<<std::endl;

    if (posicion < 0)
    {
        fichaSeleccionada = false;
        Ficha* ficha = static_cast<Ficha*>(casillaSeleccionada->getHijo(0));
        ficha->apaga();
        // casillaSeleccionada->apagaCasilla();
        casillaSeleccionada = 0;
    }
    else casillaSeleccionada = static_cast<Casilla*>(getHijo(posicion));
    
    fichaSeleccionada = true;
    Ficha* ficha = static_cast<Ficha*>(casillaSeleccionada->getHijo(0));
    ficha->ilumina();

}

void TableroMV::setCasillaSobrevolada(int posicion)
{
    if (posicion < 0)
    {
        casillaSobrevolada = 0;
    }
    else casillaSobrevolada = static_cast<Casilla*>(getHijo(posicion));
}


void TableroMV::creaCasillas()
{
    std::string columnas ="ABCDEFGH";
												    std::cout << "popo"<<std::endl;

    int contFila = 0;
    enColummas contColumna = COL_A;
    std::stringstream saux;
    ObjetoEscena* objeto;
	std::string material;

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

			material = "MaterialCasillaNegra";
          //  objeto->esNegra = true;
			  

           // objeto->cambiaMaterial("MaterialCasillaNegra");
        }else {
			material = "MaterialCasillaBlanca";

		}


		objeto = new Casilla(saux.str(), material);
       // objeto->setPosicion(contFila, contColumna);
		objeto->yRel = -10*contFila;
		objeto->xRel = -10*contColumna;
       // objeto->trasladar(-10*contFila,-10*contColumna);

        agregaHijo(objeto);

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
	std::string materialName;
	int rotation;
	int move;
	 int mask;
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
	    materialName = "MaterialFichaBlanca";
		
	break;
	case 'b':
        nombreObjeto << ("(T)Torre");       
		mask = BLANCAS;
		meshName = "Torre";
	    materialName = "MaterialFichaBlanca";
  
  
	break;
	case 'c':
		  nombreObjeto << ("(C)Caballo");       
		mask = BLANCAS;
		meshName = "Caballo";
	    materialName = "MaterialFichaBlanca";
	break;
	case 'd':
		  nombreObjeto << ("(T)Alfil");       
		mask = BLANCAS;
		meshName = "Alfil";
	    materialName = "MaterialFichaBlanca";
	break;
	case 'e':
		  nombreObjeto << ("(D)Reina");       
		mask = BLANCAS;
		meshName = "Reina";
	    materialName = "MaterialFichaBlanca";
	break;
	case 'f':
		  nombreObjeto << ("(R)Rey");       
		mask = BLANCAS;
		meshName = "Rey";
	    materialName = "MaterialFichaBlanca";
	break;
	case 'z':
		 nombreObjeto << ("(P)Peon_");       
		//new ¿Peon?
		mask = NEGRAS;
		meshName = "Peon";
	    materialName = "MaterialFichaNegra";
		
	break;
	case 'y':
		nombreObjeto << ("(T)Torre");       
		mask = NEGRAS;
		meshName = "Torre";
	    materialName = "MaterialFichaNegra";
	break;
	case 'x':
		nombreObjeto << ("(C)Caballo");       
		mask = NEGRAS;
		meshName = "Caballo";
	    materialName = "MaterialFichaNegra";
		rotation = 180;
		move = 70;	 
	break;
	case 'w':
		 nombreObjeto << ("(T)Alfil");       
		mask = NEGRAS;
		meshName = "Alfil";
	    materialName = "MaterialFichaNegra";
		rotation = 180;
		move = 70;	
	break;
	case 'v':
		 nombreObjeto << ("(D)Reina");       
		mask = NEGRAS;
		meshName = "Reina";
	   materialName = "MaterialFichaNegra";
	break;
	case 'u':
		 nombreObjeto << ("(R)Rey");       
		mask = NEGRAS;
		meshName = "Rey";
	    materialName = "MaterialFichaNegra";
	break;
	}
														    std::cout << "crea nuevaFicha"<<std::endl;

			 nombreObjeto << (i);       
			 														    std::cout << "crea nuevaFicha3333"<<std::endl;

		 Ficha* nuevaFicha = new Ficha(nombreObjeto.str(), mask, meshName, materialName);
		 nuevaFicha->rotate = rotation;
		 nuevaFicha->xRel = move;	
		 	nuevaFicha->yRel = move;		 														   
			std::cout << "agregaHijo3"<<std::endl;

	 getHijo(i)->agregaHijo(nuevaFicha);

	//do_things_with(*it);
	}

	 i++;
	}
	
													    std::cout << "fin creaPiezas"<<std::endl;
	
}