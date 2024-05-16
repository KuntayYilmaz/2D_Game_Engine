#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	Object::Object()
		:m_isPendingDestroyed{false}
	{
	}
	
	Object::~Object()
	{
		LOG("Object Destroyed\n");
	}
	
	void Object::Destroy()
	{
		m_isPendingDestroyed = true;
	}
}
