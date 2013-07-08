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
    //assert(n>0);
    while (n!=0) {
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
    int lastRead = 1;
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
        if(*x == 0){
            ++zeroCount;
        } else {
            zeroCount = 0;}
        ++length;
        lastRead = *x;
        ++x;}
    if(lastRead == 0){
        bool wasHere = false;
        for (int i = 0; i<length - zeroCount; ++i){
            ++xCopy;
            wasHere = true;}
        if(!wasHere)
            ++xCopy;
        return xCopy;
    }
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
        deque<int> shiftedProduct(1000,0);
        cpEnd = shift_left_digits(currentProduct.begin(),cpEnd,leftShift,shiftedProduct.begin());
        currentProduct.clear();
        rsEnd = plus_digits(runningSum.begin(),rsEnd,shiftedProduct.begin(),cpEnd,runningSum.begin());
        ++leftShift;
        ++b2;}
    for(deque<int>::iterator it = runningSum.begin();it!=rsEnd;++it){
        *x = *it;
        ++x;}
    return x;}

// --------------
// greater
// --------------

/**
 *
 */
template <typename II1, typename II2>
bool myCompare (II1 b1, II1 e1, II2 b2, II2 e2, unsigned int skip){
    bool moveNum = false;
    while(b1!=e1){
        if(skip == 0)
            moveNum = true;
        if(moveNum && *b1<*b2)
            return false;
        ++b1;
        if(!moveNum)
            --skip;
        if(moveNum)
            ++b2;
        if(b2 == e2)
            return true;}
    return(b2==e2);}
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
    deque<int> num(1000,0);
    deque<int> num2(1000,0); 
    deque<int> num4(1000,0);
    deque<int> num8(1000,0);
    deque<int> numRev(1000,0);
    deque<int> num2Rev(1000,0);
    deque<int> num4Rev(1000,0);
    deque<int> num8Rev(1000,0);
    deque<int> dividend(1000,0);
    deque<int> dividendRev(1000,0);

    int mul1[] = {1};
    int mul2[] = {2};
    int mul4[] = {4};
    int mul8[] = {8};
    
    deque<int>::iterator numEnd = multiplies_digits(mul1,mul1+1,b2,e2,num.begin()); 
    deque<int>::iterator num2End = multiplies_digits(mul2,mul2+1,b2,e2,num2.begin()); 
    deque<int>::iterator num4End = multiplies_digits(mul4,mul4+1,b2,e2,num4.begin());
    deque<int>::iterator num8End = multiplies_digits(mul8,mul8+1,b2,e2,num8.begin());
    std::reverse_copy(num.begin(),numEnd,numRev.begin());
    std::reverse_copy(num2.begin(),num2End,num2Rev.begin());
    std::reverse_copy(num4.begin(),num4End,num4Rev.begin());
    std::reverse_copy(num8.begin(),num8End,num8Rev.begin());
    unsigned int numSize = numEnd - num.begin();
    unsigned int num2Size = num2End - num2.begin();
    unsigned int num4Size = num4End - num4.begin();
    unsigned int num8Size = num8End - num8.begin();
    numRev.resize( numSize);
    num2Rev.resize(num2Size);
    num4Rev.resize(num4Size); 
    num8Rev.resize(num8Size);
   
    std::cout<<std::endl;
        for(deque<int>::iterator it = numRev.begin();it!=numRev.end();++it)
            std::cout<<*it<<" "; 
    std::cout<<std::endl;
        for(deque<int>::iterator it = num2Rev.begin();it!=num2Rev.end();++it)
            std::cout<<*it<<" ";
    std::cout<<std::endl;
        for(deque<int>::iterator it = num4Rev.begin();it!=num4Rev.end();++it)
            std::cout<<*it<<" ";
    std::cout<<std::endl;
        for(deque<int>::iterator it = num8Rev.begin();it!=num8Rev.end();++it)
            std::cout<<*it<<" ";
    deque<int>::iterator dividendEnd = multiplies_digits(mul1,mul1+1,b1,e1,dividend.begin()); 

    deque<int> runningSum(1000,0);
    deque<int>::iterator rsEnd = runningSum.begin();
    ++rsEnd;    

    while(true){
        int select = -1;
        unsigned int dividendSize = dividendEnd - dividend.begin();
        std::reverse_copy(dividend.begin(),dividendEnd,dividendRev.begin());
        dividendRev.resize(dividendSize);

        deque<int> shiftedNum(1000,0);
        deque<int>::iterator shiftEnd;
        
        std::cout<<std::endl;
        for(deque<int>::iterator it = dividendRev.begin();it!=dividendRev.end();++it)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
        for(deque<int>::iterator it = runningSum.begin();it!=rsEnd;++it)
            std::cout<<*it<<" ";
        std::cout<<std::endl;
        if(myCompare(dividendRev.begin(),dividendRev.end(),num4Rev.begin(),num4Rev.end(),num8Size - num4Size)){
            if(myCompare(dividendRev.begin(),dividendRev.end(),num8Rev.begin(),num8Rev.end(),num8Size - num8Size)){
                std::cout<<std::endl<<4<<std::endl;
                shiftEnd = shift_left_digits(num8.begin(),num8End,dividendSize - num8Size,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(100,0);
                deque<int>::iterator partialQEnd = shift_left_digits(mul8,mul8+1,dividendSize - num8Size,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
                select = 4;       
            } else {
                std::cout<<std::endl<<3<<std::endl;
                shiftEnd = shift_left_digits(num4.begin(),num4End,dividendSize - num4Size,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(100,0);
                deque<int>::iterator partialQEnd = shift_left_digits(mul4,mul4+1,dividendSize - num4Size,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
                select = 3;}
        } else {
            if(myCompare(dividendRev.begin(),dividendRev.end(),num2Rev.begin(),num2Rev.end(),num8Size - num2Size)){       
                std::cout<<std::endl<<2<<std::endl;
                shiftEnd = shift_left_digits(num2.begin(),num2End,dividendSize - num2Size,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(100,0);
                deque<int>::iterator partialQEnd = shift_left_digits(mul2,mul2+1,dividendSize - num2Size,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
                select = 2;
            } else if(myCompare(dividendRev.begin(),dividendRev.end(),numRev.begin(),numRev.end(),num8Size - numSize)) {
                std::cout<<std::endl<<1<<std::endl;
                shiftEnd = shift_left_digits(num.begin(),numEnd,dividendSize - numSize,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(100,0);
                deque<int>::iterator partialQEnd = shift_left_digits(mul1,mul1+1,dividendSize - numSize,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
                select = 1;
            } else {
                std::cout<<std::endl<<select<<std::endl;
                select = -1;
                break;}}
            std::cout<<std::endl<<select<<std::endl;}
    for(deque<int>::iterator it = runningSum.begin();it!=rsEnd;++it){
        *x = *it;
        ++x;}    
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
        
        typename C::const_iterator itFirst = lhs._integer.cbegin();
        typename C::const_iterator itSecond = rhs._integer.cbegin();

        while(itFirst!=lhs._integer.cend() && itSecond!=rhs._integer.cend()){
                if(*itFirst != *itSecond)
                    return false;
                ++itFirst;
                ++itSecond;}
        if(itFirst!=lhs._integer.cend())
            return false;
        if(itSecond!=rhs._integer.cend())
            return false;
        return true;}

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
        typename C::const_reverse_iterator itFirst = lhs._integer.crbegin();
        typename C::const_reverse_iterator itSecond = rhs._integer.crbegin();
        while(true){
            if(itFirst!=lhs._integer.crend() && itSecond!=rhs._integer.crend()){
                if(*itFirst<*itSecond)
                    return result;
                ++itFirst;
                ++itSecond;
            }else{
                if(itSecond!=rhs._integer.crend())
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
        if(rhs._sign)
            lhs<<"-";
        for(typename C::const_reverse_iterator rIt = rhs._integer.crbegin(); rIt!=rhs._integer.crend(); ++rIt)
            lhs<<*rIt;
        return lhs;}

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
                _sign = false;}
            if(value == 0){
                _integer.push_back(0);
            }else{
                while(value!=0){
                    _integer.push_back(value % 10);
                    value = value/10;}}
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
