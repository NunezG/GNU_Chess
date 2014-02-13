# - Try to find libRocket
# Once done this will define
#  LIBROCKET_FOUND - System has libRocket
#  LIBROCKET_INCLUDE_DIRS - The LibRocket include directories
#  LIBROCKET_LIBRARIES - The libraries needed to use LibRocket
#  LIBROCKET_DEFINITIONS - Compiler switches required for using LibRocket

include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(LIBROCKET)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(LIBROCKET)
getenv_path(LIBROCKET_INCLUDE)
getenv_path(LIBROCKET_LIBRARY)

find_path(LIBROCKET_INCLUDE_DIR Rocket/Core.h
			PATHS ${ENV_LIBROCKET}/include
          PATH_SUFFIXES Rocket )

#find_library(LIBROCKET_LIBRARY RocketCore "${ENV_LIBROCKET}/lib")


#if (${CMAKE_BUILD_TYPE} = "Release")
#find_library(LIBROCKET_CORE_LIBRARY RocketCore "${ENV_LIBROCKET}/lib")
#  find_library(LIBROCKET_CONTROLS_LIBRARY RocketControls "${ENV_LIBROCKET}/lib")
#  find_library(LIBROCKET_DEBUGGER_LIBRARY RocketDebugger "${ENV_LIBROCKET}/lib")
#else ()
#find_library(LIBROCKET_CORE_LIBRARY RocketCore_d "${ENV_LIBROCKET}/lib")
#  find_library(LIBROCKET_CONTROLS_LIBRARY RocketControls_d "${ENV_LIBROCKET}/lib")
#  find_library(LIBROCKET_DEBUGGER_LIBRARY RocketDebugger_d "${ENV_LIBROCKET}/lib")

#endif ()


find_library(LIBROCKET_CORE_LIBRARY_DBG RocketCore_d "${ENV_LIBROCKET}/lib")
find_library(LIBROCKET_CORE_LIBRARY_REL RocketCore "${ENV_LIBROCKET}/lib")
  make_library_set(LIBROCKET_CORE_LIBRARY)

find_library(LIBROCKET_CONTROLS_LIBRARY_DBG RocketControls_d "${ENV_LIBROCKET}/lib")
find_library(LIBROCKET_CONTROLS_LIBRARY_REL RocketControls "${ENV_LIBROCKET}/lib")
  make_library_set(LIBROCKET_CONTROLS_LIBRARY)

find_library(LIBROCKET_DEBUGGER_LIBRARY_DBG RocketDebugger_d "${ENV_LIBROCKET}/lib")
find_library(LIBROCKET_DEBUGGER_LIBRARY_REL RocketDebugger "${ENV_LIBROCKET}/lib")
  make_library_set(LIBROCKET_DEBUGGER_LIBRARY)

set(LIBROCKET_LIBRARIES ${LIBROCKET_LIBRARY} ${LIBROCKET_LIBRARY} ${LIBROCKET_CORE_LIBRARY} ${LIBROCKET_CONTROLS_LIBRARY} ${LIBROCKET_DEBUGGER_LIBRARY})
set(LIBROCKET_INCLUDE_DIRS ${LIBROCKET_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBROCKET_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LibRocket DEFAULT_MSG
                                  LIBROCKET_LIBRARY LIBROCKET_INCLUDE_DIR)

mark_as_advanced(LIBROCKET_INCLUDE_DIR LIBROCKET_LIBRARY )