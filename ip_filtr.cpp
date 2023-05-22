#include <iostream>
#include <algorithm>

#include "version.h"
#include "ip_filtr.h"


//bool Compare(int value, int data)
//{
//    return value == data;
//}

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_filtr::ip_filtr()
{}


void ip_filtr::insert(const IP_adress& addr)
{
    ++container[addr];
}

void ip_filtr::insert(const std::string& str)
{
    auto v = split(str, '.');
    auto tuple = MakeTupleFromVector<IP_adress>::Make(v);
    insert(tuple);
}

void ip_filtr::loggerFiltered(std::ostream& ostream, std::function<bool(IP_adress)> filter)
{
    for(const auto& ip_quantity : container)
    {
        if(!filter(ip_quantity.first))
            continue;

        for(int i = 0; i < ip_quantity.second; i++)
        {
            PrintTuple(ostream, ip_quantity.first);
            ostream << std::endl; //// вот почему сюда нужно подключать библиотеку, когда она уже сидит в ашнике!!!!
        }
    }
}

int version()
{
    return PROJECT_VERSION_PATCH;
}
