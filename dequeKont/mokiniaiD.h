#pragma once
#include <deque>
#include <string>
struct mokinys
{
    std::string name = "", surename = "";
    std::deque<double> hw;
    int egzam;
    int size = 0;
    double mediana = 0;
};