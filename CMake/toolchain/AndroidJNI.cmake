#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
message("ENTRA EN ANDROID JNI DE PROYECTOGIT")
if(ANDROID)
	
set (HEADER_FILES
        ./include/AndroidListener.h
        ./include/AndroidFileInterface.h
)
	
	#set(ANDROID_FORCE_ARM_BUILD TRUE)
set(SOURCE_FILES ./src/Inicio.cpp)


    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummyChess.cpp "int x = 24;")
    ADD_LIBRARY(ChessDummy MODULE ${CMAKE_CURRENT_BINARY_DIR}/dummyChess.cpp)

  #add_library(OgreApp STATIC ${SRCSAPP} )


    target_link_libraries(ChessDummy OgreApp ChessView ChessViewModel ChessModel ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})


    add_dependencies(ChessDummy gnustl_static android/cpufeatures android/native_app_glue ChessView OgreApp)



#target_link_libraries(ChessDummy gnustl_static android/cpufeatures android/native_app_glue ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES} ChessView ChessViewModel ChessModel)


 # @   add_dependencies(ChessDummy gnustl_static ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES} ChessView ChessModel ChessViewModel)

   # target_link_libraries(ChessDummy OgreApp ChessView ChessViewModel ChessModel ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})
        # add_dependencies(ChessDummy ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})
        #add_dependencies(ChessDummy OgreApp)
    #     add_dependencies(ChessDummy ChessView ChessViewModel ChessModel ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${LIBROCKET_LIBRARIES})




        #if(OGRE_BUILD_RENDERSYSTEM_GLES2)
	#else()		
	#	add_dependencies(OgreApp OgreMain RenderSystem_GLES)
	#endif()


    if(APPLE OR WIN32)
      SET(ANDROID_EXECUTABLE "android")
      SET(NDK_BUILD_EXECUTABLE "ndk-build")
    else()
      SET(ANDROID_EXECUTABLE "$ENV{ANDROID_SDK}/tools/android")
      SET(NDK_BUILD_EXECUTABLE "$ENV{ANDROID_NDK}/ndk-build")
    endif()

	SET(ANDROID_MOD_NAME "AndroidChess")
	SET(JNI_SRC "LOCAL_PATH := @CMAKE_SOURCE_DIR@/src\n")
    SET(JNI_SRC "${JNI_SRC}\tLOCAL_SRC_FILES := Inicio.cpp")
    SET(ANT_EXECUTABLE "ant")
	
	if(${ANDROID_NATIVE_API_LEVEL} LESS 14)
		MATH(EXPR ANDROID_SDK_API_LEVEL "${ANDROID_NATIVE_API_LEVEL}+1")
	else()
		SET(ANDROID_SDK_API_LEVEL "${ANDROID_NATIVE_API_LEVEL}")
		SET(SCREEN_SIZE "")
	endif()
	
	if(OGRE_CONFIG_ENABLE_GLES2_GLSL_OPTIMISER)
		SET(GLES_OPTIMISER "-lglsl_optimizer -lmesa -lglcpp-library")
	endif()

    SET(ANDROID_TARGET "android-${ANDROID_SDK_API_LEVEL}")
    
    SET(NDKOUT "${CMAKE_BINARY_DIR}/AndroidChessBuid")
    file(MAKE_DIRECTORY "${NDKOUT}")
    file(MAKE_DIRECTORY "${NDKOUT}/jni")
    file(MAKE_DIRECTORY "${NDKOUT}/assets")	
    file(MAKE_DIRECTORY "${NDKOUT}/res")	
	#file(MAKE_DIRECTORY "${NDKOUT}/src")
   # file(MAKE_DIRECTORY "${NDKOUT}/src/org")
   # file(MAKE_DIRECTORY "${NDKOUT}/org/gnusoft")
	#file(MAKE_DIRECTORY "${NDKOUT}/org/gnusoft/chess")	
	#file(COPY "@CMAKE_SOURCE_DIR@/OgreMain/src/Android/JNI/OgreActivityJNI.java" DESTINATION "${NDKOUT}/src/org/ogre3d/android")
	#file(COPY "@CMAKE_SOURCE_DIR@/OgreMain/src/Android/JNI/MainActivity.java" DESTINATION "${NDKOUT}/src/org/ogre3d/android")
		
    file(WRITE "${NDKOUT}/default.properties" "target=${ANDROID_TARGET}")
    file(WRITE "${NDKOUT}/jni/Application.mk" "APP_ABI := ${ANDROID_ABI}\nAPP_STL := gnustl_static")
    configure_file("CMake/Templates/AndroidManifest.xml.in" "${NDKOUT}/AndroidManifest.xml" @ONLY)

    if(NOT ANDROID_GLES_ONLY)
	  configure_file("CMake/Templates/Android.mk.in" "${NDKOUT}/jni/Android.mk" @ONLY)
    else()
      configure_file("CMake/Templates/AndroidGLES1.mk.in" "${NDKOUT}/jni/Android.mk" @ONLY)
    endif()
    
	
	#configure_file("CMake/Templates/Android_resources.cfg.in" "${NDKOUT}/assets/resources.cfg" @ONLY)
    
	
	
	 
   # file(COPY "${CMAKE_SOURCE_DIR}/Media/models" DESTINATION "${NDKOUT}/assets")
    #file(COPY "${CMAKE_SOURCE_DIR}/Media/particle" DESTINATION "${NDKOUT}/assets")
    #file(COPY "${CMAKE_SOURCE_DIR}/Media/RTShaderLib" DESTINATION "${NDKOUT}/assets")
    #file(COPY "${CMAKE_SOURCE_DIR}/Samples/Media/thumbnails" DESTINATION "${NDKOUT}/assets")
    #file(COPY "${CMAKE_SOURCE_DIR}/Samples/Media/packs" DESTINATION "${NDKOUT}/assets")
    #file(COPY "${CMAKE_SOURCE_DIR}/Samples/Media/materials" DESTINATION "${NDKOUT}/assets")
    
	#file(COPY "${CMAKE_SOURCE_DIR}/SDK/Android/drawable-hdpi" DESTINATION "${NDKOUT}/res")
	#file(COPY "${CMAKE_SOURCE_DIR}/SDK/Android/drawable-ldpi" DESTINATION "${NDKOUT}/res")
	#file(COPY "${CMAKE_SOURCE_DIR}/SDK/Android/drawable-mdpi" DESTINATION "${NDKOUT}/res")
	#file(COPY "${CMAKE_SOURCE_DIR}/SDK/Android/drawable-xhdpi" DESTINATION "${NDKOUT}/res")
	
	
	
	add_custom_command(
	                    TARGET ChessDummy
                        POST_BUILD
	                    COMMAND ${ANDROID_EXECUTABLE} update project --target ${ANDROID_TARGET} --path "${NDKOUT}"
	                    WORKING_DIRECTORY ${NDKOUT}
	                  )
	
	if(DEBUG)	 
	 	add_custom_command(
							TARGET ChessDummy
						    POST_BUILD
					        COMMAND ${NDK_BUILD_EXECUTABLE} all -j2 V=1 NDK_DEBUG=1
				            WORKING_DIRECTORY ${NDKOUT}
			              )
	else()
		add_custom_command(
							TARGET ChessDummy
						    POST_BUILD
					        COMMAND ${NDK_BUILD_EXECUTABLE} all -j2
				            WORKING_DIRECTORY ${NDKOUT}
			              )
	endif()
	                  
	add_custom_command(
	                    TARGET ChessDummy
                        POST_BUILD
	                    COMMAND ${ANT_EXECUTABLE} debug
	                    WORKING_DIRECTORY ${NDKOUT}
	                  )

endif()
message("FIN DE ANDROIDJNI.")
