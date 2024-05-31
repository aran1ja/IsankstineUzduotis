#include "funkcija.h"

//kazku klaida: what(): invalid special open parenthesis

bool failoAtidarymas(const string& failoPasirinkimas) {
    ifstream failas(failoPasirinkimas);
    return failas.good();
}

string tvarkomeZodzius(const string& zodis) {
    regex neZodziuDalis("[^\\w]");
    string tinkamasZodis = regex_replace(zodis, neZodziuDalis, " ");
    transform(tinkamasZodis.begin(), tinkamasZodis.end(), tinkamasZodis.begin(), ::tolower);
    return tinkamasZodis;
}

bool ieskomeURL(const string& zodis) {
    regex url("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?");
    return regex_match(zodis, url);
}

void zodziuIrasymasSarase(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius) {
    if (zodis.empty())
        return;

    auto ieskome = sarasas.find(zodis);

    if (ieskome == sarasas.end()) {
        vector<int> eilutesSk;
        eilutesSk.push_back(eilutesSkaicius);
        sarasas[zodis] = eilutesSk;
    } else {
        vector<int>& eilutesSk = ieskome->second;
        if (eilutesSkaicius != eilutesSk.back()) {
            eilutesSk.push_back(eilutesSkaicius);
        }
    }
}

void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, vector<string>& url) {
    ifstream failas(failoPasirinkimas);
    string eilute;
    int eilutesSkaicius = 0;

    while (getline(failas, eilute)) {
        eilutesSkaicius++;
        istringstream in(eilute);
        string zodis;
        while (in >> zodis) {
            bool arYraSkaicius = any_of(zodis.begin(), zodis.end(), ::isdigit);
            if (ieskomeURL(zodis)) {
                url.push_back(zodis);
            } else if (!arYraSkaicius) { 
                string tinkamasZodis = tvarkomeZodzius(zodis);
                istringstream irasomeTikTinkamusZodzius(tinkamasZodis);
                while (irasomeTikTinkamusZodzius >> zodis) {
                    zodziuIrasymasSarase(zodis, sarasas, eilutesSkaicius);
                }
            }
        }
    }
}

void irasymasIFaila(const map<string, vector<int>>& sarasas, const vector<string>& url) {
    ofstream rezultatas("rezultatas.txt");
    if (!rezultatas.good()) {
        cout << "Failo nepavyko sukurti." << endl;
        return;
    }

    rezultatas << "Buvo rasti tokie URL: " << endl;
    for (const auto& urls : url) {
        rezultatas << urls << endl;
    }

    if (!sarasas.empty()) {
        rezultatas << left << setw(20) << "Zodziai:" << setw(21) << " Zodziu kiekis:" <<  "Zodziai yra tokiose eilutese:" << endl;
        rezultatas << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        for (const auto& i : sarasas) {
            if (i.second.size() > 1) {
                rezultatas << left << setw(20) << i.first << setw(7) << "|" << setw(7) << i.second.size() << setw(7) << "|";

                for (int j : i.second) {
                    rezultatas << setw(4) << j;
                }

                rezultatas << endl;
            }
        }
    }

    rezultatas.close();
}

int  main() {

    string failoPasirinkimas = "text.txt";

    if (!failoAtidarymas(failoPasirinkimas)) {
        cout << "Nepavyko atidaryti failo: " << failoPasirinkimas << endl;
        return 0;
    }

    map<string, vector<int>> sarasoIsvedimas;
    vector<string> url;

    failoSkaitymas(failoPasirinkimas, sarasoIsvedimas, url);
    irasymasIFaila(sarasoIsvedimas, url);

    cout << "Rezultatas gautas, ji perziureti galima sukurtame faile 'rezultatas.txt'." << endl;

    return 0;
}