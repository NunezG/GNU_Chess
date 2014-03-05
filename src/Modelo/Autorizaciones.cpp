#include "Autorizaciones.h"


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
int Autorizaciones::autorizaCasilla()
{   

    ModeloTablero* tableroModelo = Modelo::getSingletonPtr()->tableroModelo;

    if (Modelo::getSingletonPtr()->tableroModelo->turnoN)
    {

        //  tableroModelo->jugada[0] = 143-tableroModelo->jugada[0];
        // tableroModelo->jugada[1] = 143-tableroModelo->jugada[1];
    }


    //el tipo es la ficha de casillasint
    int tipoo =  tableroModelo->casillasInt[tableroModelo->jugadaPrincipal[0]];

    if (tipoo<0)tipoo = -tipoo;


    return 0;

}


//return: 1 para autorizado, 2 para no autorizado, 3 para jaque
std::vector<int> Autorizaciones::casillasAutorizadas()
{   

    ModeloTablero* tableroModelo = Modelo::getSingletonPtr()->tableroModelo;

    if (Modelo::getSingletonPtr()->tableroModelo->turnoN)
    {

        //  tableroModelo->jugada[0] = 143-tableroModelo->jugada[0];
        // tableroModelo->jugada[1] = 143-tableroModelo->jugada[1];
    }




    //BUSCA EN EL TABLERO LAS FICHAS Y SEGUN SU TIPO VA GENERANDO LOS MOVIMIENTOS

    bool movimiento = false;
    // Movimientos::generaMovimientos(miTablero);
    

    //el tipo es la ficha de casillasint
    //int tipoo =  tableroModelo->casillasInt[tableroModelo->jugada[0]];

    //if (tipoo<0)tipoo = -tipoo;


    std::cout << "PUEDE MOVER??"<<std::endl;

    bool resus=   Movimientos::movimientosUnaFicha(tableroModelo);
    

    std::cout << "fingeneramov?"<<std::endl;


    std::vector<int> listaJugadas;





    for (std::vector<std::string>::iterator it = tableroModelo->vectorJugadas.begin(); it!=tableroModelo->vectorJugadas.end(); it++)
    {
        std::cout << "for?"<<std::endl;


        std::string jugada = *it;



        //	 for (std::vector<unsigned char*>::iterator itt = jugada.begin(); itt!=jugada.end(); itt++)
        //{
        
        for (int i =0; i<jugada.size(); i = i+2)
        {
            std::cout << "JUGADA RESALTADA? "<<(int)jugada[i+1] <<std::endl;

            //punot inicial
            //jugada[i]

            listaJugadas.push_back((int)jugada[i+1]);

            //punto final


        }
        // unsigned char* mov = *jugada.begin();

        //std::cout << "MOV0? "<<  (int)mov[0]   <<std::endl;

        //	std::cout << "MOV1? "<<  (int)mov[1]   <<std::endl;



        //     ModeloTablero* tablero = Movimientos::aplicaMovimiento(*tableroModelo);

        
        //  delete mov;
        //   mov = NULL;
        
        // }
    }



    // tableroModelo->vectorJugadas.clear();

    std::cout << "BORRA JUGADASSSS?"<<std::endl;

    tableroModelo->borraJugadas();
    std::cout << "RET?"<<std::endl;


    return listaJugadas;



}

bool Autorizaciones::pruebaJaqueMate(ModeloTablero* miTablero)
{    
    //VA GENERANDO LOS MOVIMIENTOS

    bool movimiento = false;

    Movimientos::generaMovimientos(miTablero);
    
    if(miTablero->vectorJugadas.size() > 0)
    {
        movimiento = true;
        

        miTablero->borraJugadas();


        if (movimiento)  return false;
        //else return true;

        return true; //JAQUE MATE O AHOGADO
    }
}
