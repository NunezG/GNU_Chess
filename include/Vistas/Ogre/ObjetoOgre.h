#ifndef __ObjetoOgre_
#define __ObjetoOgre_

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include <OgreEntity.h>
#include <ObjetoEscena.h>

#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3

class ObjetoOgre : public ObjetoEscena
{
public:
    ~ObjetoOgre(void);

    Ogre::SceneNode* getNodoOgre();

    void creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask);
	void eliminaHijo(int hijo);
    void agregaHijo(ObjetoEscena* objetoHijo);
    void creaHijo(std::string name, int mask, std::string mesh, std::vector<std::string> materials);

    void cambiaMaterial(int material);
    void rota(int grados);
    void trasladar(int x, int z);
    ObjetoOgre(std::string name, int mask, std::string mesh, std::vector<std::string> materials, Ogre::SceneManager* sceneMgr);
		

	bool activo;
protected:

private:
    Ogre::uint32 tipoObjeto;

    Ogre::Entity* entidad;
    Ogre::SceneNode* nodoEscena;
    Ogre::SceneManager* mSceneMgr;
		//	std::vector<ObjetoOgre*> vectorHijos;

		//std::string nombreObjeto;

};

#endif
