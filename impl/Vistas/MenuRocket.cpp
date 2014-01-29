#include "../../headers/Vistas/MenuRocket.h"

//-------------------------------------------------------------------------------------
MenuRocket::MenuRocket(ModeloVista* modeloV, Ogre::RenderWindow* mWindow) : BaseVistas(modeloV, mWindow)
   //  ,ventanaConfig(NULL),
  //  listaResoluciones(NULL)
{
				    std::cout << "menuuu "<<std::endl;

	pantallaInicio();




}

MenuRocket::~MenuRocket(void)
{
    //¿¿¿BORRA MEJOR CON EL PUNTERO ventanaEmergente???

          //CEGUI::Window*CEGUI = CEGUI::WindowManager::getSingleton();
 /*    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuRocket")->getChild("VentanaMenu")->hide();
	    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuRocket")->getChild("VentanaMenu")->hide();

      CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuRocket")->hide();
      CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("MenuRocket")->destroyChild("VentanaMenu");
      CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->destroyChild("MenuRocket");
	  */
}



bool MenuRocket::pantallaInicio()
{
    //CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->layou
/*
    CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuRocketAjedrezCEED.layout");
    //ENLAZA LOS BOTONES
    newWindow->getChild("VentanaMenu")->getChild("Salir")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuRocket::botonSalir, this));
    newWindow->getChild("VentanaMenu")->getChild("Salir")->setMouseCursor("Vanilla-Images/MouseArrow");
	newWindow->getChild("VentanaMenu")->getChild("UnJugador")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuRocket::botonJuegoSolo, this));
    newWindow->getChild("VentanaMenu")->getChild("UnJugador")->setMouseCursor("Vanilla-Images/MouseArrow");
	newWindow->getChild("VentanaMenu")->getChild("DosJugadores")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuRocket::botonJuegoTurnos, this));
   newWindow->getChild("VentanaMenu")->getChild("DosJugadores")->setMouseCursor("Vanilla-Images/MouseArrow");
	newWindow->getChild("VentanaMenu")->getChild("Configura")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuRocket::botonConfig, this));
	   newWindow->getChild("VentanaMenu")->getChild("Configura")->setMouseCursor("Vanilla-Images/MouseArrow");


    newWindow->getChild("VentanaMenu")->setMouseCursor("Vanilla-Images/MouseArrow");
     newWindow->setMouseCursor("Vanilla-Images/MouseArrow");

    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(newWindow);
	*/
    return true;
}
/*

bool MenuRocket::botonSalir(const CEGUI::EventArgs &e)
{
    modeloVista->setApagar(true);
    mWindow->setHidden(true);
    return true;
}

bool MenuRocket::botonJuegoTurnos(const CEGUI::EventArgs &e)
{
    modeloVista->setNumPantalla(1);
  //  mWindow->setVisible(false);
		mWindow->update();
	mWindow->setHidden(true);

    //modoJuego = 1;
    return true;
}

bool MenuRocket::botonJuegoSolo(const CEGUI::EventArgs &e)
{
    modeloVista->setNumPantalla(2);
    mWindow->setHidden(true);

    return true;
}

bool MenuRocket::botonConfig(const CEGUI::EventArgs &e)
{
	  if (ventanaConfig != NULL)
    {
        ventanaConfig->show();
        ventanaConfig->activate();
    }
    else
    pantallaConfig();

    return true;
}

bool MenuRocket::botonVolver(const CEGUI::EventArgs &e)
{

	pantallaCompleta->setSelected(modeloVista->pantallaCompleta);


    ventanaConfig->hide();
    return true;
}

bool MenuRocket::botonAplicarCambios(const CEGUI::EventArgs &e)
{
	CEGUI::ListboxItem* item;    	
		item =  listaResoluciones->getFirstSelectedItem();

		if(item!= NULL)
		{
            modeloVista->resolucion = item->getText().c_str();
		}
    
	 modeloVista->pantallaCompleta = pantallaCompleta->isSelected();

    item =  listaDificultades->getFirstSelectedItem();
     if(item!= NULL)
     {
             modeloVista->dificultad = item->getID();
     }

	 	 modeloVista->nombres[0] = ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("EditBlancas")->getText().c_str();
	 modeloVista->nombres[1] = ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("EditNegras")->getText().c_str();

    ventanaConfig->hide();
    mWindow->setHidden(true);

    return true;
}


bool MenuRocket::sobrevuelaListaResoluciones(const CEGUI::EventArgs &e)
{
    return sobrevuelaLista(listaResoluciones);
}

bool MenuRocket::sobrevuelaListaDificultad(const CEGUI::EventArgs &e)
{
    return sobrevuelaLista(listaDificultades);
}

bool MenuRocket::seleccionaResolucion(const CEGUI::EventArgs &e)
{
    return seleccionaElementoLista(listaResoluciones);
    return true;
}

bool MenuRocket::seleccionaDificultad(const CEGUI::EventArgs &e)
{
    return seleccionaElementoLista(listaDificultades);
}

bool MenuRocket::sobrevuelaLista(CEGUI::Listbox *lista)
{
    // Reset all list items to undetected colour
    for(int i=0; i<lista->getItemCount(); i++)
    {
        CEGUI::ListboxTextItem* item = static_cast<CEGUI::ListboxTextItem*>(lista->getListboxItemFromIndex(i));

        // If the item is selected then it maintains its selected colour
        if(!item->isSelected())
        {
            item->setTextColours(CEGUI::Colour(1.0, 1.0, 1.0, 1.0));
        }
    }
    //  listaResoluciones->handleUpdatedItemData();

    CEGUI::Window &win = *ventanaConfig;
    CEGUI::Vector2<float> mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
    CEGUI::Vector2<float> mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                    CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));

    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(lista->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem )
    {
        detectedItem->setTextColours(CEGUI::Colour(0.0, 1.0, 0.0, 0.8));
    }

    lista->handleUpdatedItemData();

    return true;
}

bool MenuRocket::seleccionaElementoLista(CEGUI::Listbox *lista)
{

    CEGUI::Window &win = *ventanaConfig;

    CEGUI::Vector2<float>   mousePos = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
       CEGUI::Vector2<float> mousePosLocal(CEGUI::CoordConverter::screenToWindowX(win,mousePos.d_x),
                                    CEGUI::CoordConverter::screenToWindowY(win,mousePos.d_y));
    CEGUI::ListboxTextItem* detectedItem = static_cast<CEGUI::ListboxTextItem*>(lista->getItemAtPoint(mousePosLocal));

    // The colour is updated only if the detected item is not selected
    if(detectedItem )
    {
        detectedItem->setSelected(true);
    }

//    lista->handleUpdatedItemData();

	sobrevuelaLista(lista);

    return true;
}

void MenuRocket::creaMenuDesplegable(CEGUI::Event::Subscriber eventoAlSobrevolar,CEGUI::Event::Subscriber eventoAlPulsar, std::vector<std::string> listaElementos, CEGUI::Listbox* lista, std::string preSeleccionado)
{
    CEGUI::Colour col;

    col.setBlue(100.0f);
    col.setGreen(50.0f);
    col.setRed(50.0f);
    col.setAlpha(50.0f);

    CEGUI::ListboxTextItem* elementoLista;

    for (int i = 0; i < listaElementos.size(); i++)
    {
        std::string texto = listaElementos.at(i);
        elementoLista= new CEGUI::ListboxTextItem(texto);

        //elementoLista->setSelectionColours(col );

        if (texto == preSeleccionado)
        {
            elementoLista->setTextColours(CEGUI::Colour(0.0, 1.0, 0.0, 1.0));
            elementoLista->setSelected(true);
        }

        elementoLista->setID(i);
        lista->addItem(elementoLista);
        lista->handleUpdatedItemData();
    }


    lista->subscribeEvent(CEGUI::Listbox::EventMouseMove, eventoAlSobrevolar);
    lista->subscribeEvent(CEGUI::Listbox::EventMouseClick, eventoAlPulsar);

    lista->handleUpdatedItemData();

    //return listaReal;
}

*/
bool MenuRocket::pantallaConfig()
{
  
     /*    ventanaConfig = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ConfiguraAjedrezCEED.layout");
		ventanaConfig->setMouseCursor("Vanilla-Images/MouseArrow");
		//ventanaConfig->getChild("VentanaConf")->getChild("BotonAceptar")->setMouseCursor("Vanilla-Images/MouseArrow");
	    ventanaConfig->getChild("VentanaConf")->setMouseCursor("Vanilla-Images/MouseArrow");


        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(ventanaConfig);
      
		pantallaCompleta = static_cast<CEGUI::ToggleButton*>(ventanaConfig->getChild("VentanaConf")->getChild("CheckPantallaC"));
		pantallaCompleta->setMouseCursor("Vanilla-Images/MouseArrow");
		if (modeloVista->pantallaCompleta) pantallaCompleta->setSelected(true);


		listaResoluciones = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("ListaResol"));
      	listaResoluciones->setMouseCursor("Vanilla-Images/MouseArrow");

		listaDificultades = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("ListaDific"));
        listaDificultades->setMouseCursor("Vanilla-Images/MouseArrow");
		
	//	listaBlancas = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("ListaJugadorBlancas"));

		//   listaBlancas = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("ListaJugadorBlancas"));
      //  listaNegras = static_cast<CEGUI::Listbox*>(ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("ListaJugadorNegras"));
        ventanaConfig->getChild("VentanaConf")->getChild("BotonAceptar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuRocket::botonAplicarCambios, this));
          ventanaConfig->getChild("VentanaConf")->getChild("BotonAceptar")->setMouseCursor("Vanilla-Images/MouseArrow");

		ventanaConfig->getChild("VentanaConf")->getChild("BotonCancelar")->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuRocket::botonVolver, this));
        ventanaConfig->getChild("VentanaConf")->getChild("BotonCancelar")->setMouseCursor("Vanilla-Images/MouseArrow");
		ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->setMouseCursor("Vanilla-Images/MouseArrow");
		ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("EditBlancas")->setMouseCursor("Vanilla-Images/MouseArrow");
			ventanaConfig->getChild("VentanaConf")->getChild("Jugadores")->getChild("EditNegras")->setMouseCursor("Vanilla-Images/MouseArrow");
	
    std::vector<std::string>  listaElementos;

    listaElementos.push_back(std::string("640 x 480"));
    listaElementos.push_back(std::string("800 x 600"));
    listaElementos.push_back(std::string("1024 x 768"));
    listaElementos.push_back(std::string("1280 x 1024"));
	listaElementos.push_back(std::string("1400 x 1050"));
	listaElementos.push_back(std::string("1440 x 900"));
	listaElementos.push_back(std::string("1680 x 1050"));
	listaElementos.push_back(std::string("1920 x 1080"));
    creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuRocket::sobrevuelaListaResoluciones, this), CEGUI::Event::Subscriber(&MenuRocket::seleccionaResolucion, this), listaElementos ,listaResoluciones, modeloVista->resolucion);

    listaElementos.clear();
    listaElementos.push_back(std::string("Easy"));
    listaElementos.push_back(std::string("Middle"));
    listaElementos.push_back(std::string("Hard"));
    creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuRocket::sobrevuelaListaDificultad, this), CEGUI::Event::Subscriber(&MenuRocket::seleccionaDificultad, this), listaElementos ,listaDificultades, listaElementos.at(modeloVista->dificultad) );

  //  listaElementos.clear();
  //  listaElementos.push_back(std::string("Humano"));
   // listaElementos.push_back(std::string("Maquina"));
  //  creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuRocket::sobrevuelaListaBlancas, this),CEGUI::Event::Subscriber(&MenuRocket::seleccionaBlancas, this), listaElementos ,listaBlancas, listaElementos.at(0));
   // creaMenuDesplegable(CEGUI::Event::Subscriber(&MenuRocket::sobrevuelaListaNegras, this), CEGUI::Event::Subscriber(&MenuRocket::seleccionaNegras, this), listaElementos ,listaNegras, listaElementos.at(0));
   */
    return true;
}