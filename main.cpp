#include "core/application.h"

#include <iostream>

using namespace std;

int main()
{
    int result = 0;

    try {
        Application app;
        result = app.exec();
    } catch (std::exception e) {
        std::cerr << e.what();
    }

    return result;
}
