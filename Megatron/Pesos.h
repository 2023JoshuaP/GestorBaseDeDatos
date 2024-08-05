#ifndef PESOS_H
#define PESOS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "./DataManager.cpp"
using namespace std;

#define sectorSize 1000

class Pesos {
    public:
        static int calculateWeight(vector<string> elements);
        static int sectorWeight(string fileSector);
        static bool verificateWeight(string fileSector, string newRegister);
        static void weightDisk(int cantPlatos, int cantSuperficie, int cantPistas, int cantSectores);
};

#endif