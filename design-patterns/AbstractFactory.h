#include <iostream>
#include <memory>
#include <string>

class AbstractProductA {
public:
	virtual std::string name() = 0;
};

class AbstractProductB {
public:
	virtual std::string name() = 0;
};

class ProductA1 : public AbstractProductA {
public:
	std::string name();
};

class ProductA2 : public AbstractProductA {
public:
	std::string name();
};

class ProductB1 : public AbstractProductB {
public:
	std::string name();
};

class ProductB2 : public AbstractProductB {
public:
	std::string name();
};

class ConcreteFactory1;
class ConcreteFactory2;

class AbstractFactory {
public:
	enum class FACTORY {
		Factory1,
		Factory2
	};
	virtual std::unique_ptr<AbstractProductA> produceA() = 0;
	virtual std::unique_ptr<AbstractProductB> produceB() = 0;
	static std::unique_ptr<AbstractFactory> createFactory(FACTORY factory);
};

class ConcreteFactory1 : public AbstractFactory {
public:
	std::unique_ptr<AbstractProductA> produceA();
	std::unique_ptr<AbstractProductB> produceB();
};

class ConcreteFactory2 : public AbstractFactory {
public:
	std::unique_ptr<AbstractProductA> produceA();
	std::unique_ptr<AbstractProductB> produceB();
};

