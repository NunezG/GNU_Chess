#include "../../headers/ModeloVista/ObjetoEscena.h"


ObjetoEscena::ObjetoEscena(std::string nombre, int mascara, std::string meshName, std::string materials[2]) :
   // esNegra(0),
    //muerta(0),
  //  tipo_ObjetoEscena(tipo),
	//seleccionada(0)
   // salto(false)
     nombreMalla(meshName)
	, nombreObjeto(nombre)
	, mask(mascara)
	
	, rotate(0)
{
											    std::cout << "crea ObjetoEscena"<<std::endl;

   materialNames[0] = materials[0];
      materialNames[1] = materials[1];

}

ObjetoEscena::~ObjetoEscena()
{
}

ObjetoEscena::ObjetoEscena( const ObjetoEscena& ObjetoEscenaOriginal, std::string nombre, int tipo )
   // esNegra(ObjetoEscenaOriginal.esNegra),
   // muerta(0),
   // tipo_ObjetoEscena(tipo),
	//seleccionada(0)
   // ObjetoOgre(nombre)
   // salto(false)
  //  tipo_ObjetoEscena = ObjetoEscenaOriginal
{
}

/*void ObjetoEscena::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{
    if (mask == NEGRAS) esNegra = true;
    else if (mask == BLANCAS )esNegra = false;

   ObjetoOgre::creaModelo3D(sceneMgr, nombreMalla, mask);
}*/

void ObjetoEscena::eliminaHijo(int hijo)
{
    //getNodoOgre()->removeChild(hijo);
    vectorHijos.erase(vectorHijos.begin()+hijo);
}


bool ObjetoEscena::sinHijos()
{
    return  vectorHijos.empty();
}

void ObjetoEscena::agregaHijo(ObjetoEscena* objetoHijo)
{
    vectorHijos.push_back(objetoHijo);
    //if (nodoEscena != NULL) nodoEscena->addChild(objetoHijo->getNodoOgre());
}



std::string ObjetoEscena::getNombre()
{
    return nombreObjeto;
}


ObjetoEscena* ObjetoEscena::getHijo(int numero)
{
    return vectorHijos.at(numero);
}

ObjetoEscena* ObjetoEscena::getHijo(std::string posicion)
{
    for (int i = 0; i< vectorHijos.size(); i++)
    {
        ObjetoEscena* obj = vectorHijos[i];
        if (posicion.compare(obj->nombreObjeto) == 0)
      {
		  	std::cout << "ObjetoEscena::getHijo con no mbre: "<<std::endl;
					  	std::cout <<obj->getNombre()<<std::endl;

          return obj;
        }
    }
			  	std::cout << "no encuentra hijo con nombre: "<< posicion.c_str()<<std::endl;

    return NULL;
}


posicion ObjetoEscena::getPosicion()
{
    return posInView;
}

void ObjetoEscena::setPosicion(int posFila, int posCol)
{
    posInView.Fila = posFila;
    posInView.Columna = posCol;
}