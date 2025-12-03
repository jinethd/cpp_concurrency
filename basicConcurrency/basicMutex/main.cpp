#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int main() {

    const int N = 1'000'000;
    const int num_threads = 4;

    long long total_sum = 0;
    std::mutex mtx;

    auto worker = [&] (int start, int end) {
        long long local = 0;

        for(int i=start;i<=end;++i){
            local +=i;
        }
        {
            std::lock_guard<std::mutex> lock(mtx);
            total_sum += local;
        }
        //mtx.unlock();

    };

    std::vector<std::thread> threads;
    int chunk_size = N/num_threads;

    for(int i=0;i<num_threads;i++){
        int start = i*chunk_size+1;
        int end = (i == num_threads-1) ? N : (i+1)*chunk_size;

        std::cout<<"start: "<<start<< " end: "<<end<<std::endl;

        threads.emplace_back(worker,start,end);
    }

    for(auto &t:threads) t.join();

    std::cout<<total_sum+1000000<<std::endl;

    return 0;
}