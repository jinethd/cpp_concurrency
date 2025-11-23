#include <iostream>

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


    std::cout<<"Hello World"<<std::endl;

    return 0;
}