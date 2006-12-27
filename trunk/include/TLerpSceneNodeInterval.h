//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef _TLERPSCENENODEINTERVAL_H_
#define _TLERPSCENENODEINTERVAL_H_

namespace Tubras
{
    class TSceneNode;

    class TLerpSceneNodeInterval : public TLerpInterval
    {

    public:
        TLerpSceneNodeInterval(const string &name, double duration, 
            BlendType blendType, bool bakeInStart,
            bool fluid,
            TSceneNode* node, TSceneNode* other);

        virtual ~TLerpSceneNodeInterval();

        inline const TSceneNode &get_node() const;
        inline const TSceneNode &get_other() const;

        inline void set_start_pos(const TVector3 &pos);
        inline void set_end_pos(const TVector3 &pos);
        inline void set_start_hpr(const TVector3 &hpr);
        inline void set_end_hpr(const TVector3 &hpr);
        inline void set_end_hpr(const TQuaternion &quat);
        inline void set_start_quat(const TQuaternion &quat);
        inline void set_end_quat(const TVector3 &hpr);
        inline void set_end_quat(const TQuaternion &quat);
        inline void set_start_scale(const TVector3 &scale);
        inline void set_start_scale(float scale);
        inline void set_end_scale(const TVector3 &scale);
        inline void set_end_scale(float scale);
        inline void set_start_shear(const TVector3 &shear);
        inline void set_end_shear(const TVector3 &shear);
        inline void set_start_color(const TVector4 &color);
        inline void set_end_color(const TVector4 &color);
        inline void set_start_color_scale(const TVector4 &color_scale);
        inline void set_end_color_scale(const TVector4 &color_scale);

        virtual void priv_initialize(double t);
        virtual void priv_instant();
        virtual void priv_step(double t);
        virtual void priv_reverse_initialize(double t);
        virtual void priv_reverse_instant();


    private:
        void setup_slerp();

        TSceneNode* _node;
        TSceneNode* _other;

        enum Flags {
            F_end_pos            = 0x000001,
            F_end_hpr            = 0x000002,
            F_end_quat           = 0x000004,
            F_end_scale          = 0x000008,
            F_end_color          = 0x000010,
            F_end_color_scale    = 0x000020,
            F_end_shear          = 0x000040,

            F_start_pos          = 0x000080,
            F_start_hpr          = 0x000100,
            F_start_quat         = 0x000200,
            F_start_scale        = 0x000400,
            F_start_color        = 0x000800,
            F_start_color_scale  = 0x001000,
            F_start_shear        = 0x002000,

            F_fluid              = 0x004000,
            F_bake_in_start      = 0x008000,

            F_slerp_setup        = 0x010000,
        };

        unsigned int _flags;
        TVector3 _start_pos, _end_pos;
        TVector3 _start_hpr, _end_hpr;
        TQuaternion _start_quat, _end_quat;
        TVector3 _start_scale, _end_scale;
        TVector3 _start_shear, _end_shear;
        TColor _start_color, _end_color;
        TVector4 _start_color_scale, _end_color_scale;

        double _prev_d;
        float _slerp_angle;
        float _slerp_denom;
        TQuaternion _slerp_c;

        void slerp_basic(TQuaternion &result, float t) const;
        void slerp_angle_0(TQuaternion &result, float t) const;
        void slerp_angle_180(TQuaternion &result, float t) const;

        // Define a pointer to one of the above three methods.
        void (TLerpSceneNodeInterval::*_slerp)(TQuaternion &result, float t) const;

    };

    ////////////////////////////////////////////////////////////////////
    //     Function: lerp_value
    //  Description: Applies the linear lerp computation for a single
    //               parameter.
    ////////////////////////////////////////////////////////////////////
    template<class NumericType>
    inline void
        lerp_value(NumericType &current_value,
        double d,
        const NumericType &starting_value,
        const NumericType &ending_value) {
            current_value = starting_value + d * (ending_value - starting_value);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: lerp_value_from_prev
    //  Description: Applies the linear lerp computation for a single
    //               parameter, when the starting value is implicit.
    //
    //               This computes the new value based on assuming the
    //               prev_value represents the value computed at delta
    //               prev_d.
    ////////////////////////////////////////////////////////////////////
    template<class NumericType>
    inline void
        lerp_value_from_prev(NumericType &current_value,
        double d, double prev_d,
        const NumericType &prev_value,
        const NumericType &ending_value) {
            if (prev_d == 1.0) {
                current_value = ending_value;
            } else {
                NumericType starting_value = 
                    (prev_value - prev_d * ending_value) / (1.0 - prev_d);
                current_value = starting_value + d * (ending_value - starting_value);
            }
    }


}

#endif