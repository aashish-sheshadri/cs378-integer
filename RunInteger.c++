// -------------------------------
// projects/integer/RunInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall Integer.c++ RunInteger.c++ -o RunInteger
    % valgrind RunInteger > RunInteger.out

To configure Doxygen:
    % doxygen -g
That creates the file "Doxyfile".
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    % doxygen Doxyfile
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <deque>    // deque

#include "Integer.h"
#include <ctime>

// ----
// main
// ----

int main () {
    using namespace std;
    
    clock_t t1, t2;
    cout << "RunInteger.c++" << endl << endl;
    
    // less than 300 ms without valgrind
    // less than  15  s with    valgrind
    cout << "*** 20th Mersenne prime: 1,332 digits ***" << endl << endl;
    t1 = clock();
    {
    const Integer<int> n = Integer<int>(2).pow(4423) - 1;
    cout << "2^4423 - 1 = " << n << endl << endl;
    }
    t2 = clock();
    std::cout<<"\n"<<"Time taken: "<<(static_cast<float>(t2)-static_cast<float>(t1))/static_cast<float>(CLOCKS_PER_SEC);
    t1 = clock();
    {
    const Integer< int, std::deque<int> > n = Integer< int, std::deque<int> >(2).pow(4423) - 1;
    cout << "2^4423 - 1 = " << n << endl << endl;
    }
    t2 = clock();
    std::cout<<"\n"<<"Time taken: "<<(static_cast<float>(t2)-static_cast<float>(t1))/static_cast<float>(CLOCKS_PER_SEC);
    // --------------------------
    // extra credit (5 bonus pts)
    // --------------------------

    // less than 4 min without valgrind
    // don't run with valgrind
    cout << "*** 30th Mersenne prime: 39,751 digits ***" << endl << endl;
    t1 = clock();
    {
    const Integer<int> n = Integer<int>(2).pow(132049) - 1;
    cout << "2^132049 - 1 = " << n << endl << endl;
    }
    t2 = clock();
    std::cout<<"\n"<<"Time taken: "<<(static_cast<float>(t2)-static_cast<float>(t1))/static_cast<float>(CLOCKS_PER_SEC);
    cout << "Done." << endl;

    return 0;}
