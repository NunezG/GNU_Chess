
  #set(CMAKE_TOOLCHAIN_FILE "D:/ogreHG/CMake/toolchain/android.toolchain.cmake")
 
 # message("CMAKE_TOOLCHAIN_FILE")
  # message(${CMAKE_TOOLCHAIN_FILE})
  			 
	  #	 set(OGRE_STATIC_GL 1)

cmake_minimum_required(VERSION 2.6)
 

if(WIN32)
project(OgreApp)
endif()
 #set(BUILD_STATIC_LIBRARY 1)
 
 	set(OGRE_STATIC 1)
		  		set(OGRE_STATIC_LIB 1)
		set(STATIC_LIB 1)
 
set (ANDROID_NDK "C:/Android/ndk")



 #Reemplaza los flags dinamicos por estaticos
 set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()



#set (FREETYPE_LIBRARY "F:/ogreHG/buildWindows/sdk/lib/freetype.lib")


if(WIN32) # EN WINDOWS COGE LOS FIND*** DEL DIRECTORIO DONDE ESTA OGRESDK
	#set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)
 
if(UNIX) # EN LINUX HAY QUE BUSCAR LOS FIND*** SI SE HACE INSTALACION MANUAL
	message("TESTUNIX.")
		 set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/")

	if(ANDROID)
	
	
	
	
	#set(ANDROID_FORCE_ARM_BUILD TRUE)

	
	message("ENTRA EN ANDROIDIDDII")
	else()

#	if(EXISTS "/usr/local/lib/OGRE/cmake")
#message("PRIMER IFF.")
#	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
#	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local
#	elseif(EXISTS "/usr/share/OGRE/cmake/modules")
#message("SEGUNDO IFF.")
#	  set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules/;${CMAKE_MODULE_PATH}")
 #         set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/include/OGRE/") # Otherwise, this one
#	else ()
#	  message("Failed to find module path. SETTING source dir CMake")
	#message(${CMAKE_CURRENT_SOURCE_DIR})
	#message(${CMAKE_MODULE_PATH})
	#  message("path")
	#message(${CMAKE_MODULE_PATH})
#    endif()
	

	endif(ANDROID)
endif(UNIX)
 
#if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
#endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
  

set(ZZIP_HOME ${OGRE_HOME})


message("INICIA FINDOGRE.")
 find_package(OGRE REQUIRED)
message("ACABA FINDOGRE.") 

#if(NOT "${OGRE_VERSION_NAME}" STREQUAL "Cthugha")
 # message(SEND_ERROR "You need Ogre 1.7 Cthugha to build this.")
#endif()
 
 find_package(OIS REQUIRED)
 
  find_package(DirectX REQUIRED)

 
 if(NOT OIS_FOUND)
	 message(SEND_ERROR "Failed to find OIS.")
 endif()
 
  message(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
 
 if(WIN32)
 
 #Find Boost
#if (OGRE_BUILD_PLATFORM_IPHONE)

set(Boost_INCLUDE_DIR $ENV{BOOST_ROOT})

	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.57" "1.57.0" "1.54" "1.54.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS system thread date_time regex chrono)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)
 

 message("PASA POR INCLUDE BOOST")
	# Set up referencing of Boost
	 message(${Boost_INCLUDE_DIR})

	 
	 
	include_directories(${Boost_INCLUDE_DIRS})
	#add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_THREAD_LIBRARY_RELEASE} ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_DATE_TIME_LIBRARY_RELEASE} ${Boost_CHRONO_LIBRARY_RELEASE})




###################################################

#set( Boost_USE_STATIC_RUNTIME OFF )
#set( Boost_USE_STATIC_LIBS OFF )
#set( Boost_DEBUG ON )
#find_package( Boost 1.54.0 )
#find_package( Boost COMPONENTS system REQUIRED )

 include_directories( ${Boost_INCLUDE_DIR} )
#target_link_libraries( ${APP_NAME} ${Boost_LIBRARIES} )
##################################################
endif()


if(WIN32)
# "opengl32.lib" "glu32.lib" "dxguid.lib"
set(OGRE_LIBRARIES ${OGRE_LIBRARIES} "dinput8.lib")
endif()


#APPLE
#set(NUEVASLIBS ${OTHER_LIBS_FOR_YOUR_PROJ})

#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   # Mac OS X specific code
#   set(OSX TRUE)
#endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#if(OSX)
if(APPLE)
        find_library(COCOA_LIB Cocoa)
        find_library(IOKIT_LIB IOKit)
        find_library(CARBON_LIB Carbon)
        find_library(COREGRAPHICS_LIB CoreGraphics)
        find_library(FOUNDATION_LIB Foundation)
		
		
		
        set(NUEVASLIBS ${NUEVASLIBS} ${COCOA_LIB} ${IOKIT_LIB} ${CARBON_LIB} ${FOUNDATION_LIB} ${COREGRAPHICS_LIB})
endif()







 
# NUEVA SECCIÓN

message("INICIA RAKNET.")
find_package(RAKNET REQUIRED)
if(NOT RAKNET_FOUND)
	message("Failed to find RAKNET.")
endif()

message("INICIA LIBROCKET.")
find_package(LIBROCKET REQUIRED)
if(NOT LIBROCKET_FOUND)
	message("Failed to find LIBROCKET.")
endif()
# FIN NUEVA SECCIÓN


set(HDRMODEL



       ./include/Modelo/Autorizaciones.h
        ./include/Modelo/Movimientos.h
        ./include/Modelo/Modelo.h
        ./include/Modelo/ModeloTablero.h
        ./include/Modelo/ArbolBusqueda.h
 ./include/Modelo/Jugador.h
        ./include/Modelo/JugadorHumano.h
        ./include/Modelo/JugadorArtificial.h

)


set(HDRVIEWMODEL
        ./include/ModeloVista/EscenaAjedrez.h
        ./include/ModeloVista/ModeloVista.h
       
                ./include/ModeloVista/TableroMV.h
                ./include/ModeloVista/ObjetoEscena.h



)

set(HDRVIEW

        ./include/Vistas/Ventana.h
        ./include/Vistas/VistaAjedrez.h
        #   ./include/Vistas/VistaAjedrezSolo.h
        ./include/Vistas/MenuRocket.h
		./include/Vistas/Escena.h

                 ./include/Vistas/UI/RocketFrameListener.h
                 ./include/Vistas/UI/RenderInterfaceOgre3D.h
				                  ./include/Vistas/UI/RenderInterfaceOgreDirectX.h
                ./include/Vistas/UI/SystemInterfaceOgre3D.h
                ./include/Vistas/UI/RocketEventListener.h



			./include/Vistas/Ogre/OgreFramework.h
			./include/Vistas/Ogre/ObjetoOgre.h
			./include/Vistas/Ogre/FrameListeners.h


			#  ./include/Vistas/MenuInicio.h
			#	./include/Vistas/Ogre/OgreStaticPluginLoader.h
			#	./include/Vistas/Tablero.h
			#./include/Vistas/UI/RocketApplication.h




)




set(SRCMODEL
       ./src/Modelo/Autorizaciones.cpp
       ./src/Modelo/Movimientos.cpp
        ./src/Modelo/Modelo.cpp
        ./src/Modelo/ModeloTablero.cpp
       ./src/Modelo/ArbolBusqueda.cpp
	      ./src/Modelo/Jugador.cpp
      ./src/Modelo/JugadorHumano.cpp
       ./src/Modelo/JugadorArtificial.cpp
)

set(SRCMODELVIEW
        ./src/ModeloVista/EscenaAjedrez.cpp
        ./src/ModeloVista/ModeloVista.cpp
    
           ./src/ModeloVista/TableroMV.cpp
         ./src/ModeloVista/ObjetoEscena.cpp

)
 
set(SRCVIEW
        ./src/Vistas/VistaAjedrez.cpp
      #     ./src/Vistas/VistaAjedrezSolo.cpp
        ./src/Vistas/Ventana.cpp
        ./src/Vistas/MenuRocket.cpp
		./src/Vistas/Escena.cpp

                ./src/Vistas/UI/RocketFrameListener.cpp
                ./src/Vistas/UI/RenderInterfaceOgre3D.cpp
				./src/Vistas/UI/RenderInterfaceOgreDirectX.cpp

                ./src/Vistas/UI/SystemInterfaceOgre3D.cpp
				./src/Vistas/UI/RocketEventListener.cpp



		./src/Vistas/Ogre/FrameListeners.cpp
		./src/Vistas/Ogre/OgreFramework.cpp
		./src/Vistas/Ogre/ObjetoOgre.cpp

)


set(SRCSAPP

./src/Inicio.cpp
./include/AndroidListener.h
./include/AndroidFileInterface.h
   #CONTROL
       # ./src/Control/Inicio.cpp


      #  ./src/Control/ControlJuego.cpp

        # VISTA
       # ./src/BaseOgre.cpp



       # ./src/CreacionJuego.cpp
       # ./src/MenuInicial.cpp

        # implementaciones de modelo

         #  MODELO
  #     ./src/Modelo/Calculos.cpp


      #    ./src/Modelo/ModuloIA.cpp

        # MODELOVISTA
        #./src/ModeloVista/FichaRey.cpp
        #./src/ModeloVista/FichaReina.cpp
    #    ./src/ModeloVista/FichaPeon.cpp
      #  ./src/ModeloVista/FichaAlfil.cpp
    #    ./src/ModeloVista/FichaCaballo.cpp
     #   ./src/ModeloVista/FichaTorre.cpp
     #   ./src/ModeloVista/Ficha.cpp
      #  ./src/ModeloVista/Casilla.cpp


     #  ./src/Modelo/ModeloMenu.cpp
)
  
 # set(OGRE_INCLUDE_DIR ${OGRE_INCLUDE_DIR} $ENV{DXSDK_DIR}include)
 # set(OGRE_LIBRARY_DIRS ${OGRE_LIBRARY_DIRS} $ENV{DXSDK_DIR}Lib\\x86)
 
 
 if(ANDROID)
 set(ANDROID_NATIVE_APP_GLUE_DIR "$ENV{ANDROID_NDK}/sources/android/native_app_glue")
        message("ANDROID_NATIVE_APP_GLUE_DIR")
        message(${ANDROID_NATIVE_APP_GLUE_DIR})
endif()
        message("CMAKE_CURRENT_SOURCE_DIR")


        message(${CMAKE_CURRENT_SOURCE_DIR})




include_directories( 
            
    ${ANDROID_NATIVE_APP_GLUE_DIR}
    ${OIS_INCLUDE_DIR}
	${OGRE_INCLUDE_DIR}
	${DirectX9_INCLUDE_DIR}
	#${OGRE_SAMPLES_INCLUDEPATH}
	#NUEVA SECCIÓN

#${BOOST_INCLUDE_DIR} 
	${LIBROCKET_INCLUDE_DIR}
	${RAKNET_INCLUDE_DIR}
	# FIN NUEVA SECCIÓN
)
 
 
  link_directories( 
     "F:/PFC/proyectoGITWINDOWSBuild/Release"
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/armeabi-v7a
  ${ANDROID_NATIVE_APP_GLUE_DIR} 
  ${OGRE_LIBRARY_DIRS} 
  ${OIS_LIBRARY_DIRS} 

   ${RAKNET_LIBRARY_DIRS}
 ${LIBROCKET_LIBRARY_DIRS} 
  )
 


  
   
   add_library(ChessModel STATIC ${HDRMODEL} ${SRCMODEL})
 
    message("testFIND")
	 message(ChessModel)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Modelo)


	# searching for include directory
find_path(CHESSMODEL_INCLUDE_DIR Modelo.h)

# searching for library file
find_library(CHESSMODEL_LIBRARY ChessModel)



if (CHESSMODEL_LIBRARY)

 message("SOLO LIBRERIA ENCONTRADA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

endif()



if (CHESSMODEL_INCLUDE_DIR)

 message("SOLO INCLUDE ENCONTRADO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

endif()

if (CHESSMODEL_INCLUDE_DIR AND CHESSMODEL_LIBRARY)
 message("LIBRERIA ENCONTRADA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
  message(${CHESSMODEL_INCLUDE_DIR})
  message(${CHESSMODEL_LIBRARY})
    # you may need that if further action in your CMakeLists.txt depends
    # on detecting your library
    set(CHESSMODEL_FOUND TRUE)

    # you may need that if you want to conditionally compile some parts
    # of your code depending on library availability
   # add_definitions(-DHAVE_LIBCHESSMODEL=1)

    # those two, you really need
    include_directories(${CHESSMODEL_INCLUDE_DIR})
    set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${CHESSMODEL_LIBRARY})
endif ()


#target_link_libraries(ChessViewModel ${YOUR_LIBRARIES})










	  
   add_library(ChessViewModel STATIC ${HDRVIEWMODEL} ${SRCMODELVIEW}) 
  

    #    add_dependencies(ChessViewModel ChessModel)
  # target_link_libraries(ChessViewModel ChessModel)

   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ModeloVista)



  add_library(ChessView STATIC ${HDRVIEW} ${SRCVIEW})
 #	add_dependencies(ChessView ChessViewModel)

 #target_link_libraries(ChessView ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})
 
   # target_link_libraries(ChessView ChessViewModel)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Vistas)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Vistas/UI)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Vistas/Ogre)

       # add_dependencies(ChessView ChessViewModel ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})
      #  add_dependencies(ChessView Plugin_OctreeSceneManager)
       # add_dependencies(ChessView Plugin_OctreeSceneManager)

       # add_dependencies(ChessView android c m dl log EGL GLESv2)



        #add_dependencies(ChessDummy OgreApp)


 #	add_dependencies(ChessView OGRE OIS LIBROCKET)



 if(ANDROID)
 
    add_library(OgreApp STATIC ${SRCSAPP} )



    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

  #  target_link_libraries(OgreApp ChessView)
#	add_dependencies(OgreApp ChessView)
    set_target_properties(OgreApp PROPERTIES DEBUG_POSTFIX _d)


 else()
    add_executable(OgreApp WIN32  ${SRCSAPP})

    target_link_libraries(OgreApp ChessView ChessViewModel ChessModel ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES} ${RAKNET_LIBRARIES} ${DirectX9_LIBRARIES})


    add_dependencies(OgreApp ChessView)

    set_target_properties(OgreApp PROPERTIES DEBUG_POSTFIX _d)


  endif()

# CAMBIA target_link_libraries(OgreApp ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
 #target_link_libraries(OgreApp ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})





  link_directories( 
     "F:/PFC/proyectoGITWINDOWSBuild/Release"
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/armeabi-v7a
  ${ANDROID_NATIVE_APP_GLUE_DIR} 
  ${OGRE_LIBRARY_DIRS} 
  ${OIS_LIBRARY_DIRS} 

  ${RAKNET_LIBRARY_DIRS} 
 ${LIBROCKET_LIBRARY_DIRS} 
  )









 
  #Add android JNI binding
if(ANDROID)
  include(toolchain/AndroidJNI)
endif()
  

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)
 
# post-build copy for win32
if(WIN32 AND NOT MINGW)
        add_custom_command( TARGET OgreApp PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
        add_custom_command( TARGET OgreApp POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)



if(ANDROID)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES 
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
	
	
		
		
elseif(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
  

#set_target_properties(OgreApp PROPERTIES MACOSX_BUNDLE TRUE)
 
# set_property(TARGET OgreApp PROPERTY MACOSX_BUNDLE TRUE)
 #set_property(TARGET OgreApp PROPERTY MACOSX_BUNDLE_INFO_PLIST Info.plist)
 
 
 
 
 
elseif(WIN32)
 
        install(TARGETS OgreApp
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins_d.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources_d.cfg
		DESTINATION bin
		CONFIGURATIONS Debug
	) 
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
	install(FILES 
	    ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/Plugin_OctreeSceneManager.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/OIS.dll
		
		${ENV_LIBROCKET}/bin/RocketControls.dll
		${ENV_LIBROCKET}/bin/RocketCore.dll
		${ENV_LIBROCKET}/bin/RocketDebugger.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)
 
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/OIS_d.dll
		
		DESTINATION bin
		CONFIGURATIONS Debug
	)
 
 
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   #install(FILES ${Boost_SYSTEM_LIBRARY_RELEASE}
   #${Boost_DATE_TIME_LIBRARY_RELEASE}
   #   ${Boost_THREAD_LIBRARY_RELEASE}
   #   DESTINATION bin
   #   CONFIGURATIONS Release RelWithDebInfo
   #)
 
   #install(FILES ${Boost_SYSTEM_LIBRARY_DEBUG}
   #${Boost_DATE_TIME_LIBRARY_DEBUG}
   #   ${Boost_THREAD_LIBRARY_DEBUG}
   #   DESTINATION bin
   #   CONFIGURATIONS Debug
   #)
endif()

if(UNIX)
 
	if(APPLE)
		message("MANZANITA.")
		set_property(TARGET OgreApp PROPERTY MACOSX_BUNDLE TRUE)
	
		#rm -rf ${CMAKE_CURRENT_BINARY_DIR}/dist/Components
		#	rm -rf ${CMAKE_CURRENT_BINARY_DIR}/dist/Plugins
		#	rm -rf ${CMAKE_CURRENT_BINARY_DIR}/dist/Resources
		#	rm -rf ${CMAKE_CURRENT_BINARY_DIR}/dist/Frameworks
	
		# create directories (if they don't exist)
		#	mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/dist/Components
		#	mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/dist/Plugins
		#	mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/dist/Resources
		#	mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/dist/Frameworks
 
 
			# copy components
			#cp $(OGRE_SDK)/lib/libOgrePaging.dylib $(CONTENT_PATH)/Components
			#cp $(OGRE_SDK)/lib/libOgreProperty.dylib $(CONTENT_PATH)/Components
			#cp $(OGRE_SDK)/lib/libOgreRTShaderSystem.dylib $(CONTENT_PATH)/Components
			#cp $(OGRE_SDK)/lib/libOgreTerrain.dylib $(CONTENT_PATH)/Components
 
			# copy plugins
			#cp $(OGRE_SDK)/lib/Plugin_BSPSceneManager.dylib $(CONTENT_PATH)/Plugins
		#	cp $(OGRE_SDK)/lib/Plugin_CgProgramManager.dylib $(CONTENT_PATH)/Plugins
		#	cp $(OGRE_SDK)/lib/Plugin_OctreeSceneManager.dylib $(CONTENT_PATH)/Plugins
		#	cp $(OGRE_SDK)/lib/Plugin_OctreeZone.dylib $(CONTENT_PATH)/Plugins
		#	cp $(OGRE_SDK)/lib/Plugin_PCZSceneManager.dylib $(CONTENT_PATH)/Plugins
		#	cp $(OGRE_SDK)/lib/Plugin_ParticleFX.dylib $(CONTENT_PATH)/Plugins
			#cp $(OGRE_SDK)/lib/RenderSystem_GL.dylib $(CONTENT_PATH)/Plugins
 
			# copy frameworks
			#cp -R /Library/Frameworks/Cg.framework $(CONTENT_PATH)/Frameworks/
		#	cp -R $(OGRE_SDK)/lib/release/Ogre.framework $(CONTENT_PATH)/Frameworks/
 
			# copy resource files
			#cp -R Resources/* ${CMAKE_CURRENT_BINARY_DIR}/Resources/
			#
			# change permission on all files
		#	chmod -R u+rwx ${CMAKE_CURRENT_BINARY_DIR}/dist/*
		#	chmod -R go+r ${CMAKE_CURRENT_BINARY_DIR}/dist/*
        install(TARGETS OgreApp
		BUNDLE  DESTINATION .
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
	elseif(NOT ANDROID)
		
        install(TARGETS OgreApp
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
		install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
		DESTINATION ./
		CONFIGURATIONS Release RelWithDebInfo Debug
		)
 
		install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
		${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
		)
 
	endif(APPLE)
 
	message("finunix.")
 
endif(UNIX)
 message("FIN DE CMAKELISTIS")
