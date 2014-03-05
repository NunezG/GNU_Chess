#include "../../include/ModeloVista/ObjetoEscena.h"


ObjetoEscena::ObjetoEscena(std::string nombre, int mascara, std::string meshName, std::vector<std::string> materials) :
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

    materialNames = materials;
    //  materialNames[1] = materials[1];
    // materialNames[2] = materials[2];
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


int ObjetoEscena::numHijos()
{
    if (vectorHijos.empty()) return 0;
    else return vectorHijos.size();
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

            return obj;
        }
    }

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
