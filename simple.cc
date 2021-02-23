#include <iostream>
#include <thread>

void thread_init()
{
    std::cout << "This statement is executed in the new thread\n";
}

int main()
{
    std::thread t(thread_init);
    std::cout << "This statement is executed in the main thread\n";
    t.join();
}