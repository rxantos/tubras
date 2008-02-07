//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TRANDOM_H_
#define _TRANDOM_H_

/* Period parameters */  
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)


namespace Tubras
{

    class TRandom : public IReferenceCounted
    {
    private:
        // DATA
        unsigned int		rseed;
        unsigned int		rseed_sp;
        unsigned long mt[CMATH_N]; /* the array for the state vector  */
        int mti; /* mti==N+1 means mt[N] is not initialized */

        // FUNCTIONS
    public:
        TRandom();	

        unsigned int	getRandomInt( unsigned int n );
        float			getRandomFloat( );
        float           getRandomUniform(float min, float max);
        void			setRandomSeed(unsigned int n);
        unsigned int	getRandomSeed();
        void			randomize();
    };
}
#endif
