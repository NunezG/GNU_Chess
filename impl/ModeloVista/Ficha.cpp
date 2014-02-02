#include "../../headers/ModeloVista/Ficha.h"
Ficha::Ficha(std::string nombre, int tipo, std::string meshName, std::string materialName) :// ObjetoEscena(nombre, tipo, meshName, materialName)
     esNegra(0),
    //muerta(0),
    tipo_Ficha(tipo),
	seleccionada(0)
   // salto(false)
    // ,casilla(0)
{
}

Ficha::~Ficha()
{
}

Ficha::Ficha( const Ficha& fichaOriginal, std::string nombre, int tipo ):// ObjetoEscena(fichaOriginal, nombre, tipo)
    esNegra(fichaOriginal.esNegra),
   // muerta(0),
    tipo_Ficha(tipo),
	seleccionada(0)
   // ObjetoOgre(nombre)
   // salto(false)
  //  tipo_Ficha = fichaOriginal
{
}

/*void Ficha::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{
    if (mask == NEGRAS) esNegra = true;
    else if (mask == BLANCAS )esNegra = false;

   ObjetoOgre::creaModelo3D(sceneMgr, nombreMalla, mask);
}*/



void Ficha::apaga()
{
	seleccionada = false;

							   	std::cout << "APAGA EN ESCENA"<<std::endl;

   // getNodoOgre()->showBoundingBox(true);
 
    if (esNegra)
    {
		//materialName = ("MaterialFichaNegra");
       // cambiaMaterial("MaterialFichaNegraIluminada");
    }
	else{} //cambiaMaterial("MaterialFichaBlancaIluminada"); 
		//materialName = ("MaterialFichaBlanca");

	
}

void Ficha::ilumina()
{
		seleccionada = true;

							   	std::cout << "ILUMINAFICHA EN ESCENA"<<std::endl;

   // getNodoOgre()->showBoundingBox(true);
 
    if (esNegra)
    {
		//materialName = ("MaterialFichaNegraIluminada");
       // cambiaMaterial("MaterialFichaNegraIluminada");
    }
	else {}//cambiaMaterial("MaterialFichaBlancaIluminada"); 
		///materialName = ("MaterialFichaBlancaIluminada");
	
}
