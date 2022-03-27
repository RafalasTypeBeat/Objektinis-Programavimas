#include <iostream>
#include <random>
#include <chrono>
int main() {
using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
std::uniform_int_distribution<int> dist(0, 99);
for (int i = 0; i < 16; ++i) {
std::cout << dist(mt) << " ";
}
std::cout << std::endl;
}