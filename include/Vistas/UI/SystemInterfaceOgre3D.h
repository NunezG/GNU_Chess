

#ifndef SYSTEMINTERFACE3D_H
#define SYSTEMINTERFACE3D_H

#include <Rocket/Core/SystemInterface.h>
#include <Ogre.h>


class SystemInterfaceOgre3D : public Rocket::Core::SystemInterface
{
	public:
		SystemInterfaceOgre3D();
		virtual ~SystemInterfaceOgre3D();

		/// Gets the number of seconds elapsed since the start of the application.
		virtual float GetElapsedTime();

		/// Logs the specified message.
		virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);

	private:
		Ogre::Timer timer;
};

#endif
