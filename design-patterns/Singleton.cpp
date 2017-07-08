#include <iostream>
#include <memory>

class Singleton {
public:
	static std::shared_ptr<Singleton> getInstance()
	{
		static std::shared_ptr<Singleton> instance{new Singleton};
		return instance;
	}
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
private:
	Singleton()
	{
		std::cout << "create an instance.\n";
	}
};

int main()
{
	// only create once.
	auto s1 = Singleton::getInstance();
	auto s2 = Singleton::getInstance();
}
