#include "./SchemaManager.h"

void SchemaManager::createSquema(string nameRelation) {
    DataManager dataManager;
    string fileCSV;
    
    if (nameRelation == "") {
        cout << "Ingresar nombre de la relacion: ";
        cin >> nameRelation;
    }
    else {
        cout << "La relacion se creara: " << nameRelation << endl;
    }

    nameRelation = dataManager.capitalize(nameRelation);
    cout << "Ingresar el nombre del archivo CSV para crear el esquema: ";
    cin >> fileCSV;
    ofstream fileSquemas(esquemas, ios::app);
    ifstream fileInput(fileCSV);

    if (!fileInput.is_open()) {
        cerr << "Error al abrir el archivo CSV." << endl;
        return;
    }

    fileSquemas << nameRelation;
    string line;

    if (getline(fileInput, line)) {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            fileSquemas << "#";
            fileSquemas << value;
        }
    }

    fileSquemas << endl;
    fileInput.close();
    fileSquemas.close();

    cout << "Creacion del Esquema correctamente." << endl;
}

bool SchemaManager::thereRelation(string relation) {
    ifstream fileInput(esquemas);
    string line;

    while (getline(fileInput, line, '#')) {
        if (line == relation) {
            return true;
        }
    }
    
    return false;
}

void SchemaManager::createRelation() {
    DataManager dataManager;
    string nameFileRelation;
    string nameRelation;

    cout << "Ingresar el nombre de la Relacion: ";
    cin >> nameRelation;

    if (!thereRelation(dataManager.capitalize(nameRelation))) {
        cout << "La Relacion no existe: " << nameRelation << endl;
        createSquema(nameRelation);
    }

    cout << "Ingresar el archivo CSV para extraer la data: ";
    cin >> nameFileRelation;
    ifstream fileInput(nameFileRelation);

    if (!fileInput.is_open()) {
        cerr << "Error al abrir el archivo CSV." << endl;
        return;
    }

    string nameFileOutput = dataManager.capitalize(nameRelation);
    bool validate = true;

    if (validate == true) {
        ofstream fileOutput(nameFileOutput, ios::app);
        string line;
        bool firstLine = true;
        while (getline(fileInput, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            int countCommas = count(line.begin(), line.end(), ',');
            int countHashtag = 0;
            stringstream ss(line);
            string value;
            string lineRelation = "";
            while (getline(ss, value, ',')) {
                fileOutput << value;
                lineRelation += value;
                if (countHashtag < countCommas) {
                    fileOutput << "#";
                    lineRelation += "#";
                    countHashtag++;
                }
            }
            fileOutput << endl;
        }

        fileInput.close();
        fileOutput.close();
        cout << "La Relacion se ha creado correctamente." << endl;
    }
    else {
        cout << "La data no coincide con el esquema." << endl;
    }
}

string SchemaManager::findRelation(string nameRelation) {
    string lineSquema;
    ifstream fileInput(esquemas);

    while (getline(fileInput, lineSquema)) {
        if (lineSquema.find(nameRelation) != -1) {
            stringstream ss(lineSquema);
            int pos = 0;
            while (getline(ss, lineSquema, '#')) {
                if (pos > 0 && pos % 2 != 0) {
                    cout << lineSquema << '#';
                }
                pos += 1;
            }
            fileInput.close();
            return lineSquema;
        }
    }

    fileInput.close();
    return "No encontrado.";
}