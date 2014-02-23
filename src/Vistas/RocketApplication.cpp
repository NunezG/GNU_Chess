
#include "../../headers/Vistas/RocketApplication.h"
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include "../../headers/Vistas/RenderInterfaceOgre3D.h"
#include "../../headers/Vistas/FrameListener.h"
#include "../../headers/Vistas/SystemInterfaceOgre3D.h"
#include <direct.h>

RocketApplication::RocketApplication()
{
	
}

RocketApplication::~RocketApplication()
{
}




// Called from Ogre before a queue group is rendered.
//void RocketApplication::renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation))
//{
//	if (queueGroupId == Ogre::RENDER_QUEUE_OVERLAY && Ogre::Root::getSingleton().getRenderSystem()->_getViewport()->getOverlaysEnabled())
//	{
//		context->Update();

//		ConfigureRenderSystem();
//		context->Render();
//	}
//}

// Called from Ogre after a queue group is rendered.
//void RocketApplication::renderQueueEnded(Ogre::uint8 ROCKET_UNUSED(queueGroupId), const Ogre::String& ROCKET_UNUSED(invocation), bool& ROCKET_UNUSED(repeatThisInvocation))
//{
//}



