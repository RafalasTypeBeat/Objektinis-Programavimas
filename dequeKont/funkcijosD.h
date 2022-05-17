#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <deque>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <chrono>
#include <sstream>
#include "mokiniaiD.h"

using std::string;
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::deque;
using hrClock = std::chrono::high_resolution_clock;
using std::istream;
using std::stringstream;
using std::sort;

void input(deque<mokinys>& mok, int vieta);
void print(deque<mokinys>& mok);
istream& readHw(istream& in, mokinys& temp);
istream& readData(istream& in, mokinys& temp);
bool compareName(const mokinys&x , const mokinys& y);
double mediana(deque<double> hw);
double vidurkis(deque<double> hw);
double galutinis(double egz, double hw);
double galutinis(double egz, const deque<double>& hw, double (*kriterijus)(deque<double>) = mediana);
void generate(int &FileSkc);
bool gavoSkola(deque<double> &hw, int egz, double &mediana);
void sortByGrades(deque<mokinys>& mok, deque<mokinys> &fail, deque<mokinys> &pass);
void readAndSort(int FileSkc);
void writeSorted(deque<mokinys> &fail,deque<mokinys> &pass, int FileNr);