#include <thread>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
#include <functional>

template <typename Iterator, typename T>
struct AccumulateBlock {
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallelAccumulate(Iterator first, Iterator last, T init)
{
    using UL = unsigned long;
    UL const length = std::distance(first, last);

    if (length == 0) {
        return init;
    }

    UL const min_per_thread = 25;
    UL const max_threads = (length + min_per_thread - 1) / min_per_thread;

    UL const hardware_threads = std::thread::hardware_concurrency();

    UL const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2,
                                        max_threads);

    UL const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    auto block_start = first;

    for (UL i = 0; i < (num_threads - 1); ++i) {
        auto block_end = block_start;
        std::advance(block_end, block_size);

        threads[i] = std::thread{AccumulateBlock<Iterator, T>(),
                                 block_start, block_end, std::ref(results[i])};

        block_start = block_end;
    }

    AccumulateBlock<Iterator, T>()(block_start, last, results[num_threads-1]);

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
    int a = 0;

    std::vector<int> vi(1000000, 1);

    std::cout << parallelAccumulate(vi.begin(), vi.end(), a);
}
