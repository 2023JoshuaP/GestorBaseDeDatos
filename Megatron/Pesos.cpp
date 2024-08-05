#include "Pesos.h"

int Pesos::calculateWeight(vector<string> elements) {
    int weight = 0;
    for (int i = 0; i < elements.size(); i++) {
        weight += elements[i].size();
    }
    return weight * 8;
}

int Pesos::sectorWeight(string fileSector) {
    ifstream file(fileSector);
    string line;
    vector<string> elements;

    while (getline(file, line)) {
        vector<string> words = DataManager::split(line, '#');
        for (int i = 0; i < words.size(); i++) {
            elements.push_back(words[i]);
        }
    }
    return calculateWeight(elements);
}

bool Pesos::verificateWeight(string fileSector, string newRegister) {
    vector<string> elements = DataManager::split(newRegister, '#');
    int registerSize = calculateWeight(elements);
    return sectorWeight(fileSector) + registerSize <= sectorSize;
}