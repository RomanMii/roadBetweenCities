#include "map.h"


int main()
{
    Map m("miasta.txt");
    m.roadGenerator();
    cout<<"roads:"<<endl;
    m.build();
    m.printResultArray();
    m.capitalCity();
    m.printResultArray();
    m.shortestWayFromTo("Bialystok","Gdansk");
}
