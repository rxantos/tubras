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
        TLerpSceneNodeInterval(const TString &name, double duration, 
            BlendType blendType, bool bakeInStart,
            bool fluid,
            TSceneNode* node, TSceneNode* other);

        virtual ~TLerpSceneNodeInterval();

        inline const TSceneNode* get_node() const;
        inline const TSceneNode* get_other() const;

        inline void set_start_pos(const TVector3 &pos);
        inline void set_end_pos(const TVector3 &pos);
        inline void set_start_hpr(const TVector3 &hpr);
        inline void set_start_hpr(const TQuaternion &quat);
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
        inline void set_start_color(const TColour &color);
        inline void set_end_color(const TColour &color);
        inline void set_start_color_scale(const TColour &color_scale);
        inline void set_end_color_scale(const TColour &color_scale);

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
        TQuaternion _start_hpr, _end_hpr;
        TQuaternion _start_quat, _end_quat;
        TVector3 _start_scale, _end_scale;
        TVector3 _start_shear, _end_shear;
        TColour _start_color, _end_color;
        TColour _start_color_scale, _end_color_scale;

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


    // Filename: cLerpNodePathInterval.I
    // Created by:  drose (27Aug02)
    //
    ////////////////////////////////////////////////////////////////////
    //
    // PANDA 3D SOFTWARE
    // Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
    //
    // All use of this software is subject to the terms of the Panda 3d
    // Software license.  You should have received a copy of this license
    // along with this source code; you will also find a current copy of
    // the license at http://etc.cmu.edu/panda3d/docs/license/ .
    //
    // To contact the maintainers of this program write to
    // panda3d-general@lists.sourceforge.net .
    //
    ////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::get_node
    //       Access: Published
    //  Description: Returns the node being lerped.
    ////////////////////////////////////////////////////////////////////
    inline const TSceneNode* TLerpSceneNodeInterval::
        get_node() const {
            return _node;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::get_other
    //       Access: Published
    //  Description: Returns the "other" node, which the lerped node is
    //               being moved relative to.  If this is an empty node
    //               path, the lerped node is being moved in its own
    //               coordinate system.
    ////////////////////////////////////////////////////////////////////
    inline const TSceneNode* TLerpSceneNodeInterval::
        get_other() const {
            return _other;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_pos
    //       Access: Published
    //  Description: Indicates the initial position of the lerped node.
    //               This is meaningful only if set_end_pos() is also
    //               called.  This parameter is optional; if unspecified,
    //               the value will be taken from the node's actual
    //               position at the time the lerp is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_pos(const TVector3 &pos) {
            _start_pos = pos;
            _flags |= F_start_pos;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_pos
    //       Access: Published
    //  Description: Indicates that the position of the node should be
    //               lerped, and specifies the final position of the node.
    //               This should be called before priv_initialize().  If this
    //               is not called, the node's position will not be
    //               affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_pos(const TVector3 &pos) {
            _end_pos = pos;
            _flags |= F_end_pos;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_hpr
    //       Access: Published
    //  Description: Indicates the initial rotation of the lerped node.
    //               This is meaningful only if either set_end_hpr() or
    //               set_end_quat() is also called.  This parameter is
    //               optional; if unspecified, the value will be taken
    //               from the node's actual rotation at the time the lerp
    //               is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::set_start_hpr(const TVector3 &hpr) 
    {
            _start_hpr.setHpr(hpr.x,hpr.y,hpr.z);
            _flags = (_flags & ~(F_slerp_setup | F_start_quat)) | F_start_hpr;
    }

    inline void TLerpSceneNodeInterval::set_start_hpr(const TQuaternion &quat)
    {
        _start_hpr = quat;
        _flags = (_flags & ~(F_slerp_setup | F_start_quat)) | F_start_hpr;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_hpr
    //       Access: Published
    //  Description: Indicates that the rotation of the node should be
    //               lerped, and specifies the final rotation of the node.
    //               This should be called before priv_initialize().
    //
    //               This replaces a previous call to set_end_quat().  If
    //               neither set_end_hpr() nor set_end_quat() is called,
    //               the node's rotation will not be affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::set_end_hpr(const TVector3 &hpr) 
    {
            _end_hpr.setHpr(hpr.x,hpr.y,hpr.z);
            _flags = (_flags & ~F_end_quat) | F_end_hpr;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_hpr
    //       Access: Published
    //  Description: Indicates that the rotation of the node should be
    //               lerped, and specifies the final rotation of the node.
    //               This should be called before priv_initialize().
    //
    //               This special function is overloaded to accept a
    //               quaternion, even though the function name is
    //               set_end_hpr().  The quaternion will be implicitly
    //               converted to a HPR trio, and the lerp will be
    //               performed in HPR space, componentwise.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_hpr(const TQuaternion &quat) {
            //_end_hpr = quat.get_hpr();
            _flags = (_flags & ~F_end_quat) | F_end_hpr;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_quat
    //       Access: Published
    //  Description: Indicates the initial rotation of the lerped node.
    //               This is meaningful only if either set_end_quat() or
    //               set_end_hpr() is also called.  This parameter is
    //               optional; if unspecified, the value will be taken
    //               from the node's actual rotation at the time the lerp
    //               is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_quat(const TQuaternion &quat) {
            _start_quat = quat;
            _flags = (_flags & ~(F_slerp_setup | F_start_hpr)) | F_start_quat;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_quat
    //       Access: Published
    //  Description: Indicates that the rotation of the node should be
    //               lerped, and specifies the final rotation of the node.
    //               This should be called before priv_initialize().
    //
    //               This replaces a previous call to set_end_hpr().  If
    //               neither set_end_quat() nor set_end_hpr() is called,
    //               the node's rotation will not be affected by the lerp.
    //
    //               This special function is overloaded to accept a HPR
    //               trio, even though the function name is
    //               set_end_quat().  The HPR will be implicitly converted
    //               to a quaternion, and the lerp will be performed in
    //               quaternion space, as a spherical lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_quat(const TVector3 &hpr) {
            //_end_quat.set_hpr(hpr);
            _flags = (_flags & ~(F_slerp_setup | F_end_hpr)) | F_end_quat;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_quat
    //       Access: Published
    //  Description: Indicates that the rotation of the node should be
    //               lerped, and specifies the final rotation of the node.
    //               This should be called before priv_initialize().
    //
    //               This replaces a previous call to set_end_hpr().  If
    //               neither set_end_quat() nor set_end_hpr() is called,
    //               the node's rotation will not be affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_quat(const TQuaternion &quat) {
            _end_quat = quat;
            _flags = (_flags & ~(F_slerp_setup | F_end_hpr)) | F_end_quat;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_scale
    //       Access: Published
    //  Description: Indicates the initial scale of the lerped node.
    //               This is meaningful only if set_end_scale() is also
    //               called.  This parameter is optional; if unspecified,
    //               the value will be taken from the node's actual
    //               scale at the time the lerp is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_scale(const TVector3 &scale) {
            _start_scale = scale;
            _flags |= F_start_scale;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_scale
    //       Access: Published
    //  Description: Indicates the initial scale of the lerped node.
    //               This is meaningful only if set_end_scale() is also
    //               called.  This parameter is optional; if unspecified,
    //               the value will be taken from the node's actual
    //               scale at the time the lerp is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_scale(float scale) {
            set_start_scale(TVector3(scale, scale, scale));
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_scale
    //       Access: Published
    //  Description: Indicates that the scale of the node should be
    //               lerped, and specifies the final scale of the node.
    //               This should be called before priv_initialize().  If this
    //               is not called, the node's scale will not be
    //               affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_scale(const TVector3 &scale) {
            _end_scale = scale;
            _flags |= F_end_scale;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_scale
    //       Access: Published
    //  Description: Indicates that the scale of the node should be
    //               lerped, and specifies the final scale of the node.
    //               This should be called before priv_initialize().  If this
    //               is not called, the node's scale will not be
    //               affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_scale(float scale) {
            set_end_scale(TVector3(scale, scale, scale));
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_shear
    //       Access: Published
    //  Description: Indicates the initial shear of the lerped node.
    //               This is meaningful only if set_end_shear() is also
    //               called.  This parameter is optional; if unspecified,
    //               the value will be taken from the node's actual
    //               shear at the time the lerp is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_shear(const TVector3 &shear) {
            _start_shear = shear;
            _flags |= F_start_shear;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_shear
    //       Access: Published
    //  Description: Indicates that the shear of the node should be
    //               lerped, and specifies the final shear of the node.
    //               This should be called before priv_initialize().  If this
    //               is not called, the node's shear will not be
    //               affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_shear(const TVector3 &shear) {
            _end_shear = shear;
            _flags |= F_end_shear;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_color
    //       Access: Published
    //  Description: Indicates the initial color of the lerped node.
    //               This is meaningful only if set_end_color() is also
    //               called.  This parameter is optional; if unspecified,
    //               the value will be taken from the node's actual
    //               color at the time the lerp is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_color(const TColour &color) {
            _start_color = color;
            _flags |= F_start_color;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_color
    //       Access: Published
    //  Description: Indicates that the color of the node should be
    //               lerped, and specifies the final color of the node.
    //               This should be called before priv_initialize().  If this
    //               is not called, the node's color will not be
    //               affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_color(const TColour &color) {
            _end_color = color;
            _flags |= F_end_color;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_start_color_scale
    //       Access: Published
    //  Description: Indicates the initial color scale of the lerped node.
    //               This is meaningful only if set_end_color_scale() is also
    //               called.  This parameter is optional; if unspecified,
    //               the value will be taken from the node's actual
    //               color scale at the time the lerp is performed.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_start_color_scale(const TColour &color_scale) {
            _start_color_scale = color_scale;
            _flags |= F_start_color_scale;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::set_end_color_scale
    //       Access: Published
    //  Description: Indicates that the color scale of the node should be
    //               lerped, and specifies the final color scale of the node.
    //               This should be called before priv_initialize().  If this
    //               is not called, the node's color scale will not be
    //               affected by the lerp.
    ////////////////////////////////////////////////////////////////////
    inline void TLerpSceneNodeInterval::
        set_end_color_scale(const TColour &color_scale) {
            _end_color_scale = color_scale;
            _flags |= F_end_color_scale;
    }



}

#endif