#include "../../headers/ModeloVista/ObjetoOgre.h"


ObjetoOgre::ObjetoOgre(std::string nombre) :
    vectorHijos(0),
    nodoEscena(NULL)
  , entidad(NULL)
{
    nombreObjeto = nombre;
}

ObjetoOgre::~ObjetoOgre()
{
    if (nodoEscena)
    {
        nodoEscena->detachAllObjects();

        for(int i = 0; i < vectorHijos.size(); i++)
        {
            delete vectorHijos.at(i);
            vectorHijos.at(i) = NULL;
        }
        vectorHijos.clear();
        nodoEscena->removeAndDestroyAllChildren();
        mSceneMgr->destroySceneNode(nodoEscena);

        delete entidad;
        nodoEscena = NULL;
    }
}

std::string ObjetoOgre::getNombre()
{
    return nombreObjeto;
}

void ObjetoOgre::cambiaMaterial(std::string material)
{
    entidad->setMaterialName(material);
}

void ObjetoOgre::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{
    //  entidad = mSceneMgr->createEntity("test12", "Tablero.mesh");
    mSceneMgr = sceneMgr;
    nodoEscena = mSceneMgr->createSceneNode(nombreObjeto);

    nombreMalla.append(".mesh");

    entidad = mSceneMgr->createEntity(nombreObjeto, nombreMalla);
    nodoEscena->attachObject(entidad);
    entidad->setQueryFlags(mask);
}

void ObjetoOgre::trasladar(int x, int z)
{
    nodoEscena->translate(x,0,z);
}

void ObjetoOgre::rota(int grados)
{
    nodoEscena->yaw(Ogre::Degree(grados));
}

ObjetoOgre* ObjetoOgre::getHijo(int numero)
{
    return vectorHijos.at(numero);
}

ObjetoOgre* ObjetoOgre::getHijo(std::string posicion)
{
    for (int i = 0; i< vectorHijos.size(); i++)
    {
        ObjetoOgre* obj = vectorHijos[i];
        if (obj->getNombre() == posicion)
        {
            return obj;
        }
    }
    return NULL;
}

void ObjetoOgre::eliminaHijo(int hijo)
{
    getNodoOgre()->removeChild(hijo);
    vectorHijos.erase(vectorHijos.begin()+hijo);
}


bool ObjetoOgre::sinHijos()
{
    return  vectorHijos.empty();
}

void ObjetoOgre::agregaHijo(ObjetoOgre* objetoHijo)
{
    vectorHijos.push_back(objetoHijo);
    if (nodoEscena != NULL) nodoEscena->addChild(objetoHijo->getNodoOgre());
}

Ogre::SceneNode* ObjetoOgre::getNodoOgre()
{
    return nodoEscena;
}
