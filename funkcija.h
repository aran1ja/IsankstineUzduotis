#ifndef FUNKCIJA_H
#define FUNKCIJA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <iomanip>

using namespace std;

bool failoAtidarymas(const string& failoPasirinkimas);
void zodziuIrasymasSarase(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius);
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas);
void irasymasIFaila(const map<string, vector<int>>& sarasas);

#endif


