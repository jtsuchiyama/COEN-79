#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include "mystring.h"   // Or use the Standard Library <string>

using std::cin;
using std::cout;
using std::endl;
using namespace coen79_lab5;

int main() {
    string first("mom");
    string third(" ");
    cout << "hoi\n";
    first += third;
    cout << "\n" << first << "\n";
}


