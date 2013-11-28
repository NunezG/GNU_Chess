#ifndef __Tablero_
#define __Tablero_

#include <vector>
#include <string>
#include <iostream>

#include "FichaAlfil.h"
#include "FichaCaballo.h"
#include "FichaTorre.h"
#include "FichaReina.h"
#include "FichaRey.h"
#include "FichaPeon.h"
#include "Casilla.h"

enum enColummas{
    COL_A,
    COL_B,
    COL_C,
    COL_D,
    COL_E,
    COL_F,
    COL_G,
    COL_H

};

// ESTE SERÁ EL NODO USADO EN LOS ÁRBOLES
class Tablero: public ObjetoOgre
{
public:
    ~Tablero(void);
    Tablero(void);

    int getAlPaso();
    void setAlPaso(int casilla);
    Casilla* getCasillaSeleccionada();
    Casilla* getCasillaSobrevolada();
    void setCasillaSeleccionada(Casilla* nodo);
    void setCasillaSobrevolada(Casilla* nodo);
    void setCasillaSeleccionada(int posicion);
    void setCasillaSobrevolada(int posicion);
    bool getTurnoNegras();
    void creaTableroYCasillas(Ogre::SceneManager* sceneMgr);
    void actualizaTablero(Ogre::SceneManager* manager);

    bool fichaSeleccionada;
    Ogre::Degree rotacionCamara;
    int peonesPromocionados;

private:
    void creaCasillas();
    void creaPeones();
    void creaNobleza();
    void creaVasallos();

    bool turnoNegras;
    Ogre::SceneManager* mSceneMgr;
    int alPaso;
    Casilla* casillaSeleccionada;
    Casilla* casillaSobrevolada;
};

#endif
