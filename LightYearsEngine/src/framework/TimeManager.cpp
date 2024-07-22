#include "framework/TimeManager.h"

namespace ly
{
	unique<TimeManager> TimeManager::m_TimeManager{ nullptr };

	void TimeManager::UpdateTimer(float deltaTime)
	{
		for (Timer& timer : m_Timers)
		{
			timer.TickTime(deltaTime);
		}
	}

	TimeManager::TimeManager() : m_Timers{}
	{

	}

	TimeManager& TimeManager::Get()
	{
		if (!m_TimeManager)
		{
			m_TimeManager = unique<TimeManager>(new TimeManager());
		}

		return *m_TimeManager;
	}

	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		: m_Listener{ weakRef,callback },
		m_Duration{ duration },
		m_Repeat{ repeat },
		m_TimeCounter{0.f},
		m_IsExpired{false}
	{

	}

	void Timer::TickTime(float deltaTime)
	{
		if (Expired())
		{
			return;	
		}
		
		m_TimeCounter += deltaTime;
		if (m_TimeCounter >= m_Duration)
		{
			m_Listener.second();

			if (m_Repeat)
			{
				m_TimeCounter = 0.f;
			}
			else
			{
				SetExpired();
			}
		}
	}

	bool Timer::Expired() const
	{
		return m_IsExpired || m_Listener.first.expired() || m_Listener.first.lock()->isPendingDestroyed();
	}

	void Timer::SetExpired()
	{
		m_IsExpired = true;
	}
}