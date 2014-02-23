#include "SystemInterfaceOgre3D.h"

SystemInterfaceOgre3D::SystemInterfaceOgre3D()
{
}

SystemInterfaceOgre3D::~SystemInterfaceOgre3D()
{
}

// Gets the number of seconds elapsed since the start of the application.
float SystemInterfaceOgre3D::GetElapsedTime()
{
	return timer.getMilliseconds() * 0.001f;
}

// Logs the specified message.
bool SystemInterfaceOgre3D::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
{
	Ogre::LogMessageLevel message_level;
	switch (type)
	{
		case Rocket::Core::Log::LT_ALWAYS:
		case Rocket::Core::Log::LT_ERROR:
		case Rocket::Core::Log::LT_ASSERT:
		case Rocket::Core::Log::LT_WARNING:
			message_level = Ogre::LML_CRITICAL;
			break;

		default:
			message_level = Ogre::LML_NORMAL;
			break;
	}

	Ogre::LogManager::getSingleton().logMessage(message.CString(), message_level);
	return false;
}
