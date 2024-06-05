#include "funkcija.h"

// Funkcija, tikrinanti ar pavyksta atidaryti faila
bool failoAtidarymas(const string& failoPasirinkimas) {
    ifstream failas(failoPasirinkimas);
    return failas.good();
}

// Funkcija, tvarkanti zodzius (pasalina ne zodzio dalis ir pavercia maz raidemis)
string tvarkomeZodzius(const string& zodis) {
    regex neZodziuDalis("[^\\w]");
    string tinkamasZodis = regex_replace(zodis, neZodziuDalis, " ");
    transform(tinkamasZodis.begin(), tinkamasZodis.end(), tinkamasZodis.begin(), ::tolower);
    return tinkamasZodis;
}

const unordered_set<string> neURLsarasas = {
    "jpg", "jpeg", "doc", "docx", "ppt", "pptx", "pdf", "xls", "xlsx", "zip", "gif", "txt", "exe", "png", "accdb", "svg", "obj"
};

// Funkcija, ieskanti ar zodis yra URL
bool ieskomeURL(const string& zodis) {
    regex url ("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    return regex_match(zodis, url);
}

// Funkcija, ieskanti zodziu su ALY
void ieskotiZodziusSuAly(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius) {
    size_t zodisSuAly = zodis.find("aly");
    if (zodisSuAly < zodis.size()) {
        zodziuIrasymasSarase(zodis, sarasas, eilutesSkaicius);
    }
}

// Funkcija, pridedanti zodi i sarasa ir nuorodanti kurioje vietoje jis randasi
void zodziuIrasymasSarase(const string& zodis, map<string, vector<int>>& sarasas, int eilutesSkaicius) {
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

// Zodziu nuskaitymas is failo
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, map<string, vector<int>>& ALYsarasas, vector<string>& url) {
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
                size_t zodisSuAly = zodis.find("aly");
                while (irasomeTikTinkamusZodzius >> zodis) {
                    if (zodisSuAly < zodis.size()) {
                    zodziuIrasymasSarase(zodis, ALYsarasas, eilutesSkaicius);
                } else {
                    zodziuIrasymasSarase(zodis, sarasas, eilutesSkaicius);
                }
                }
            }
        }
    }
}

// Rezultatai irasomi i naujas faila 'rezultatas.txt'
void irasymasIFaila(const map<string, vector<int>>& sarasas, map<string, vector<int>>& ALYsarasas, const vector<string>& url) {
    ofstream rezultatas("rezultatas.txt");
    if (!rezultatas.good()) {
        cout << "Failo nepavyko sukurti." << endl;
        return;
    }

    rezultatas << "Buvo rasti tokie URL: " << endl;
    for (const auto& urls : url) {
        rezultatas << urls << endl;
    }

    rezultatas << " " << endl;

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

    if (!ALYsarasas.empty()) {
        rezultatas << left << setw(20) << "Zodziai su 'aly':" << endl;
        rezultatas << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        for (const auto& i : ALYsarasas) {
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

int main() {

    string failoPasirinkimas = "text.txt";

    if (!failoAtidarymas(failoPasirinkimas)) {
        cout << "Nepavyko atidaryti failo: " << failoPasirinkimas << endl;
        return 0;
    }

    map<string, vector<int>> ALYsarasoIsvedimas;
    map<string, vector<int>> sarasoIsvedimas;
    vector<string> url;

    failoSkaitymas(failoPasirinkimas, sarasoIsvedimas, ALYsarasoIsvedimas, url);
    irasymasIFaila(sarasoIsvedimas, ALYsarasoIsvedimas, url);

    cout << "Rezultatas gautas, ji perziureti galima sukurtame faile 'rezultatas.txt'." << endl;

    return 0;
}

