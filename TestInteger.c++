// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Integer.c++ TestInteger.c++ -o TestInteger -lcppunit -ldl
    % valgrind TestInteger > TestInteger.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <vector>
#include <deque>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {
    // -----------------
    // shift_left_digits
    // -----------------

    void test_shift_left_digits_1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {0, 0, 2, 3, 4};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
    
    void test_shift_left_digits_2 () {
        const std::vector<int> a (3,3);
        std::vector<int> b (2,0);
        b.push_back(3);
        b.push_back(3);
        b.push_back(3);
        std::vector<int> x(10,0);  
        const std::vector<int>::iterator p = shift_left_digits(a.begin(), a.end(), 2, x.begin());
        CPPUNIT_ASSERT((p - x.begin()) == 5);
        CPPUNIT_ASSERT(std::equal(x.begin(), p, b.begin()));}
     
    void test_shift_left_digits_3 () {
        const std::deque<int> a (3,3);
        std::deque<int> b (2,0);
        b.push_back(3);
        b.push_back(3);
        b.push_back(3);
        std::deque<int> x(10,0);  
        const std::deque<int>::iterator p = shift_left_digits(a.begin(), a.end(), 2, x.begin());
        CPPUNIT_ASSERT(std::equal(x.begin(), p, b.begin()));}
    
    void test_shift_left_digits_4 () {
        const int a[] = {1};
        const int b[] = {1};
              int x[10];
        const int* p = shift_left_digits(a, a + 1, 0, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
    
    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits_1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
    
    void test_shift_right_digits_2 () {
        const std::vector<int> a (3,3);
        std::vector<int> b (1,3);
        std::vector<int> x(10,0);  
        const std::vector<int>::iterator p = shift_right_digits(a.begin(), a.end(), 2, x.begin());
        CPPUNIT_ASSERT((p - x.begin()) == 1);
        CPPUNIT_ASSERT(std::equal(x.begin(), p, b.begin()));}
     
    void test_shift_right_digits_3 () {
        const std::deque<int> a (3,3);
        std::deque<int> b (1,3);
        std::deque<int> x(10,0);  
        const std::deque<int>::iterator p = shift_right_digits(a.begin(), a.end(), 2, x.begin());
        CPPUNIT_ASSERT(std::equal(x.begin(), p, b.begin()));}
 

    // -----------
    // plus_digits
    // -----------

    void test_plus_digits_1 () {
        const int a[] = {4, 3, 2};
        const int b[] = {7, 6, 5};
        const int c[] = {1, 0, 8};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
   
    void test_plus_digits_2 () {
        const int a[] = {4, 3, 2, 1};
        const int b[] = {7, 6, 5};
        const int c[] = {1, 0, 8, 1};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
   
    void test_plus_digits_3 () {
        const int a[] = {4, 3, 2};
        const int b[] = {7, 6, 5, 1};
        const int c[] = {1, 0, 8, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));} 
    
    void test_plus_digits_4 () {
        const int a[] = {9, 9, 9};
        const int b[] = {0};
        const int c[] = {9, 9, 9};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    void test_plus_digits_5 () {
        const int a[] = {1};
        deque<int> b(1000,0);
        deque<int>::iterator itB = b.begin();
        ++itB;
        deque<int> c(1000,1);
        deque<int> x(1000,0);
        deque<int>::iterator p = plus_digits(a, a + 1, b.begin(), itB, x.begin());
        CPPUNIT_ASSERT(p - x.begin() == 1);
        CPPUNIT_ASSERT(std::equal(x.begin(), p, c.begin()));}
    
    // ------------
    // minus_digits
    // ------------

    void test_minus_digits_1 () {
        const int a[] = {1, 0, 8};
        const int b[] = {7, 6, 5};
        const int c[] = {4, 3, 2};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    void test_minus_digits_2 () {
        const int a[] = {0, 0, 1};
        const int b[] = {9, 9};
        const int c[] = {1};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));} 
    
    void test_minus_digits_3 () {
        const int a[] = {0, 0, 1};
        const int b[] = {0, 0, 1};
        const int c[] = {0};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    void test_minus_digits_4 () {
        const int a[] = {0, 0, 0, 1};
        const int b[] = {1};
        const int c[] = {9, 9, 9};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------------
    // multiply_digit
    // -----------------
    
    void test_multiply_digit_1 () {
        const int a[] = {4, 3, 2};
        const int b = 2;
        const int c[] = {8, 6, 4};
        int x[10];
        const int* p = multiply_digit(a, a + 3, b, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiply_digit_2 () {
        const int a[] = {4, 3, 2};
        const int b = 3;
        const int c[] = {2, 0, 7};
        int x[10];
        const int* p = multiply_digit(a, a + 3, b, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    void test_multiply_digit_3 () {
        const int a[] = {4, 3, 2};
        const int b = 9;
        const int c[] = {6, 0, 1, 2};
        int x[10];
        const int* p = multiply_digit(a, a + 3, b, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits_1 () {
        const int a[] = {4, 3, 2};
        const int b[] = {7, 6, 5};
        const int c[] = {8, 7, 6, 2, 3, 1};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits_2 () {
        const int a[] = {0};
        const int b[] = {5, 6, 7};
        const int c[] = {0};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits_3 () {
        const int a[] = {0,0,1};
        const int b[] = {9,9,9};
        const int c[] = {0, 0, 9, 9, 9};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    void test_multiplies_digits_4 () {
        const int a[] = {4, 3, 2};
        const int b[] = {7, 6, 5};
        const int c[] = {8, 7, 6, 2, 3, 1};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // --------------
    // myCompare
    // --------------
    
    void test_myCompare_1 () {
        const int a[] = {8, 7, 6, 2, 3, 1};
        const int b[] = {7, 6, 5};
        CPPUNIT_ASSERT(myCompare(a,a+6,b,b+3,0));}
    void test_myCompare_2 () {
        const int a[] = {1, 2, 3, 2, 3, 1};
        const int b[] = {7, 6, 5};
        CPPUNIT_ASSERT(!myCompare(a,a+6,b,b+3,0));}
    void test_myCompare_3 () {
        const int a[] = {8, 7, 6};
        const int b[] = {6, 5};
        CPPUNIT_ASSERT(myCompare(a,a+3,b,b+3,1));}

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits_1 () {
        const int a[] = {8, 7, 6, 2, 3, 1};
        const int b[] = {7, 6, 5};
        const int c[] = {4, 3, 2};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    void test_divides_digits_2 () {
        const int a[] = {8};
        const int b[] = {8};
        const int c[] = {1};
              int x[10];
        const int* p = divides_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits_3 () {
        const int a[] = {0, 0, 0, 0, 0, 1};
        const int b[] = {0, 0, 1};
        const int c[] = {0, 0, 0, 1};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
 
    void test_divides_digits_4 () {
        const int a[] = {8, 7, 6};
        const int b[] = {7, 6, 5};
        const int c[] = {1};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}   
    // -----------
    // constructor
    // -----------

    void test_constructor_1 () {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));}}

    void test_constructor_2 () {
        try {
            const Integer<int> x("2");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_3 () {
        try {
            const Integer<int> x(2);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_constructor_4 () {
        try {
            const Integer<int> x("-382");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    // ---
    // abs
    // ---

    void test_abs_1 () {
        try {
            Integer<int>  x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_2 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y ==  98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_3 () {
        try {
            Integer<int>  x = -9;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 9);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_abs_4 () {
        try {
            const Integer<int> x = 8765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == 8765);
            CPPUNIT_ASSERT(y == 8765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_5 () {
        try {
            Integer<int>  x = 8765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 8765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_abs_6 () {
        try {
            const Integer<int> x = -9;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -9);
            CPPUNIT_ASSERT(y ==  9);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // equal_to
    // --------

    void test_equal_to_1 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 98765);
            CPPUNIT_ASSERT(  98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to_2 () {
        try {
            const Integer<int> x = 0;
            const Integer<int> y = 0;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 0);
            CPPUNIT_ASSERT(  0 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 0));
            CPPUNIT_ASSERT(!(0 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_equal_to_3 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = -98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == -98765);
            CPPUNIT_ASSERT(  -98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != -98765));
            CPPUNIT_ASSERT(!(-98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // negation
    // --------

    void test_negation_1 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_negation_2 () {
        try {
            const Integer<int> x = 1;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_negation_3 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ------
    // output
    // ------

    void test_output_1 () {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_output_2 () {
        try {
            const Integer<int> x = -98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output_3 () {
        try {
            const Integer<int> x("-98765");
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int>       x = 2;
            const int          e = 8;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT( e == 8);
            CPPUNIT_ASSERT( x == 256);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_2 () {
        try {
            const Integer<int> x = 3;
            const int          e =  4;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 3);
            CPPUNIT_ASSERT(e ==  4);
            CPPUNIT_ASSERT(y == 81);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_pow_3 () {
        try {
            const Integer<int> x = 9;
            const int          e =  999;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 9);
            CPPUNIT_ASSERT(e ==  9);
            CPPUNIT_ASSERT(y == 387420489);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits_1);
    CPPUNIT_TEST(test_shift_left_digits_2);
    CPPUNIT_TEST(test_shift_left_digits_3);
    CPPUNIT_TEST(test_shift_right_digits_1);
    CPPUNIT_TEST(test_shift_right_digits_2);
    CPPUNIT_TEST(test_shift_right_digits_3);
    CPPUNIT_TEST(test_plus_digits_1);
    CPPUNIT_TEST(test_plus_digits_2);
    CPPUNIT_TEST(test_plus_digits_3);
    CPPUNIT_TEST(test_plus_digits_4); 
    CPPUNIT_TEST(test_plus_digits_5);
    CPPUNIT_TEST(test_minus_digits_1);
    CPPUNIT_TEST(test_minus_digits_2);
    CPPUNIT_TEST(test_minus_digits_3);
    CPPUNIT_TEST(test_minus_digits_4);
    CPPUNIT_TEST(test_multiply_digit_1);
    CPPUNIT_TEST(test_multiply_digit_2);
    CPPUNIT_TEST(test_multiply_digit_3);
    CPPUNIT_TEST(test_multiplies_digits_1);
    CPPUNIT_TEST(test_multiplies_digits_2);
    CPPUNIT_TEST(test_multiplies_digits_3);
    CPPUNIT_TEST(test_multiplies_digits_4);
    CPPUNIT_TEST(test_myCompare_1);
    CPPUNIT_TEST(test_myCompare_2);
    CPPUNIT_TEST(test_myCompare_3);
    CPPUNIT_TEST(test_divides_digits_1);
    CPPUNIT_TEST(test_divides_digits_2);
    CPPUNIT_TEST(test_divides_digits_3);
    CPPUNIT_TEST(test_divides_digits_4);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_abs_3);
    CPPUNIT_TEST(test_abs_4);
    CPPUNIT_TEST(test_abs_5);
    CPPUNIT_TEST(test_abs_6);
    CPPUNIT_TEST(test_equal_to_1);
    CPPUNIT_TEST(test_equal_to_2);
    CPPUNIT_TEST(test_equal_to_3);
    CPPUNIT_TEST(test_negation_1);
    CPPUNIT_TEST(test_negation_2);
    CPPUNIT_TEST(test_negation_3);
    CPPUNIT_TEST(test_output_1);
    CPPUNIT_TEST(test_output_2);
    CPPUNIT_TEST(test_output_3);
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    cout << "TestInteger.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestInteger::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
