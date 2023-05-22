#include <iostream>

#include <cstdlib>
#include <string>

#include "ip_filtr.h"

using namespace std;

int main()
{
//    cout << "Hello World!" << endl;

    try
    {
        ip_filtr ip_pool;
        std::string line;
        while (std::getline(std::cin, line))
        {
            auto v = split(line, '\t');
            ip_pool.insert(v[0]);
        }

        ip_pool.printAll_IP(std::cout);

        ip_pool.printAll_IP(std::cout, 1);

        ip_pool.printAll_IP(std::cout, 46, 70);

        ip_pool.print_any(std::cout, 46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
