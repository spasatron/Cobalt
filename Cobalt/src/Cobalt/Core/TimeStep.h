#pragma once


namespace Cobalt {

	class TimeStep {
	public:
		TimeStep(float time = 0.0f) : m_time(time) {}


		float GetSeconds() const { return m_time; }
		float GetMilliseconds() const { return m_time * 1000; }


		operator float() const { return m_time; }


	private:
		float m_time;
	};
	
}