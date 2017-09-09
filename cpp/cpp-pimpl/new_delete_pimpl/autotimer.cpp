#include "autotimer.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

class AutoTimer::Impl {
public:
	double getElapsed() const
	{
#ifdef _WIN32
		return (GetTickCount() - m_start_time) / 1e3;
#else
		struct timeval end_time;
		gettimeofday(&end_time, NULL);
		double t1 = m_start_time.tv_usec / 1e6 + m_start_time.tv_sec;
		double t2 = end_time.tv_usec / 1e6 + end_time.tv_sec;
		return t2 - t1; 
#endif
	}
	
	std::string m_name;
#ifdef _WIN32
	DWORD m_start_time;
#else
	struct timeval m_start_time;
#endif
};

AutoTimer::AutoTimer(const std::string& name):
	m_impl(new AutoTimer::Impl())
{
	m_impl->m_name = name;
#ifdef _WIN32
	m_impl->m_start_time = GetTickCount();
#else
	gettimeofday(&m_impl->m_start_time, NULL);
#endif
}

AutoTimer::~AutoTimer()
{
	std::cout << m_impl->m_name << ": took " << m_impl->getElapsed() << " secs\n";
	delete m_impl;
	m_impl = nullptr;
}
