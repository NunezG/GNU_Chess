#ifndef ROCKETAPPLICATION_H
#define ROCKETAPPLICATION_H

//#include <OgreExampleApplication.h>
//#include "BaseVistas.h"

#include <Ogre.h>

namespace Rocket {
namespace Core {

class Context;

}
}

class SystemInterfaceOgre3D;
class RenderInterfaceOgre3D;

/**
	@author Peter Curry
 */

class RocketApplication : public BaseVistas
{
	public:
		RocketApplication();
		virtual ~RocketApplication();

	protected:
		

		/// Called from Ogre before a queue group is rendered.
		//virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
		/// Called from Ogre after a queue group is rendered.
        //virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);

	private:
		




	    FrameListener* mFrameListener;
		    Ogre::Root* mRoot;
					    Ogre::RenderWindow* mWindow;

		//Ogre::SceneManager* mSceneMgr;
};

#endif
