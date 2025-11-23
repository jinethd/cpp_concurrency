#include <iostream>
#include <vector>
#include <thread>

// we seek to sum the numbers 1-1000000 using 4 separate threads for each quarter of 1m

// here is the function that the thread will run 
void partialSum(int start, int end, long long &result) {
    result = 0;
    for(int i=start;i<=end;++i){
        result += i;
    }
};

int main(){

    const int N = 1'000'000;
    const int num_threads = 4;

    std::vector<std::thread> threads;
    std::vector<long long> results(num_threads);

    //std::cout<<sizeof(results[0])<<std::endl;

    int chunk_size = N/num_threads;

    for (int i=0; i<num_threads ; ++i) {

        int start = i*chunk_size +1;
        int end = (i==num_threads-1) ? N:(i+1)*chunk_size;

        threads.emplace_back(partialSum,start,end,std::ref(results[i]));
    }

    for (auto &t : threads) {
        t.join();
    }

    long long total_sum = 0;

    for (auto sum : results) {
        total_sum += sum;
    }

    std::cout<<"total is: "<<total_sum<<std::endl;

    return 0;
}