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
    unsigned int size = 0;
    {
        II1 b1Copy = b1;
        II2 b2Copy = b2;
        while(b1Copy!=e1 && b2Copy!=e2){
            ++b1Copy;
            ++b2Copy;
            ++size;}
        while(b1Copy!=e1){
            ++b1Copy;
            ++size;}
        while(b2Copy!=e2){
            ++b2Copy;
            ++size;}}
    deque<int> runningSum(size,0);
    deque<int>::iterator rsEnd = runningSum.begin();
    ++rsEnd;
    unsigned int leftShift = 0;
    while(b2!=e2){
        if(*b2 == 0){
            ++leftShift;
            ++b2;
            continue;}
        deque<int> currentProduct(size);
        deque<int>::iterator cpEnd = multiply_digit(b1,e1,static_cast<int>(*b2),currentProduct.begin());
        deque<int> shiftedProduct(size);
        cpEnd = shift_left_digits(currentProduct.begin(),cpEnd,leftShift,shiftedProduct.begin());
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
    while(b1!=e1){
        if(skip != 0)
            return true;
        if(*b1<*b2){
            return false;
        }else if(*b1>*b2){
            return true;}
        ++b1;
        ++b2;
        if(b2 == e2)
            return true;}
    return false;}

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
    {
        II1 b1Copy = b1;
        II2 b2Copy = b2;
        assert(!(*b2Copy == 0 && ++b2Copy == e2));
        if((*b1Copy == 0 && ++b1Copy == e1) ){
            *x = 0;
            ++x;
            return x;}}
    {
        II2 b2Copy = b2; 
        if(*b2Copy == 1 && ++b2Copy == e2){
            while(b1!=e1){
                *x = *b1;
                ++b1;
                ++x;}
            return x;}}
    
    unsigned int size = 0;
    {
        II1 b1Copy = b1;
        II2 b2Copy = b2;
        while(b1Copy!=e1 && b2Copy!=e2){
            ++b1Copy;
            ++b2Copy;
            ++size;}
        while(b1Copy!=e1){
            ++b1Copy;
            ++size;}
        while(b2Copy!=e2){
            ++b2Copy;
            ++size;}}

    deque<int> num(size);
    deque<int> num2(size); 
    deque<int> num4(size);
    deque<int> num8(size);
    deque<int> numRev(size);
    deque<int> num2Rev(size);
    deque<int> num4Rev(size);
    deque<int> num8Rev(size);
    deque<int> dividend(size);
    deque<int> dividendRev(size);

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
    numRev.resize(numSize);
    num2Rev.resize(num2Size);
    num4Rev.resize(num4Size); 
    num8Rev.resize(num8Size);
    
    deque<int>::iterator dividendEnd = multiplies_digits(mul1,mul1+1,b1,e1,dividend.begin()); 

    deque<int> runningSum(size);
    runningSum.push_back(0);
    deque<int>::iterator rsEnd = runningSum.begin();
    ++rsEnd;    

    while(true){
        unsigned int dividendSize = dividendEnd - dividend.begin();
        std::reverse_copy(dividend.begin(),dividendEnd,dividendRev.begin());
        dividendRev.resize(dividendSize);

        deque<int> shiftedNum(size);
        deque<int>::iterator shiftEnd;
        if(dividendSize>=num4Size && myCompare(dividendRev.begin(),dividendRev.end(),num4Rev.begin(),num4Rev.end(),dividendSize==num4Size?0:num8Size - num4Size)){
            if(dividendSize>=num8Size && myCompare(dividendRev.begin(),dividendRev.end(),num8Rev.begin(),num8Rev.end(),dividendSize==num8Size?0:num8Size - num8Size)){
                shiftEnd = shift_left_digits(num8.begin(),num8End,dividendSize - num8Size,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(size);
                deque<int>::iterator partialQEnd = shift_left_digits(mul8,mul8+1,dividendSize - num8Size,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
            } else {
                shiftEnd = shift_left_digits(num4.begin(),num4End,dividendSize - num4Size,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(size);
                deque<int>::iterator partialQEnd = shift_left_digits(mul4,mul4+1,dividendSize - num4Size,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());}
        } else {
            if(dividendSize>=num2Size && myCompare(dividendRev.begin(),dividendRev.end(),num2Rev.begin(),num2Rev.end(),dividendSize==num2Size?0:num8Size - num2Size)){       
                shiftEnd = shift_left_digits(num2.begin(),num2End,dividendSize - num2Size,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(size);
                deque<int>::iterator partialQEnd = shift_left_digits(mul2,mul2+1,dividendSize - num2Size,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
            } else if(dividendSize >= numSize && myCompare(dividendRev.begin(),dividendRev.end(),numRev.begin(),numRev.end(),dividendSize==numSize?0:num8Size - numSize)) {
                shiftEnd = shift_left_digits(num.begin(),numEnd,dividendSize - numSize,shiftedNum.begin());
                dividendEnd = minus_digits(dividend.begin(),dividendEnd,shiftedNum.begin(),shiftEnd,dividend.begin());
                deque<int> partialQ(size);
                deque<int>::iterator partialQEnd = shift_left_digits(mul1,mul1+1,dividendSize - numSize,partialQ.begin());
                rsEnd = plus_digits(runningSum.begin(),rsEnd,partialQ.begin(),partialQEnd,runningSum.begin());
            } else {
                break;}}}
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
                if(*itFirst<*itSecond){
                    return result;
                } else if (*itFirst>*itSecond){
                    return !result;}
                ++itFirst;
                ++itSecond;
            }else{
                if(itSecond!=rhs._integer.crend())
                    return result;
                break;}} 
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
        unsigned int _size;
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
            _size = 0;
            if(value<0){
                _sign = true;
                value *= -1;
            } else {
                _sign = false;}
            if(value == 0){
                _integer.push_back(0);
                ++_size;
            }else{
                while(value!=0){
                    _integer.push_back(value % 10);
                    value = value/10;
                    ++_size;}}
            _integer.resize(_size);
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            string::const_iterator vBegin = value.cbegin();
            string::const_reverse_iterator vRevBegin = value.crbegin();
            string::const_reverse_iterator vRevEnd = value.crend();
            _size = 0;
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
                _integer.push_back(digit);
                ++_size;}
            _integer.resize(_size);
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
            if(this->_sign == rhs._sign){
                typename C::iterator plusEnd = plus_digits(this->_integer.begin(),this->_integer.end(),rhs._integer.begin(),rhs._integer.end(),this->_integer.begin());
                this->_integer.resize(plusEnd - this->_integer.begin());
            }else{
                bool lhsGreater = abs(*this) > rhs;
                if(lhsGreater){
                    typename C::iterator minusEnd = minus_digits(this->_integer.begin(),this->_integer.end(),rhs._integer.begin(),rhs._integer.end(),this->_integer.begin());
                } else {
                    typename C::iterator minusEnd = minus_digits(rhs._integer.begin(),rhs._integer.end(),this->_integer.begin(),this->_integer.end(),this->_integer.begin());
                    this->_sign = !this->_sign;}}
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
            if(this->_sign == rhs._sign){
                if(this->_sign)
                    this->_sign=!this->_sign;}
            typename C::iterator oldEnd = this->_integer.end();
           // this->_integer.resize(this->_size+rhs._size);
            C newInt(this->_size+rhs._size);
            typename C::iterator newEnd = multiplies_digits(this->_integer.begin(),oldEnd,rhs._integer.begin(),rhs._integer.end(),newInt.begin());
            this->_size = newEnd - newInt.begin();
            newInt.resize(this->_size);
            this->_integer = newInt;
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
            if (this->_sign)
                this->_sign = !this->_sign;
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
            //std::deque<int> powers; 
            std::deque<bool> powersOdd;
            typename std::deque<Integer<T,C> > products;
            typename C::iterator productEnd;

            //std::ostringstream out;
            //out << x;
            std::cout<<std::endl<<"Attempting to raise "<<*this<<"^"<<e<<" Size: "<<this->_integer.size()<<std::endl; 
            while(e){
                if(e%2 == 0){
              //      powers.push_back(e/2);
                    e/=2;
                    powersOdd.push_back(false);
                }else{
              //      powers.push_back(--e/2);
                    powersOdd.push_back(true);
                    --e;
                    e/=2;}}
           // std::deque<bool>::iterator itBTemp = powersOdd.begin();
           // for(std::deque<int>::iterator it = powers.begin();it!=powers.end();++it,++itBTemp)
           //     std::cout<<*it<<" "<<*itBTemp<<std::endl;
            for(deque<bool>::iterator itB = powersOdd.begin();itB!=powersOdd.end();++itB){
                products.push_back(*this);
               // this->_integer.resize(_size*2);
               // productEnd = multiplies_digits(this->_integer.begin(),this->_integer.end(),this->_integer.begin(),this->_integer.end(),this->_integer.begin());
               // _size = productEnd - this->_integer.begin();
               // this->_integer.resize(_size);
                (*this) *= (*this);
                std::cout<<"Hmmm";}
            typename deque<Integer<T,C> >::iterator itP = products.begin();
            for(deque<bool>::iterator itB = powersOdd.begin(); itB!=powersOdd.end(); ++itB,++itP){
                if(*itB){
                    //this->_integer.resize(_size * _size + (*itP).size());
                    //productEnd = multiplies_digits(this->_integer.begin(),this->_integer.end(),(*itP).begin(),(*itP).end(),this->_integer.begin());
                    //this->_integer.resize(productEnd - this->_integer.begin());
                    *this *= *itP;}}
            std::cout<<"\n"<<*this;
            return *this;}};

#endif // Integer_h
