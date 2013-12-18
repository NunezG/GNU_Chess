# This is my README

In Windows, the following env variables should be added so CMake can find the dependencies:


Ogre:
	OGRE_HOME or OGRE_SDK (OGRE SDK directory, Example: D:/OgreSDK_vc11_v1-9-0)

	alternative:
	OGRE_SOURCE (OGRE Build directory)
	OGRE_BUILD (OGRE Source directory)
	OGRE_DEPENDENCIES_DIR is also suitable in this case

CEGUI:
	CEGUI_HOME (CEGUI Build directory, Example: D:/cegui-0.8.2-build)
	CEGUI_DIR (CEGUI Source directory, Example: D:/cegui-0.8.2)


BOOST:
BOOST_ROOT
