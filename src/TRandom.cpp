//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "tubras.h"
#include <time.h>

namespace Tubras {

    //-----------------------------------------------------------------------
    //                               T R a n d o m 
    //-----------------------------------------------------------------------
    TRandom::TRandom()
    {
        rseed = 1;
        // safe0 start
        rseed_sp = 0;
        mti=CMATH_N+1;
        // safe0 end
    }	

    //-----------------------------------------------------------------------
    //                          g e t R a n d o m I n t
    //-----------------------------------------------------------------------
    // Returns a number from 0 to n (excluding n)
    unsigned int TRandom::getRandomInt( unsigned int n )
    {
        unsigned long y;
        static unsigned long mag01[2]={0x0, CMATH_MATRIX_A};

        if(n==0)
            return(0);

        /* mag01[x] = x * MATRIX_A  for x=0,1 */

        if (mti >= CMATH_N) { /* generate N words at one time */
            int kk;

            if (mti == CMATH_N+1)   /* if sgenrand() has not been called, */
                setRandomSeed(4357); /* a default initial seed is used   */

            for (kk=0;kk<CMATH_N-CMATH_M;kk++) {
                y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
                mt[kk] = mt[kk+CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
            }
            for (;kk<CMATH_N-1;kk++) {
                y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
                mt[kk] = mt[kk+(CMATH_M-CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
            }
            y = (mt[CMATH_N-1]&CMATH_UPPER_MASK)|(mt[0]&CMATH_LOWER_MASK);
            mt[CMATH_N-1] = mt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

            mti = 0;
        }

        y = mt[mti++];
        y ^= CMATH_TEMPERING_SHIFT_U(y);
        y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
        y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
        y ^= CMATH_TEMPERING_SHIFT_L(y);

        // ET - old engine added one to the result.
        // We almost NEVER wanted to use this function
        // like this.  So, removed the +1 to return a 
        // range from 0 to n (not including n).
        return (y%n);
    }


    //-----------------------------------------------------------------------
    //                            g e t R a n d o m 
    //-----------------------------------------------------------------------
    // Returns a random float between 0.0f-1.0f
    // NEW for Game Code Complete 2nd Edition!
    float TRandom::getRandomFloat( )
    {
        unsigned int r = getRandomInt(0xffffffff);
        float divisor = (float)0xffffffff;
        return r / divisor;
    }

    //-----------------------------------------------------------------------
    //                         S e t R a n d o m S e e d
    //-----------------------------------------------------------------------
    void TRandom::setRandomSeed(unsigned int n)
    {
        /* setting initial seeds to mt[N] using         */
        /* the generator Line 25 of Table 1 in          */
        /* [KNUTH 1981, The Art of Computer Programming */
        /*    Vol. 2 (2nd Ed.), pp102]                  */
        mt[0]= n & 0xffffffff;
        for (mti=1; mti<CMATH_N; mti++)
            mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

        rseed = n;
    }

    //-----------------------------------------------------------------------
    //                         G e t R a n d o m S e e d
    //-----------------------------------------------------------------------
    unsigned int TRandom::getRandomSeed()
    {
        return(rseed);
    }

    //-----------------------------------------------------------------------
    //                            R a n d o m i z e
    //-----------------------------------------------------------------------
    void TRandom::randomize()
    {
        setRandomSeed((unsigned int)time(NULL));
    }

}



