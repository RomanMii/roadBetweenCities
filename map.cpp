#include "map.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

Map::Map(string source)
{
    getCities(source);
}

Map::~Map()
{
    for(int i = 0; i < numberOfCities; ++i) {
        delete [] roads[i];
    }
    delete [] roads;

    for(int i = 0; i < numberOfCities; ++i) {
        delete [] shortestWay[i];
    }
    delete [] shortestWay;
}


double Map::value(double x, double y, double _x, double _y)
{
    return sqrt(pow(_x - x,2) + pow((cos((x * 3.14)/180.0) * ( _y - y)),2)) * (40075.704 / 360.0);
}

void Map::getCities(string source)
{
ifstream citiesInfo(source);
    if (citiesInfo.is_open())
    {
        string str;
        while(getline(citiesInfo,str))
        {
            double x,y;
            string name;
            int id;
            size_t pos = str.find(" ");
            string x_ = str.substr(0,pos);
            stringstream numberx(x_);
            numberx >> x;
            int prev = pos+1;
            pos = str.find(" ", pos + 1);
            string y_ = str.substr(prev,pos - prev);
            stringstream numbery(y_);
            numbery >> y;
            name = str.substr(pos + 1, str.length() - pos + 1);
            id = numberOfCities;
            city c(x,y,name,id);
            cities.push_back(c);
            numberOfCities++;
        }
        citiesInfo.close();
    }
}

void Map::roadGenerator()
{
    roads = new double*[numberOfCities];
    for(int i = 0; i < numberOfCities; ++i)
    {
        roads[i] = new double[numberOfCities];
    }
    for(auto i : cities)
    {
        for(auto j : cities)
        {
            roads[i.id][j.id] = value(i.x,i.y,j.x,j.y);
        }
    }
}

int Map::minKey(double key[], bool mstSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < numberOfCities; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void Map::build()
{
    int parent[numberOfCities];

    double key[numberOfCities];

    bool mstSet[numberOfCities];

    for (int i = 0; i < numberOfCities; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numberOfCities - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < numberOfCities; v++)
            if (roads[u][v] && mstSet[v] == false && roads[u][v] < key[v])
                parent[v] = u, key[v] = roads[u][v];
    }


    //resulting array
    shortestWay = new double*[numberOfCities];
    for(int i = 0; i < numberOfCities; ++i)
    {
        shortestWay[i] = new double[numberOfCities];
    }

    for(int i =0; i < numberOfCities; ++i)
    {
        for(int j =0; j < numberOfCities; ++j)
        {
            shortestWay[i][j] = 0;
        }
    }

    //print
    for (int i = 1; i < numberOfCities; i++)
    {
        fullPrice+=roads[i][parent[i]];
        list<city>::iterator from = cities.begin();
        advance(from,parent[i]);
        list<city>::iterator to = cities.begin();
        advance(to,i);
        shortestWay[parent[i]][i] = roads[i][parent[i]];
        shortestWay[i][parent[i]] = roads[i][parent[i]];
        cout<<from->name<<" - "<<to->name<<"   \t"<<roads[i][parent[i]]<<" \n";
    }
    cout<<"full price = "<<fullPrice<<endl;
}

void Map::printResultArray()
{
    cout<<"\nresulting array \n";
    for(int i =0; i < numberOfCities; ++i)
    {
        for(int j =0; j < numberOfCities; ++j)
        {
            cout<<shortestWay[j][i]<<"\t";
        }
        cout<<endl;
    }
}


void Map::capitalCity()
{
    list<city>::iterator from = cities.begin();
    list<city>::iterator to = cities.begin();
    for(int i = 0; i < numberOfCities; ++i)
    {
        //int x =
        shortestWay[i][0] = shortestWay[0][i] = value(from -> x, from -> y, to -> x, to -> y);
        advance(from,1);
    }
}

void Map::shortestWayFromTo(string _a, string _b)
{
    // input data
    const int MAX = 9999;
    int a,b;
    for(auto v: cities)
    {
        if(v.name == _a)
            a = v.id;
        else if(v.name == _b)
            b = v.id;
    }

    double dist[numberOfCities]; // The output array.
    bool sptSet[numberOfCities]; // sptSet[i] will be true if vertex i is included in shortest
    for (int i = 0; i < numberOfCities; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[a] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numberOfCities - 1; count++)
    {
        int u = minKey(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < numberOfCities; v++)
        {
            if (!sptSet[v] && shortestWay[u][v] && dist[u] != INT_MAX && dist[u] + shortestWay[u][v] < dist[v])
            {
                dist[v] = dist[u] + shortestWay[u][v] * 1.0;
            }
        }
    }

    //decoder
    list<int> road;
    double weight = dist[b];
    int end = b;
    road.push_front(b);
    while(end != a)
    {
        for(int i = 0; i < numberOfCities; ++i)
        {
            if(shortestWay[i][end] != 0)
            {
                double temp = weight - shortestWay[i][end];
                double g = round(temp* 1000.)/1000.;
                double h = round(dist[i]* 1000.)/1000.;
                if (g == h)
                {
                    weight = temp;
                    end = i;
                    road.push_front(i);
                }
            }
        }
    }

    //print
    cout<<"Distance from "<<_a<<" to "<<_b<<" - "<<dist[b]<<endl;
    cout<<"road: ";
    for(auto v : road)
    {
        list<city>::iterator cityName = cities.begin();
        advance(cityName,v);
        cout<<cityName->name<<" -> ";
    }cout<<endl;

}


