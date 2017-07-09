#include "AbstractFactory.h"

std::string ProductA1::name()
{
	return "ProductA1";
}

std::string ProductA2::name()
{
	return "ProductA2";
}

std::string ProductB1::name()
{
	return "ProductB1";
}

std::string ProductB2::name()
{
	return "ProductB2";
}

class ConcreteFactory1;
class ConcreteFactory2;

std::unique_ptr<AbstractFactory> AbstractFactory::createFactory(AbstractFactory::FACTORY factory)
{
	if (factory == FACTORY::Factory1) {
		return std::unique_ptr<AbstractFactory>(new ConcreteFactory1);
	} else if (factory == FACTORY::Factory2) {
		return std::unique_ptr<AbstractFactory>(new ConcreteFactory2);
	}
}

std::unique_ptr<AbstractProductA> ConcreteFactory1::produceA() {
	return std::unique_ptr<AbstractProductA>(new ProductA1);
}

std::unique_ptr<AbstractProductB> ConcreteFactory1::produceB() {
	return std::unique_ptr<AbstractProductB>(new ProductB1);
}

std::unique_ptr<AbstractProductA> ConcreteFactory2::produceA() {
	return std::unique_ptr<AbstractProductA>(new ProductA2);
}

std::unique_ptr<AbstractProductB> ConcreteFactory2::produceB() {
	return std::unique_ptr<AbstractProductB>(new ProductB2);
}

int main()
{
	std::unique_ptr<AbstractFactory> factory = 
		AbstractFactory::createFactory(AbstractFactory::FACTORY::Factory1);
	std::cout << "get ProductA1 from ConcreteFactory1: "
		 << factory->produceA()->name() << "\n";
	std::cout << "get ProductB1 from ConcreteFactory1: "
		 << factory->produceB()->name() << "\n";

	factory = 
		AbstractFactory::createFactory(AbstractFactory::FACTORY::Factory2);
	std::cout << "get ProductA2 from ConcreteFactory2: "
		 << factory->produceA()->name() << "\n";
	std::cout << "get ProductB2 from ConcreteFactory2: "
		 << factory->produceB()->name() << "\n";
}
