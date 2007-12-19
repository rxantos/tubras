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
#ifndef _TMATH_H_
#define _TMATH_H_

namespace Tubras
{

    class TDegree;
    /* shamelessly ripped from "ogremath.h"
    /** Wrapper class which indicates a given angle value is in Radians.
    @remarks
    Radian values are interchangeable with Degree values, and conversions
    will be done automatically between them.
    */
    class TRadian
    {
        f32 mRad;

    public:
        explicit TRadian ( f32 r=0 ) : mRad(r) {}
        TRadian ( const TDegree& d );
        TRadian& operator = ( const f32& f ) { mRad = f; return *this; }
        TRadian& operator = ( const TRadian& r ) { mRad = r.mRad; return *this; }
        TRadian& operator = ( const TDegree& d );

        f32 valueDegrees() const; // see bottom of this file
        f32 valueRadians() const { return mRad; }
        f32 valueAngleUnits() const;

        const TRadian& operator + () const { return *this; }
        TRadian operator + ( const TRadian& r ) const { return TRadian ( mRad + r.mRad ); }
        TRadian operator + ( const TDegree& d ) const;
        TRadian& operator += ( const TRadian& r ) { mRad += r.mRad; return *this; }
        TRadian& operator += ( const TDegree& d );
        TRadian operator - () const { return TRadian(-mRad); }
        TRadian operator - ( const TRadian& r ) const { return TRadian ( mRad - r.mRad ); }
        TRadian operator - ( const TDegree& d ) const;
        TRadian& operator -= ( const TRadian& r ) { mRad -= r.mRad; return *this; }
        TRadian& operator -= ( const TDegree& d );
        TRadian operator * ( f32 f ) const { return TRadian ( mRad * f ); }
        TRadian operator * ( const TRadian& f ) const { return TRadian ( mRad * f.mRad ); }
        TRadian& operator *= ( f32 f ) { mRad *= f; return *this; }
        TRadian operator / ( f32 f ) const { return TRadian ( mRad / f ); }
        TRadian& operator /= ( f32 f ) { mRad /= f; return *this; }

        bool operator <  ( const TRadian& r ) const { return mRad <  r.mRad; }
        bool operator <= ( const TRadian& r ) const { return mRad <= r.mRad; }
        bool operator == ( const TRadian& r ) const { return mRad == r.mRad; }
        bool operator != ( const TRadian& r ) const { return mRad != r.mRad; }
        bool operator >= ( const TRadian& r ) const { return mRad >= r.mRad; }
        bool operator >  ( const TRadian& r ) const { return mRad >  r.mRad; }
    };

    /** Wrapper class which indicates a given angle value is in TDegrees.
    @remarks
    TDegree values are interchangeable with TRadian values, and conversions
    will be done automatically between them.
    */
    class TDegree
    {
        f32 mDeg; // if you get an error here - make sure to define/typedef 'Real' first

    public:
        explicit TDegree ( f32 d=0 ) : mDeg(d) {}
        TDegree ( const TRadian& r ) : mDeg(r.valueDegrees()) {}
        TDegree& operator = ( const f32& f ) { mDeg = f; return *this; }
        TDegree& operator = ( const TDegree& d ) { mDeg = d.mDeg; return *this; }
        TDegree& operator = ( const TRadian& r ) { mDeg = r.valueDegrees(); return *this; }

        f32 valueDegrees() const { return mDeg; }
        f32 valueRadians() const; // see bottom of this file
        f32 valueAngleUnits() const;

        const TDegree& operator + () const { return *this; }
        TDegree operator + ( const TDegree& d ) const { return TDegree ( mDeg + d.mDeg ); }
        TDegree operator + ( const TRadian& r ) const { return TDegree ( mDeg + r.valueDegrees() ); }
        TDegree& operator += ( const TDegree& d ) { mDeg += d.mDeg; return *this; }
        TDegree& operator += ( const TRadian& r ) { mDeg += r.valueDegrees(); return *this; }
        TDegree operator - () const { return TDegree(-mDeg); }
        TDegree operator - ( const TDegree& d ) const { return TDegree ( mDeg - d.mDeg ); }
        TDegree operator - ( const TRadian& r ) const { return TDegree ( mDeg - r.valueDegrees() ); }
        TDegree& operator -= ( const TDegree& d ) { mDeg -= d.mDeg; return *this; }
        TDegree& operator -= ( const TRadian& r ) { mDeg -= r.valueDegrees(); return *this; }
        TDegree operator * ( f32 f ) const { return TDegree ( mDeg * f ); }
        TDegree operator * ( const TDegree& f ) const { return TDegree ( mDeg * f.mDeg ); }
        TDegree& operator *= ( f32 f ) { mDeg *= f; return *this; }
        TDegree operator / ( f32 f ) const { return TDegree ( mDeg / f ); }
        TDegree& operator /= ( f32 f ) { mDeg /= f; return *this; }

        bool operator <  ( const TDegree& d ) const { return mDeg <  d.mDeg; }
        bool operator <= ( const TDegree& d ) const { return mDeg <= d.mDeg; }
        bool operator == ( const TDegree& d ) const { return mDeg == d.mDeg; }
        bool operator != ( const TDegree& d ) const { return mDeg != d.mDeg; }
        bool operator >= ( const TDegree& d ) const { return mDeg >= d.mDeg; }
        bool operator >  ( const TDegree& d ) const { return mDeg >  d.mDeg; }
    };

    /** Wrapper class which identifies a value as the currently default angle 
    type, as defined by Math::setAngleUnit.
    @remarks
    Angle values will be automatically converted between TRadians and TDegrees,
    as appropriate.
    */
    class TAngle
    {
        f32 mAngle;
    public:
        explicit TAngle ( f32 angle ) : mAngle(angle) {}
        operator TRadian() const;
        operator TDegree() const;
    };

    // these functions could not be defined within the class definition of class
    // TRadian because they required class TDegree to be defined
    inline TRadian::TRadian ( const TDegree& d ) : mRad(d.valueRadians()) {
    }
    inline TRadian& TRadian::operator = ( const TDegree& d ) {
        mRad = d.valueRadians(); return *this;
    }
    inline TRadian TRadian::operator + ( const TDegree& d ) const {
        return TRadian ( mRad + d.valueRadians() );
    }
    inline TRadian& TRadian::operator += ( const TDegree& d ) {
        mRad += d.valueRadians();
        return *this;
    }
    inline TRadian TRadian::operator - ( const TDegree& d ) const {
        return TRadian ( mRad - d.valueRadians() );
    }
    inline TRadian& TRadian::operator -= ( const TDegree& d ) {
        mRad -= d.valueRadians();
        return *this;
    }

    class TMath
    {
    public:
        TMath();

        static const f32 PI;
        static const f32 TWO_PI;
        static const f32 RECIPROCAL_PI;
        static const f32 HALF_PI;
        static const f32 DEGTORAD;
        static const f32 RADTODEG;
    };
}
#endif
