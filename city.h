#ifndef CT
#define CT

using namespace std;

class city
{
public:
    double x;
    double y;
    string name;
    int id;
public:
    city(double x = 0, double y = 0, string name = "unknown", int id = -1)
        {this -> x = x;
        this -> y = y;
        this -> name = name;
        this -> id = id;}
    ~city() = default;
    friend ostream& operator<<(ostream& os, const city& Ct)
    {
        os<<Ct.id<<"; "<<Ct.x<<"; "<<Ct.y<<"; "<<Ct.name;
        return os;
    }
};

#endif // CT
