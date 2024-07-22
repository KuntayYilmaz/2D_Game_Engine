#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
	struct Timer
	{
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();
	private:
		std::pair<weak<Object>, std::function<void()>> m_Listener;
		float m_Duration;
		bool m_Repeat;
		float m_TimeCounter;
		bool m_IsExpired;

	};


	class TimeManager
	{
	public:
		static TimeManager& Get();
		template<typename ClassName>
		void SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			m_Timers.push_back(Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); },duration, repeat));
		}

		void UpdateTimer(float deltaTime);

	protected:
		TimeManager();
	private:
		static unique<TimeManager> m_TimeManager;
		List<Timer> m_Timers;
	};
}