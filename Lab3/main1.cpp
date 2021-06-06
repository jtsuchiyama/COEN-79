#include <iostream>     // Provides cout and cin
#include "sequence1.h"  

using namespace std;
using namespace coen79_lab3;

void show_sequence(sequence display)
// Library facilities used: iostream
{
    cout << "\n";
    for (display.start( ); display.is_item( ); display.advance( ))
        cout << display.current( ) << "\n";
    cout << "The count is " << display.size() << ", and the mean is " << display.mean() << ".\n";
}

int main() {
    sequence test1; 
    test1.insert(12);
    sequence test2; 
    test2.insert(8);
    sequence test3;
    test3 = test1 + test2;
    show_sequence(test3);
    test1 += test2;
    show_sequence(test1);
}

