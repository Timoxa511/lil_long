
#include <TXLib.h>
#include <stdlib.h>
#include "W:\terrain-of-serviceable-gears\array_function_pack.h"

const size_t SZ = 8;

class SuperN
    {
    int number_ [SZ];

    public:
    SuperN ();                            //def constr
    SuperN (std::initializer_list<int> number);   //constr

    SuperN (const SuperN& ancestor);  //copy constr

        void printf (const char* comm);

            SuperN  operator~ () const;
            SuperN  operator- () const;
            SuperN& operator+= (const SuperN& b);
            SuperN& operator-= (const SuperN& b);
     friend SuperN  operator+  (const SuperN& a, const SuperN& b);
     friend SuperN  operator-  (const SuperN& a, const SuperN& b);
     friend SuperN  operator*  (const SuperN& a, const SuperN& b);   // <-+
                                                                     ///  |
            SuperN& operator*= (const SuperN& b);                    //   |
                                                                     //   |
            SuperN& plusEq_shifted (const SuperN& b, unsigned shift);//for+



    };



//=============================================================================

int main ()
    {

    SuperN a ({0,0,0,0,1,0,0,1});
    a.printf (__PRETTY_FUNCTION__);


    SuperN b ({0,0,0,0,0,0,0,0});
    b.printf (__PRETTY_FUNCTION__);


    SuperN c ({0,0,0,0,0,0,1,1});
    c.printf (__PRETTY_FUNCTION__);

    //SuperN c = a + b;
    //a -= b;

    a *= c;

    a.printf (__PRETTY_FUNCTION__);

    }


//{SuperN::--------------------------------------------------------------------
SuperN::SuperN () :
    number_ ()
    {}


//-----------------------------------------------------------------------------
SuperN::SuperN (std::initializer_list<int> number) :
    number_ ()
    {


    size_t i = number.size() - 1;

    for (auto iter = number.begin(); iter != number.end(); iter++)    //filling number_
        number_[i--] = *iter;

    assert (i == size_t (-1));
    }


//-----------------------------------------------------------------------------
SuperN::SuperN (const SuperN& ancestor) :
    number_ ()
    {
    assert (sizeof(ancestor.number_) ==  sizeof(number_));

    ::memcpy (number_, ancestor.number_, sizeof(number_)); //filling number_
    }


//=============================================================================

void SuperN::printf (const char* comm)
    {
    for (int i = SZ - 1; i >= 0; i--)
        {
        ::printf ("%2d ", number_[i]);
        }
    ::printf ("    %s\n", comm);
    }

//-----------------------------------------------------------------------------
SuperN& SuperN::operator+= (const SuperN& b)
    {

    for (unsigned i = 0; i < SZ; i++)
        {
        int sum = number_[i] + b.number_[i];

        number_[i]    = sum % 2;
        number_[i+1] += sum / 2;
        }
    return *this;
    }

//-----------------------------------------------------------------------------
SuperN operator+ (const SuperN& a, const SuperN& b)
    {
    SuperN ret = a;

    return ret += b;
    }


//-----------------------------------------------------------------------------
SuperN SuperN::operator~ ()  const
    {
    SuperN ret;

    int maxDig = 1;

    for (size_t  i = 0; i < SZ; i++)
        ret.number_[i] = maxDig - number_[i];

    return ret;
    }


//-----------------------------------------------------------------------------
SuperN SuperN::operator- () const
    {
    SuperN clone = ~*this;

    clone += SuperN ({0,0,0,0,0,0,0,1});

    return clone;
    }


//-----------------------------------------------------------------------------
SuperN operator- (const SuperN& a, const SuperN& b)
    {
    return a + -b;
    }


//-----------------------------------------------------------------------------
SuperN& SuperN::operator-= (const SuperN& b)
    {
    return (*this += -b);
    }


//-----------------------------------------------------------------------------
SuperN& SuperN::plusEq_shifted (const SuperN& b, unsigned shift)
    {
    for (unsigned i = 0; i < SZ; i++)
        {
        int sum = number_[i] + (i < shift)? 0 : b.number_[i - shift];
                                                                               //more effective with 2 loops : [0; shift] + (shift; SZ]
        number_[i]    = sum % 2;
        number_[i+1] += sum / 2;
        }
    return *this;
    }

//-----------------------------------------------------------------------------
SuperN operator* (const SuperN& a, const SuperN& b)
    {
    SuperN retv;

    for (int i = 0; i < SZ; i++)                                    //не степени двойки
        {
        if (b.number_[i]) retv.plusEq_shifted (a, i);
        }

    return retv;
    }


//-----------------------------------------------------------------------------
SuperN& SuperN::operator*= (const SuperN& b)
    {
    *this = *this * b;

    return *this;
    }

//}
//-----------------------------------------------------------------------------



