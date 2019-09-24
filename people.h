#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>


class People
{
public:
    People();
    std::string imie;
    std::string nazwisko;
    std::string getImie();
    std::string getNazwisko();
    int lat;
};

#endif // PEOPLE_H
