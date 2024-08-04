#ifndef _DATAMANAGER_
#define _DATAMANAGER_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cctype>
#include <cmath>
using namespace std;

class DataManager {
    public:
        static string determinateTypeOfData(const string& value);
        static string toLowerCase(string str);
        static string capitalize(string& str);
        static vector<string> getTypeFromLine(string line);
        static vector<string> split(string str, char delimiter);
        static void queryData(string nameRelation);
        template <typename... Args>
        static vector<string> queryColumns(string nameColumn, Args... args);
        static vector<string> queryTables(string nameRelation, string column);
        static void mixData(vector<vector<string>> data);
        static void queryTablesFinal(string nameRelation, vector<string> columns);
        static void where(string relation, string dataString, string symbol, int compare);
        static void whereCondition(string relation, string dataString, string symbol, int compare, string sign, string nameNewRelation);
};

#endif