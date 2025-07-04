#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int buffer = -1; // Shared data (-1 means empty)
bool buffer_full = false; // Indicates if buffer has data

std::mutex mtx;
std::condition_variable cv;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until buffer is empty
        cv.wait(lock, []() { return !buffer_full; });

        // Critical section: put data into buffer
        buffer = i;
        std::cout << "Produced: " << buffer << std::endl;
        buffer_full = true;

        // Notify consumer that buffer has data
        cv.notify_one();
    }
}

void consumer() {
    for (int i = 1; i <= 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until buffer has data
        cv.wait(lock, []() { return buffer_full; });

        // Critical section: consume data from buffer
        std::cout << "Consumed: " << buffer << std::endl;
        buffer = -1;
        buffer_full = false;

        // Notify producer that buffer is empty
        cv.notify_one();
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
