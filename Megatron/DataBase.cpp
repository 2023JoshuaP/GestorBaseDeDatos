#include "./DataBase.h"

void DataBase::init() {
    string nameRelation;
    string commands;
    string stringId;
    string operador;
    string separator;
    string nameNewRelation;
    int dataOperator;
    int idRegister;
    
    while (true) {
        cout << "-----------------------------------------------------" << endl;
        cout << "\t\t   Bienvenido a Megatron 3000\t\t" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Los comandos son:" << endl;
        cout << "1. create_squema" << endl;
        cout << "2. create_relation" << endl;
        cout << "3. consult_SELECT*FROM" << endl;
        cout << "4. consult_SELECT*FROM_" << endl;
        cout << "5. consult_SELECT" << endl;
        cout << "6. SEARCH" << endl;
        cout << "7. exit_program" << endl;
        cout << "Escriba el comando que va a realizar: " << endl;
        cin >> commands;

        if (commands == "create_squema") {
            SchemaManager::createSquema();
        }
        else if (commands == "create_relation") {
            SchemaManager::createRelation();
        }
        else if (commands == "consult_SELECT*FROM") {
            cout << "Nombre de la Relacion: ";
            cin >> nameRelation;
            DataManager::queryData(nameRelation);
        }
        else if (commands == "consult_SELECT*FROM_") {
            cout << "Nombre de la Relacion: ";
            cin >> nameRelation;
            cout << "WHERE (nombre columna)" << " ";
            cin >> stringId;
            cout << "Operador: ";
            cin >> operador;
            cout << "Numero de operador: ";
            cin >> dataOperator;
            cout << "Separador (NULL && |): ";
            cin >> separator;

            if (separator == "NULL") {
                cout << endl;
                DataManager::where(nameRelation, stringId, operador, dataOperator);
                cout << endl;
            }
            else if (separator == "|") {
                cout << endl;
                cout << "Nueva relacion: ";
                cin >> nameNewRelation;
                cout << endl;
                DataManager::whereCondition(nameRelation, stringId, operador, dataOperator, separator, nameNewRelation);
                cout << endl;
            }
        }
        else if (commands == "consult_SELECT") {
            vector<string> columns;
            string column;
            while (cin >> column) {
                cout << "Columnas? (string)" << endl;
                if (column == "FROM") {
                    break;
                }
                columns.push_back(column);
            }
            cin >> nameRelation;
            DataManager::queryTablesFinal(nameRelation, columns);
        }
        else if (commands == "SEARCH") {
            cout << "Se implementara mas adelante." << endl;
        }
        else if (commands == "exit_program") {
            break;
        }
        else {
            cout << "El comando no es valido." << endl;
        }
    }
}