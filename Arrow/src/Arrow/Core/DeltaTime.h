#pragma once

namespace Arrow {

	class DeltaTime {
	public:
		DeltaTime(float time)
			:m_Time(time) {
		}

		operator float() const { return m_Time; }

		float GetSeconds() { return m_Time; }
		float GetMileseconds() { return m_Time * 1000; }
	private:
		float m_Time;
	};
}