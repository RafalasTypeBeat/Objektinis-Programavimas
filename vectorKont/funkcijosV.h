#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <chrono>
#include <sstream>
#include "mokiniaiV.h"

using std::string;
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using hrClock = std::chrono::high_resolution_clock;
using std::istream;
using std::stringstream;

void input(vector<mokinys>& mok, int vieta);
void print(vector<mokinys>& mok);
istream& readHw(istream& in, mokinys& temp);
istream& readData(istream& in, mokinys& temp);
bool compareName(const mokinys&x , const mokinys& y);
double mediana(vector<double> hw);
double vidurkis(vector<double> hw);
double galutinis(double egz, double hw);
double galutinis(double egz, const vector<double>& hw, double (*kriterijus)(vector<double>) = mediana);
void generate(int &FileSkc);
bool gavoSkola(vector<double> &hw, int egz, double &mediana);
vector<mokinys> sortByGrades(vector<mokinys>& mok);
void readAndSort(int FileSkc);
void writeSorted(vector<mokinys> &fail,vector<mokinys> &pass, int FileNr);