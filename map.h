#ifndef MP
#define MP

#include <iostream>
#include <utility>
#include <list>
#include <bits/stdc++.h>
#include "city.h"

//# define INF 0x3f3f3f3f

class Map
{
    string source;
    int numberOfCities = 0;
    list<city> cities;
    double** roads;
    double** shortestWay;
    double fullPrice = 0;
public:
    Map(string);
    ~Map();
    double value(double,double,double,double);
    void getCities(string);
    void roadGenerator();
    int minKey(double key[], bool mstSet[]);
    void build();
    void capitalCity();
    void printResultArray();
    void shortestWayFromTo(string,string);
};
#endif // MP
