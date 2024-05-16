#pragma once

namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		void Destroy();
		bool isPendingDestroyed() const { return m_isPendingDestroyed; }

	private:
		bool m_isPendingDestroyed;
	};
}