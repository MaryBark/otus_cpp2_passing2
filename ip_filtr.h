#ifndef IP_FILTR_H
#define IP_FILTR_H


#include "tuplesIP.h"

// создаем тип данных с помщью кортежа, состоящий из 4 int
using IP_adress = std::tuple<int, int, int, int>;


class ip_filtr
{
public:
    ip_filtr();
    ~ip_filtr(){}

    void insert(const IP_adress& addr);
    void insert(const std::string& str);

    template <typename... Args>
    void printAll_IP(std::ostream& ostream, Args&&... args)
    {
        auto filterAll = [&](const auto& addr)
        {
            return CompareTuples<sizeof...(args)>::CompareAll(addr, std::make_tuple(args...));
        };
        loggerFiltered(ostream, filterAll);
    }

    template <typename... Args>
    void print_any(std::ostream& ostream, Args&&... args)
    {
        auto filterAny = [&](const auto& addr)
        {
            return CompareTuples<sizeof...(args)>::CompareAny(addr, std::make_tuple(args...));
        };
        loggerFiltered(ostream, filterAny);
    }


private:
    using IPadressConteiner = std::map<IP_adress, int, std::greater<IP_adress>>;
    IPadressConteiner container;

    void loggerFiltered(std::ostream& ostream, std::function<bool(IP_adress)> filter);
};


std::vector<std::string> split(const std::string &str, char d);

int version();

#endif // IP_FILTR_H
