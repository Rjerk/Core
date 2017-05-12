#include <deque>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

#include "semaphore.h"

std::deque<int> buffer;
const int sz = 10;

semaphore mx(1);
semaphore full(0);
semaphore empty(sz);

// produce random integer as item.
unsigned produce_item()
{
	static thread_local std::mt19937 generator;
	static std::uniform_int_distribution<unsigned> u(0, 99);
	unsigned item = u(generator);
	return item;
}

void consume_item(unsigned item)
{
}

// put item to buffer.
void put_item(unsigned item)
{
	buffer.push_back(item);
	std::cout << "produce: " << item << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

// get item from buffer.
unsigned get_item()
{
	unsigned item = buffer.back();
	buffer.pop_back();
	std::cout << "consume: " << item << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return item;
}

void producer()
{
	while (true) {
		unsigned item = produce_item();
		empty.down();
		mx.down();
		put_item(item);
		mx.up();
		full.up();
	}
}

void consumer()
{
	while (true) {
		full.down();
		mx.down();
		unsigned item = get_item();
		mx.up();
		empty.up();
		consume_item(item);
	}
}

int main()
{
	std::thread producer_thread(&producer);
	std::thread consumer_thread(&consumer);
	producer_thread.join();
	consumer_thread.join();
	return 0;
}
