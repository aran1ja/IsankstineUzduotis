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
#include <unordered_set>

using namespace std;

bool failoAtidarymas(const string& failoPasirinkimas);
string tvarkomeZodzius(const string& zodis);
bool ieskomeURL(const string& zodis);
void ieskotiZodziusSuAly(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius);
void zodziuIrasymasSarase(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius);
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, map<string, vector<int>>& ALYsarasas, vector<string>& url);
void irasymasIFaila(const map<string, vector<int>>& sarasas, map<string, vector<int>>& ALYsarasas, const vector<string>& url);

#endif