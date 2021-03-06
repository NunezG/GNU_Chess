#include "VistaAjedrezSolo.h"

//-------------------------------------------------------------------------------------
VistaAjedrezSolo::VistaAjedrezSolo(OgreFramework* fw)
    : VistaAjedrez(fw)

{
}

VistaAjedrezSolo::~VistaAjedrezSolo(void)
{    

}



#if (OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS) && (OGRE_PLATFORM != OGRE_PLATFORM_ANDROID)

bool VistaAjedrezSolo::mouseMoved( const OIS::MouseEvent &arg )
{
    // Jugador* jug = modelo->jugadores.at(escenaAjedrez->getTablero()->getTurnoNegras());

    //  if(jug->esHumano())
    return VistaAjedrez::mouseMoved( arg );
    //else mInputMan->injectMouseMove(arg);
}

bool VistaAjedrezSolo::mousePressed( const OIS::MouseEvent &arg,OIS::MouseButtonID id )
{

    // Jugador* jug = modelo->jugadores.at(escenaAjedrez->getTablero()->getTurnoNegras());

    //  if(jug->esHumano())
    return VistaAjedrez::mousePressed(arg, id);
    //else mInputMan->injectMouseDown(arg, id);

}

bool VistaAjedrezSolo::mouseReleased( const OIS::MouseEvent &arg,OIS::MouseButtonID id )
{
    //   Jugador* jug = modelo->jugadores.at(escenaAjedrez->getTablero()->getTurnoNegras());

    //  if(jug->esHumano())
    return VistaAjedrez::mouseReleased(arg,  id );
    //  else{
    //  mInputMan->injectMouseUp(arg, id);
    // calculaMovimiento();
    //    }
}



//NO SIRVE PARA NADA PERO SE PUEDE USAR PARA MOSTRAR OTROS MENUS

//-------------------------------------------------------------------------------------
bool VistaAjedrezSolo::keyPressed( const OIS::KeyEvent &arg )
{
    return VistaAjedrez::keyPressed( arg );
}

bool VistaAjedrezSolo::keyReleased( const OIS::KeyEvent &arg )
{ 
    return VistaAjedrez::keyReleased( arg );
}


#endif


//bool VistaAjedrezSolo::frameRenderingQueued(const Ogre::FrameEvent& evt)
//{
// return VistaAjedrez::frameRenderingQueued(evt);

/*  if (!FrameListeners::frameRenderingQueued(evt)) return false;
    else if(escenaAjedrez->tablero->rotacionCamara != Ogre::Degree(0))
    {
        mueveCamara(evt.timeSinceLastFrame);

    }*/

//}

//-------------------------------------------------------------------------------------
//bool VistaAjedrezSolo::frameRenderingQueued(float frecuencia)
//{
// if(modelo->getTablero()->getTurnoNegras())rotaTurno = Ogre::Real(0.0f);
//return VistaAjedrez::mueveCamara(frecuencia);
//  return true;
//}




