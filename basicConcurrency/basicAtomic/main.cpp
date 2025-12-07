#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

int main() {
    
    const int N = 1'000'000;
    const int num_threads = 4;

    std::atomic<long long> sum{0};

    auto worker = [&] (int start, int end) {
        long long local = 0;

        for (int i=start;i<=end;++i){
            local +=i;
        };

        sum.fetch_add(local, std::memory_order_relaxed);

    };

    std::vector<std::thread> threads;
    int chunk_size = N/num_threads;

    for (int i=0;i<num_threads;i++){
        int start = i*chunk_size+1;
        int end = (i==num_threads-1) ? N : (i+1)*chunk_size;

        threads.emplace_back(worker,start,end);

    }

    for (auto &t:threads) t.join();
    std::cout<<"final sum is: "<<sum.load()<< std::endl;

    return 0;
}