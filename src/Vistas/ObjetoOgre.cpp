#include "ObjetoOgre.h"


ObjetoOgre::ObjetoOgre(std::string name, int mask, std::string mesh, std::vector<std::string> materials, Ogre::SceneManager* sceneMgr) : ObjetoEscena(name,mask,mesh,materials)
  // ,vectorHijos(0),
  //  nodoEscena(NULL)
  , entidad(NULL)
  , activo(true)
{

    //  //COUTCOMENTADOstd::cout << "crea objetoogree"<<std::endl;

    mSceneMgr = sceneMgr;

    //materials
    creaModelo3D(mSceneMgr, mesh, mask);
    // //COUTCOMENTADOstd::cout << "pe y ja"<<std::endl;

    cambiaMaterial(0);
    //   //COUTCOMENTADOstd::cout << "medio"<<std::endl;


    nombreObjeto = name;
    // //COUTCOMENTADOstd::cout << "objetoogre"<<std::endl;

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


void ObjetoOgre::cambiaMaterial(int material)
{
    ////COUTCOMENTADOstd::cout << "obj: "<<getNombre()<<std::endl;

    //	//COUTCOMENTADOstd::cout << "cambiaMaterial aaaa: "<<material<<std::endl;
    ////COUTCOMENTADOstd::cout << "que es: "<<materialNames[material]<<std::endl;
    if (materialNames.size() > material)
        entidad->setMaterialName(materialNames[material]);
}

void ObjetoOgre::creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask)
{
    // //COUTCOMENTADOstd::cout << "crea modelito"<<std::endl;

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
    //Ogre::SceneNode* mTarget = mSceneMgr->getRootSceneNode();

    // Ogre::Real dist = (nodoEscena->getPosition() - mTarget->_getDerivedPosition()).length();

    //Mueve nodoEscena a la posicion central
    // nodoEscena->setPosition(mTarget->_getDerivedPosition());
    //Rota nodoEscena
    //  nodoEscena->yaw(Ogre::Degree(grados));

    //Devuelve la camara a su posicion original
    //  nodoEscena->translate(Ogre::Vector3(0, 0, dist));



    nodoEscena->yaw(Ogre::Degree(grados));
}



void ObjetoOgre::eliminaHijo(int hijo)
{
    getNodoOgre()->removeChild(hijo);
    // getNodoOgre()->chil
    
    ObjetoEscena::eliminaHijo(hijo);
    //vectorHijos.erase(vectorHijos.begin()+hijo);

}

/*
void ObjetoOgre::cambiaPadre(int hijo)
{
    getNodoOgre()->getParent()->removeChild(getNodoOgre());
   // getNodoOgre()->removeChild(hijo);
    vectorHijos.erase(vectorHijos.begin()+hijo);
}
*/


void ObjetoOgre::agregaHijo(ObjetoEscena* objetoHijo)
{

    //mejor crearlo aqui?

    //  vectorHijos.push_back(objetoHijo);
    ObjetoEscena::agregaHijo(objetoHijo);
    if (nodoEscena != NULL) nodoEscena->addChild(static_cast<ObjetoOgre*>(objetoHijo)->getNodoOgre());

}

void ObjetoOgre::creaHijo(std::string name, int mask, std::string mesh, std::vector<std::string> materials)
{
    //mejor crearlo aqui?
    //ObjetoEscena::creaHijo(name, mask, mesh, material);

    ObjetoOgre*	objeto = new ObjetoOgre(name, mask, mesh, materials, mSceneMgr);



    agregaHijo(objeto);


}

Ogre::SceneNode* ObjetoOgre::getNodoOgre()
{
    return nodoEscena;
}
