#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cmath>
#include <filesystem>
#include <string>
#include <vector>
#include "SchemaManager.h"
using namespace std;

#define esquemas "Esquemas"

class DataBase {
    public:
        static void init();
};

#endif