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

template <typename... Args>
vector<string> DataManager::queryColumns(string nameColumn, Args... args) {
    vector<string> columns;
    columns.push_back(nameColumn);
    vector<string> nextColumns = queryColumns(args...);
    columns.insert(columns.end(), nextColumns.begin(), nextColumns.end());
    return columns;
}

vector<string> DataManager::queryTables(string nameRelation, string column) {
    string lineSquema;
    string lineData;
    vector<string> elements;
    ifstream fileInput(esquemas);
    ifstream fileData(nameRelation);
    string line;
    int pos;
    int posColumn = -1;
    cout << "Buscando el Esquema para la Relacion: " << nameRelation << endl;

    while (getline(fileInput, lineSquema)) {
        istringstream lineSquemaStream(lineSquema);
        pos = lineSquema.find(nameRelation);
        string columnSquema;
        int columnPosition = 0;
        
        if (pos == 0) {
            cout << "Esquema encontrado: " << lineSquema << endl;
            while (getline(lineSquemaStream, columnSquema, '#')) {
                if (columnSquema == column) {
                    posColumn = columnPosition;
                    cout << "Columna encontrada: " << column << " en la posicion " << posColumn << endl;
                    break;
                }
                if (pos % 2 != 0) {
                    columnPosition++;
                }
                pos++;
            }
            if (posColumn != -1) {
                break;
            }
        }
    }

    if (posColumn == -1) {
        cout << "Error, no se pudo encontrar la columna " << column << " en la relacion " << nameRelation << endl;
        return elements;
    }

    cout << "Leyendo los datos de la relacion: " << nameRelation << endl;

    int posData = 0;

    while (getline(fileData, lineData)) {
        stringstream ss(lineData);
        string value;
        while (getline(ss, value, '#')) {
            if (posData == posColumn) {
                elements.push_back(value);
                cout << "Valor encontrado: " << value << endl;
            }
            posData++;
        }
        posData = 0;
    }

    fileInput.close();
    fileData.close();

    cout << "Resultados obtenidos: " << endl;

    for (const auto& elem : elements) {
        cout << elem << endl;
    }

    if (elements.empty()) {
        cout << "No se encontraron datos para la consulta." << endl;
    }

    return elements;
}

void DataManager::mixData(vector<vector<string>> data) {
    int dataSize = data[0].size();
    int aux = 0;

    while (aux < dataSize) {
        for (int i = 0; i < data.size(); i++) {
            cout << data[i][aux] << endl;
            if (i < data.size() - 1) {
                cout << "\t#\t";
            }
            cout << endl;
            aux++;
        }
    }
}

void DataManager::queryTablesFinal(string nameRelation, vector<string> columns) {
    vector<vector<string>> data;

    for (int i = 0; i < columns.size(); i++) {
        cout << columns[i];
        if (i < columns.size() - 1) {
            cout << "\t#\t";
            data.push_back(queryTables(nameRelation, columns[i]));
        }
    }

    cout << endl;
    mixData(data);
}

void DataManager::where (string relation, string dataString, string symbol, int compare) {
    string lineSquema;
    ifstream nameRelation(esquemas);
    int pos;
    int posColumnData = -1;
    vector<string> elements;

    cout << "Buscando el Esquema para la Relacion: " << relation << endl;

    while (getline(nameRelation, lineSquema)) {
        string wordLineSquema;
        istringstream lineSquemaStream(lineSquema);
        pos = lineSquema.find(relation);
        int posColumn = -1;

        if (pos == 0) {
            cout << "Esquema encontrado:" << lineSquema << endl;
            while (getline(lineSquemaStream, wordLineSquema, '#')) {
                posColumn++;
                if (wordLineSquema == dataString) {
                    posColumnData = posColumn;
                    cout << "Columna encontrada para " << dataString << ": " << posColumnData << endl;
                }
            }
            break;
        }
    }

    if (posColumnData == -1) {
        cout << "Error, no se encontro la columna " << dataString << " en la relacion " << relation << endl;
        return;
    }
    
    nameRelation.close();
    cout << "Buscando datos en la relacion: " << relation << endl;
    posColumnData--;
    string lineRelation;
    ifstream data(relation);

    while (getline(data, lineRelation)) {
        string wordLineRelation;
        istringstream lineRelationStream(lineRelation);
        int posRelation = 0;

        while (getline(lineRelationStream, wordLineRelation, '#')) {
            if (posRelation == posColumnData) {
                bool match = false;
                int value = stoi(wordLineRelation);

                if (symbol == ">") {
                    match = value > compare;
                }
                else if (symbol == ">=") {
                    match = value >= compare;
                }
                else if (symbol == "<") {
                    match = value < compare;
                }
                else if (symbol == "<=") {
                    match = value <= compare;
                }
                else if (symbol == "==") {
                    match = value == compare;
                }
                else if (symbol == "!=") {
                    match = value != compare;
                }
                else {
                    cout << "Error, el operador no es soportado: " << symbol << endl;
                    return;
                }

                if (match) {
                    elements.push_back(lineRelation);
                    cout << "Coincidencia encontrada: " << lineRelation << endl;
                }
            }
            posRelation++;
        }
    }

    data.close();

    cout << "Resultados encontrados:" << endl;
    for (const auto& elem : elements) {
        cout << elem << endl;
    }

    if (elements.empty()) {
        cout << "No se encontraron coincidencias para la consulta." << endl;
    }
}