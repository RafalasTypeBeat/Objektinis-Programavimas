#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <list>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <chrono>
#include <sstream>
#include "mokiniaiL.h"

using std::string;
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::list;
using hrClock = std::chrono::high_resolution_clock;
using std::istream;
using std::stringstream;

void input(list<mokinys>& mok, int vieta);
void print(list<mokinys>& mok);
istream& readHw(istream& in, mokinys& temp);
istream& readData(istream& in, mokinys& temp);
bool compareName(const mokinys&x , const mokinys& y);
double mediana(list<double> hw);
double vidurkis(list<double> hw);
double galutinis(double egz, double hw);
double galutinis(double egz, const list<double>& hw, double (*kriterijus)(list<double>) = mediana);
void generate(int &FileSkc);
bool gavoSkola(list<double> &hw, int egz, double &mediana);
void sortByGrades(list<mokinys>& mok, list<mokinys> &fail, list<mokinys> &pass);
void readAndSort(int FileSkc);
void writeSorted(list<mokinys> &fail,list<mokinys> &pass, int FileNr);