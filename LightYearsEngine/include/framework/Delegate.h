#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...))
		{
			std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args)->bool
				{
					if (!obj.expired())
					{
						(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
						return true;
					}
					return false;
				};

			m_Callbacks.push_back(callbackFunc);
		}

		void Broadcast(Args... args)
		{
			for (auto it = m_Callbacks.begin(); it != m_Callbacks.end();)
			{
				if ((*it)(args...))
				{
					++it;
				}
				else
				{
					it = m_Callbacks.erase(it);
				}
			}
		}
	private:
		List<std::function<bool(Args...)>> m_Callbacks;
	};
}