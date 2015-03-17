# - Try to find RakNet
# Once done this will define
#
#  RakNet_FOUND - system has RakNet
#  RakNet_INCLUDES - the RakNet include directory
#  RakNet_LIBRARY - Link these to use RakNet
getenv_path(RAKNET_ROOT)


if(Win32)
SET(RakNet_LIBRARY_Name RakNetLibStatic)
SET(RakNet_LIBRARY_Name_Debug RakNet_VS2008_LibStatic_Release_Win32)
endif(Win32)

FIND_LIBRARY (RakNet_LIBRARY_RELEASE NAMES ${RakNet_LIBRARY_Name}
    PATHS
    ENV LD_LIBRARY_PATH
    ENV LIBRARY_PATH
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /opt/local/lib
	${ENV_RAKNET_ROOT}/lib
	C:/Users/gui/Documents/RakNet/lib/Lib/LibStatic/Release/
    )
	
FIND_LIBRARY (RakNet_LIBRARY_DEBUG NAMES  ${RakNet_LIBRARY_Name_Debug}
    PATHS
    ENV LD_LIBRARY_PATH
    ENV LIBRARY_PATH
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /opt/local/lib
	${ENV_RAKNET_ROOT}/lib
    )	
	
	

FIND_PATH (RakNet_INCLUDES raknet/RakPeer.h
    ENV CPATH
    /usr/include
    /usr/local/include
    /opt/local/include
	${ENV_RAKNET_ROOT}/include
    )
 
 
 	message("EN RAKNET.")
 	message("${RakNet_INCLUDES}")

IF(RakNet_INCLUDES AND RakNet_LIBRARY_RELEASE)
    SET(RakNet_FOUND TRUE)
ENDIF(RakNet_INCLUDES AND RakNet_LIBRARY_RELEASE)

 	message("EN RAKNET.")
 	message("${RakNet_LIBRARIES}")
	 	message("${RakNet_FOUND}")
 	message("${RakNet_LIBRARY_RELEASE}")

IF(RakNet_FOUND)
  SET(RakNet_INCLUDES ${RakNet_INCLUDES})
  
  
   IF (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
        SET(RakNet_LIBRARY optimized ${RakNet_LIBRARY_RELEASE} debug ${RakNet_LIBRARY_DEBUG})
      ELSE()
        # if there are no configuration types and CMAKE_BUILD_TYPE has no value
        # then just use the release libraries
        SET(RakNet_LIBRARY ${RakNet_LIBRARY_RELEASE} )
      ENDIF()
  IF(NOT RakNet_FIND_QUIETLY)
    MESSAGE(STATUS "Found RakNet: ${RakNet_LIBRARIES}")
  ENDIF(NOT RakNet_FIND_QUIETLY)
ELSE(RakNet_FOUND)
  IF(RakNet_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find RakNet")
  ENDIF(RakNet_FIND_REQUIRED)
ENDIF(RakNet_FOUND)
