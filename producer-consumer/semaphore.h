#include <mutex>
#include <condition_variable>

class semaphore {
public:
	semaphore(int count_ = 0): count(count_) { }
	semaphore(const semaphore& rhs) = delete;
	semaphore operator=(const semaphore& rhs) = delete;
	semaphore(semaphore&& rhs) = delete;
	semaphore operator=(semaphore&& rhs) = delete;

	void down()
	{
		std::unique_lock<std::mutex> lock(mutx);
		while (count == 0)
			cv.wait(lock);
		--count;
	}
	void up()
	{
		std::unique_lock<std::mutex> lock(mutx);
		++count;
		cv.notify_one();
	}
private:
	std::mutex mutx;
	std::condition_variable cv;
	int count;
};
