#include<iostream>
#include<chrono>

#include "threadpool.h"

void print() {
    threadpool pool(4);
    std::vector<std::future<void>> res;
    std::function<void(int, int)> func = [](int m, int j) {
        std::cout << "job " << m << " begin..." << std::endl;
        for (int i = 0; i < 100000; ++i){
            j += i;
        }
        std::cout << "job " << m << " done!" << std::endl;
        // std::cout << "i = " << i << ' ' << "j = " << j << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::cout << "i + j = " << i + j << ' ' << std::endl;
    };
    for (int i = 0; i < 10; ++i) {
        res.emplace_back(pool.enqueue(func, i, (2 * i)));
    }
    for (std::future<void>& a : res) {
        a.get();
    }
    pool.shutdown();
}

int main() {
    print();
    std::cout << "end" << std::endl;
    return 0;
}
