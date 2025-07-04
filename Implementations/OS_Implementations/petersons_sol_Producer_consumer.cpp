#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

//REFER GFG COMMENTS FOR UNDERSTANDING BUT GFG's code is wrong... correct code is this..

const int N = 2;

std::atomic<bool> flag[N]; // Atomic flags
std::atomic<int> turn;     // Atomic turn variable
int buffer = -1;           // Shared buffer

void producer(int id) {
    while (true) {
        // Entry section
        flag[id] = true;
        turn = 1 - id;
        while (flag[1 - id] && turn == 1 - id) {
            // Busy wait
        }

        // Critical Section
        if (buffer == -1) {
            buffer = rand() % 100;
            std::cout << "Produced: " << buffer << std::endl;
        }

        // Exit section
        flag[id] = false;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer(int id) {
    while (true) {
        // Entry section
        flag[id] = true;
        turn = 1 - id;
        while (flag[1 - id] && turn == 1 - id) {
            // Busy wait
        }

        // Critical Section
        if (buffer != -1) {
            std::cout << "Consumed: " << buffer << std::endl;
            buffer = -1;
        }

        // Exit section
        flag[id] = false;

        std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }
}

int main() {
    flag[0] = false;
    flag[1] = false;
    turn = 0;

    std::thread t1(producer, 0);
    std::thread t2(consumer, 1);

    t1.join();
    t2.join();

    return 0;
}
