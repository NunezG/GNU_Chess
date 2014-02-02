#ifndef __ObjetoEscena_
#define __ObjetoEscena_
#include <iostream>
#include <vector>
#include <string>
//#include "ObjetoOgre.h"

/*
struct ObjetoEscenaPrueba{
    Ogre::String Tipo;
    Ogre::Entity* entObjetoEscena;
    bool esNegra;
    bool muerta;
    int casilla[2];
};

struct ListaPosiciones{
    ListaPosiciones* anterior;
    int posicion[2];
};
*/


struct posicion{
    int Fila;
    int Columna;

};

#define CASILLA 1 << 0  // Mascara para el escenario
#define NEGRAS 1 << 1  // Mascara para objetos de tipo 1
#define BLANCAS 1 << 2  // Mascara para objetos de tipo 2
#define TABLERO 1 << 3

class ObjetoEscena
{
public:

    ~ObjetoEscena(void);
	       // ObjetoEscena(std::string nombre);

    //constructor de copia
    ObjetoEscena(const ObjetoEscena& ObjetoEscenaOriginal, std::string nombre, int tipo);
    //void creaModelo3D(Ogre::SceneManager* sceneMgr, Ogre::String nombreMalla, Ogre::uint32 mask);
   // int tipo_ObjetoEscena;
    //bool esNegra;
	//bool seleccionada;
    //void apaga();
    ///void ilumina();
	 virtual std::string getNombre();
	virtual ObjetoEscena* getHijo(int numero);
  virtual  ObjetoEscena* getHijo(std::string posicion);
	 std::string nombreMalla;
		std::vector<ObjetoEscena*> vectorHijos;
			int mask;
			int xRel;
			int yRel;
		virtual	void setPosicion(int posFila, int posCol);
    virtual posicion getPosicion();
			posicion posInView;
			int posInModel;

				std::string materialNames[2];

			virtual void creaHijo(std::string name, int mask, std::string mesh, std::string materials[2]) = 0;

				//void creaHijo(std::string nombre);
	virtual void eliminaHijo(int hijo);
    virtual void agregaHijo(ObjetoEscena* objetoHijo);
   virtual bool sinHijos();
		 int rotate;
	ObjetoEscena( std::string nombre, int mascara, std::string meshName, std::string materials[2]);
		std::string nombreObjeto;
		   virtual void cambiaMaterial(int material) = 0;


protected:

private: 
   // virtual bool setCasilla(int fila, int col);
   // bool salto;
  //  bool Selected;
    //PARA EVALUAR:
  //  bool Moved;
 //   short PieceActionValue;
  //  short AttackedValue;
 //   short DefendedValue;
 //   short valorObjetoEscena;
   //  Stack<byte> ValidMoves; // lista de movimientos válidos
   // bool muerta;
    //int casilla[2];


    //ObjetoOgre* objetoOgreAsociado;
};

#endif
