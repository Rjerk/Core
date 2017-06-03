#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

class Observable;

class Observer {
public:
    virtual ~Observer();
    virtual void update() = 0;
    void observe(Observable* s);
protected:
    Observable* subject_;
};

class Observable {
public:
    void register_(Observer* x)
    {
        observers_.push_back(x);
    }
    void unregister(Observer* x)
    {
        std::vector<Observer*>::iterator iter = 
			std::find(observers_.begin(), observers_.end(), x);
        if (iter != observers_.end()) {
            std::swap(*iter, observers_.back());
            observers_.pop_back();
        }
    }
    
    void notifyObservers()
    {
        for (size_t i = 0; i < observers_.size(); ++i) {
            auto x = observers_[i];
            if (x) x->update();
        }
    }
private:
    std::vector<Observer*> observers_;
};

Observer::~Observer()
{
	subject_->unregister(this);
}

void Observer::observe(Observable* s)
{
	s->register_(this);
	subject_ = s;
}

class Foo : public Observer {
    virtual void update()
    {
    	printf ("Foo::update() %p\n", this);
	}
};

int main()
{
	Observable subject;
	
	Foo* p1 = new Foo;
	Foo* p2 = new Foo;
	Foo* p3 = new Foo;
	p1->observe(&subject);
	p2->observe(&subject);
	p3->observe(&subject);
	std::cout << "notify observers:\n";
	subject.notifyObservers();

	delete p1;
	delete p2;
	
	std::cout << "notify observers:\n";
	subject.notifyObservers();
}
