// autotimer.h
#include <string>
#include <memory>

class AutoTimer {
public:
	explicit AutoTimer(const std::string& name);
	~AutoTimer();
private:
	class Impl;
	Impl* m_impl; // ʹ������ָ�� 
};
