// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <algorithm>
using namespace std;
// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    while (n) {
        *x = 0;
        ++x;
        --n;}
    while (b != e) {
        *x = *b;
        ++x;
        ++b;}
    return x;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    while (n) {
        ++b;
        --n;}
    while(b!=e) {
        *x = *b;
        ++b;
        ++x;} 
    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    unsigned int carry = 0;
    
    {
        II1 b1Copy = b1;
        II2 b2Copy = b2;

        if(*b1Copy == 0 && ++b1Copy == e1){
            while(b2!=e2){
                *x = *b2;
                ++b2;
                ++x;}
            return x;}
        if(*b2Copy == 0 && ++b2Copy == e2){
            while(b1!=e1){
                *x = *b1;
                ++b1;
                ++x;}
            return x;}}
    while(true){
        int result = 0;
        if(b1 != e1 && b2 != e2){
            result = carry + *b1 + *b2;
            *x = result % 10;
            ++x;
            ++b1;
            ++b2;
        }else if(b1 == e1 && b2 != e2){
            result = carry + *b2;
            *x = result % 10;
            ++x;
            ++b2;
        }else if(b2 == e2 && b1 != e1){
            result = carry + *b1;
            *x = result % 10;
            ++x;
            ++b1;
        } else {
            if(carry > 0){
                *x = carry;
                ++x;}
            break;
        }
        carry = result/10;}
    return x;}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {    
    unsigned int borrow = 0;
    
    {
        II2 b2Copy = b2;
        if(*b2Copy == 0 && ++b2Copy == e2){
            while(b1!=e1){
                *x = *b1;
                ++b1;
                ++x;}
            return x;}}
    OI xCopy = x;
    int length = 0;
    int zeroCount = 0;
    while(true){
        if(b1 != e1 && b2 != e2){
            *x = *b1 - *b2 - borrow;
            ++b1;
            ++b2;
        }else if(b2 == e2 && b1 != e1){
            *x = *b1 - borrow;
            ++b1;
        } else {
            break;}
        if(*x<0){
            *x += 10;
            borrow = 1;
        } else {
            borrow = 0;}
        if(*x == 0)
            ++zeroCount;
        ++length;
        ++x;}
    if(zeroCount == length){
        *xCopy = 0;
        return ++xCopy;}
    return x;}

// -----------------
// multiply_digit
// -----------------

/**
 *
 *
 *
 */

template <typename II1, typename OI>
OI multiply_digit (II1 b1, II1 e1, int digit, OI x){
    unsigned int table [9][9] = {{1,2,3,4,5,6,7,8,9},
        {2,4,6,8,10,12,14,16,18},
        {3,6,9,12,15,18,21,24,27},
        {4,8,12,16,20,24,28,32,36},
        {5,10,15,20,25,30,35,40,45},
        {6,12,18,24,30,36,42,48,54},
        {7,14,21,28,35,42,49,56,63},
        {8,16,24,32,40,48,56,64,72},
        {9,18,27,36,45,54,63,72,81}};
    unsigned int carry = 0;
    std::vector<int> resultVec;
    while(b1!=e1){
         unsigned int tempResult = carry + (*b1 == 0? 0 :table[digit - 1][*b1 - 1]);
         *x = tempResult % 10;
         carry = tempResult/10;
         ++x;
         ++b1;}
    if(carry>0){
        *x = carry;
        ++x;}
    return x;}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    {
        II1 b1Copy = b1;
        II2 b2Copy = b2;
        if((*b1Copy == 0 && ++b1Copy == e1) || (*b2Copy == 0 && ++b2Copy == e2)){
            *x = 0;
            ++x;
            return x;}}
    {
        II1 b1Copy = b1;
        II2 b2Copy = b2;
        if(*b1Copy == 1 && ++b1Copy == e1){
            while(b2!=e2){
                *x = *b2;
                ++b2;
                ++x;}
            return x;} 
        if(*b2Copy == 1 && ++b2Copy == e2){
            while(b1!=e1){
                *x = *b1;
                ++b1;
                ++x;}
            return x;}}
    deque<int> runningSum(1000,0);
    deque<int>::iterator rsEnd = runningSum.begin();
    ++rsEnd;
    unsigned int leftShift = 0;
    while(b2!=e2){
        if(*b2 == 0){
            ++leftShift;
            ++b2;
            continue;}
        deque<int> currentProduct(1000,0);
        deque<int>::iterator cpEnd = multiply_digit(b1,e1,static_cast<int>(*b2),currentProduct.begin());
        cpEnd = shift_left_digits(currentProduct.begin(),cpEnd,leftShift,currentProduct.begin());
        rsEnd = plus_digits(runningSum.begin(),rsEnd,currentProduct.begin(),cpEnd,runningSum.begin());
        ++leftShift;}
    for(deque<int>::iterator it = runningSum.begin();it!=rsEnd;++it){
        *x = *it;
        ++x;}
    return x;}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    return x;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        if(lhs._sign!=rhs._sign)
            return false;
        return !(lhs > rhs) && !(rhs > lhs);}

    // -----------
    // operator !=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        if(lhs._sign != rhs._sign)
            if(rhs._sign)
                return true;
        bool result = true;
        if(lhs._sign)
            result = !result;
        typename C::const_iterator itFirst = lhs._integer.cbegin();
        typename C::const_iterator itSecond = rhs._integer.cbegin();
        while(true){
            if(itFirst!=lhs._integer.cend() && itSecond!=rhs._integer.cend()){
                if(*itFirst>*itSecond)
                    return result;
                ++itFirst;
                ++itSecond;
            }else{
                if(itFirst!=lhs._integer.cend())
                    return result;
                break;
            }
        } 
        return !result;}

    // -----------
    // operator <=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        // <your code>
        return lhs << "0";}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * does NOT modify the argument
     * <your documentation>
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * does NOT modify the argument
     * <your documentation>
     * @throws invalid_argument if (x == 0) && (e == 0)
     * @throws invalid_argument if (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        C _integer;
        bool _sign; //true -> negative

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            if(value<0){
                _sign = true;
                value *= -1;
            } else {
                _sign = false;
            }

            if(value == 0){
                _integer.push_back(static_cast<T>(0));
            }else{
                while(value!=0){
                    _integer.push_back(static_cast<T>(value % 10));
                    value = value/10;}}
            std::reverse(_integer.begin(),_integer.end());
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            string::const_iterator vBegin = value.cbegin();
            string::const_reverse_iterator vRevBegin = value.crbegin();
            string::const_reverse_iterator vRevEnd = value.crend();

            if(*vBegin == '-'){
                _sign = true;
                ++vBegin;
                --vRevEnd;
            } else {
                _sign = false;}
            
            for(;vRevBegin!=vRevEnd; ++vRevBegin){
                T digit = static_cast<T>(*vRevBegin) - '0';
                    if(!(digit>=0 && digit<=9)) 
                        throw std::invalid_argument("Integer::Integer()");
                   _integer.push_back(digit);}
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            Integer negateInt = *this;
            negateInt._sign = !negateInt._sign; 
            return negateInt;}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            // <your code>
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer& pow (int e) {
            // <your code>
            return *this;}};

#endif // Integer_h
