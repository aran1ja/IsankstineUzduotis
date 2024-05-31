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
string tvarkomeZodzius(const string& zodis);
bool ieskomeURL(const string& zodis);
void zodziuIrasymasSarase(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius);
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, vector<string>& url);
void irasymasIFaila(const map<string, vector<int>>& sarasas, const vector<string>& url);

#endif


