#ifndef SCHEMAMANAGER_H
#define SCHEMAMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cmath>
#include <vector>
#include "GlobalVariable.h"
#include "Pesos.h"
#include "DataManager.h"
using namespace std;

#define esquemas "Esquemas"
#define sectorSize 1000

class SchemaManager {
    public:
        static void createSquema(string nameRelation = "");
        static bool thereRelation(string relation);
        static void createRelation();
        static string findRelation(string nameRelation);
};

#endif