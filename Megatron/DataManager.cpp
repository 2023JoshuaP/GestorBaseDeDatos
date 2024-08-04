#include "DataManager.h"
#define esquemas "Esquemas"

string DataManager::determinateTypeOfData(const string& value) {
    if (value.empty()) {
        return "empty";
    }

    bool onlyDigits = true;
    bool decimalPoint = false;

    for (char c : value) {
        if (isdigit(c)) {
            continue;
        }
        else if (c == '.' && !decimalPoint) {
            decimalPoint = true;
        }
        else {
            onlyDigits = false;
            break;
        }
    }

    if (onlyDigits) {
        if (decimalPoint) {
            return "float";
        }
        else {
            return "int";
        }
    }
    else {
        return "string";
    }
}

string DataManager::toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {return tolower(c); });
    return str;
}

string DataManager::capitalize(string& str) {
    if (!str.empty()) {
        str[0] = toupper(str[0]);
        transform(str.begin(), str.end(), str.begin() + 1, [](unsigned char c) {return tolower(c); });
    }
    return str;
}

vector<string> DataManager::getTypeFromLine(string line) {
    vector<string> types;
    string value;
    stringstream ss(line);

    while (getline(ss, value, ';')) {
        types.push_back(determinateTypeOfData(value));
    }

    return types;
}

void DataManager::queryData(string nameRelation) {
    string lineSquema;
    vector<string> elements;
    ifstream fileInput(esquemas);
    string line;
    int pos;

    while (getline(fileInput, lineSquema)) {
        string wordLineSquema;
        istringstream lineSquemaStream(lineSquema);
        pos = lineSquema.find(lineSquema);
        if (pos == 0) {
            while (getline(lineSquemaStream, wordLineSquema, '#')) {
                if (pos > 0 && pos % 2 == 1) {
                    elements.push_back(wordLineSquema);
                }
                pos++;
            }
            break;
        }
    }

    int idx = 0;

    for (auto i : elements) {
        cout << i;
        if (idx < elements.size() - 1) {
            cout << "\t#\t";
            idx++;
        }
    }
    cout << endl;
    cout << "-----------------------------------------------" << endl;

    ifstream dataRelation(nameRelation);
    int idj = 0;

    while (getline(dataRelation, lineSquema)) {
        stringstream ss(lineSquema);
        while (getline(ss, lineSquema, '#')) {
            cout << lineSquema;
            if (idj < idx) {
                cout << "\t#\t";
                idj++;
            }
        }
        idj = 0;
        cout << endl;
    }
}

vector<string> DataManager::split(string str, char delimiter) {
    vector<string> res;
    istringstream ss(str);
    string tok;

    while (getline(ss, tok, delimiter)) {
        if (tok != "") {
            res.push_back(tok);
        }
    }

    return res;
}