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

#include "tubras.h"

namespace Tubras
{
    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::Constructor
    //       Access: Published
    //  Description: Constructs a lerp interval that will lerp some
    //               properties on the indicated node, possibly relative
    //               to the indicated other node (if other is nonempty).
    //
    //               You must call set_end_pos(), etc. for the various
    //               properties you wish to lerp before the first call to
    //               priv_initialize().  If you want to set a starting value
    //               for any of the properties, you may call
    //               set_start_pos(), etc.; otherwise, the starting value
    //               is taken from the actual node's value at the time the
    //               lerp is performed.
    //
    //               The starting values may be explicitly specified or
    //               omitted.  The value of bake_in_start determines the
    //               behavior if the starting values are omitted.  If
    //               bake_in_start is true, the values are obtained the
    //               first time the lerp runs, and thenceforth are stored
    //               within the interval.  If bake_in_start is false, the
    //               starting value is computed each frame, based on
    //               assuming the current value represents the value set
    //               from the last time the interval was run.  This
    //               "smart" behavior allows code to manipulate the object
    //               event while it is being lerped, and the lerp
    //               continues to apply in a sensible way.
    //
    //               If fluid is true, the prev_transform is not adjusted
    //               by the lerp; otherwise, it is reset.
    ////////////////////////////////////////////////////////////////////
    TLerpSceneNodeInterval::TLerpSceneNodeInterval(const TString &name, double duration, 
        BlendType blend_type,
        bool bake_in_start, bool fluid,
        TSceneNode* node, TSceneNode* other) :
    TLerpInterval(name, duration, blend_type),
        _node(node),
        _other(other),
        _flags(0),
        _slerp(NULL)
    {
        if (bake_in_start) {
            _flags |= F_bake_in_start;
        }
        if (fluid) {
            _flags |= F_fluid;
        }
        _prev_d = 0.0;
    }

    TLerpSceneNodeInterval::~TLerpSceneNodeInterval()
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::initialize
    //       Access: Published, Virtual
    //  Description: This replaces the first call to priv_step(), and indicates
    //               that the interval has just begun.  This may be
    //               overridden by derived classes that need to do some
    //               explicit initialization on the first call.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        priv_initialize(double t) {
            recompute();
            _prev_d = 0.0;
            _state = S_started;
            priv_step(t);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::instant
    //       Access: Published, Virtual
    //  Description: This is called in lieu of priv_initialize() .. priv_step()
    //               .. priv_finalize(), when everything is to happen within
    //               one frame.  The interval should initialize itself,
    //               then leave itself in the final state.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        priv_instant() {
            recompute();
            _prev_d = 0.0;
            _state = S_started;
            priv_step(get_duration());
            _state = S_final;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::step
    //       Access: Published, Virtual
    //  Description: Advances the time on the interval.  The time may
    //               either increase (the normal case) or decrease
    //               (e.g. if the interval is being played by a slider).
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::priv_step(double t) 
    {
        TLerpInterval::priv_step(t);

        _state = S_started;
        double d = computeDelta(t);


        // Save this in case we want to restore it later.
        TMatrix4 prev_transform;
        TVector3 prev_hpr;
        TQuaternion prev_quat;
        _node->getTransform(&prev_transform);
        prev_hpr = _node->getHpr();
        prev_quat = _node->getOrientation();

        if ((_flags & (F_end_pos | F_end_hpr | F_end_quat | F_end_scale | F_end_shear)) != 0) 
        {
            // We have some transform lerp.
            TMatrix4 transform;

            if (_other == NULL) 
            {
                // If there is no other node, it's a local transform lerp.
                _node->getTransform(&transform);
            } else 
            {
                // If there *is* another node, we get the transform relative to
                // that node.
                _node->getTransform(&transform,_other);
            }

            TVector3 pos;
            TQuaternion hpr;
            TQuaternion quat;
            TVector3 scale;
            TVector3 shear;

            if ((_flags & F_end_pos) != 0) 
            {
                if ((_flags & F_start_pos) != 0) 
                {
                    lerp_value(pos, d, _start_pos, _end_pos);
                } 
                else if ((_flags & F_bake_in_start) != 0) 
                {
                    // Get the current starting pos, and bake it in.
                    TVector3 tpos;
                    transform.getPos(tpos);
                    set_start_pos(tpos);
                    lerp_value(pos, d, _start_pos, _end_pos);

                } 
                else 
                {
                    // "smart" lerp from the current pos to the new pos.
                    transform.getPos(pos);
                    lerp_value_from_prev(pos, d, _prev_d, pos, _end_pos);
                }
            }
            
            if ((_flags & F_end_hpr) != 0) 
            {
                hpr = TQuaternion::Slerp(d,_start_hpr, _end_hpr);
                    
                
            }
            /*
            if ((_flags & F_end_quat) != 0) {
            if ((_flags & F_slerp_setup) == 0) {
            if ((_flags & F_start_quat) != 0) {
            setup_slerp();

            } else if ((_flags & F_start_hpr) != 0) {
            _start_quat.set_hpr(_start_hpr);
            _flags |= F_start_quat;
            setup_slerp();

            } else if ((_flags & F_bake_in_start) != 0) {
            set_start_quat(transform->get_quat());
            setup_slerp();

            } else {
            if (_prev_d == 1.0) {
            _start_quat = _end_quat;
            } else {
            TQuaternion prev_value = transform->get_quat();
            _start_quat = (prev_value - _prev_d * _end_quat) / (1.0 - _prev_d);
            }
            setup_slerp();

            // In this case, clear the slerp_setup flag because we need
            // to re-setup the slerp each time.
            _flags &= ~F_slerp_setup;
            }
            }
            nassertv(_slerp != NULL);
            (this->*_slerp)(quat, d);
            }
            if ((_flags & F_end_scale) != 0) {
            if ((_flags & F_start_scale) != 0) {
            lerp_value(scale, d, _start_scale, _end_scale);

            } else if ((_flags & F_bake_in_start) != 0) {
            set_start_scale(transform->get_scale());
            lerp_value(scale, d, _start_scale, _end_scale);

            } else {
            scale = transform->get_scale();
            lerp_value_from_prev(scale, d, _prev_d, scale, _end_scale);
            }
            }
            if ((_flags & F_end_shear) != 0) {
            if ((_flags & F_start_shear) != 0) {
            lerp_value(shear, d, _start_shear, _end_shear);

            } else if ((_flags & F_bake_in_start) != 0) {
            set_start_shear(transform->get_shear());
            lerp_value(shear, d, _start_shear, _end_shear);

            } else {
            shear = transform->get_shear();
            lerp_value_from_prev(shear, d, _prev_d, shear, _end_shear);
            }
            }
            */

            // Now apply the modifications back to the transform.  We want to
            // be a little careful here, because we don't want to assume the
            // transform has hpr/scale components if they're not needed.  And
            // in any case, we only want to apply the components that we
            // computed, above.
            unsigned int transform_flags = _flags & (F_end_pos | F_end_hpr | F_end_quat | F_end_scale);
            switch (transform_flags) 
            {
            case 0:
                break;

            case F_end_pos:
                if (!_other) 
                {
                    _node->setPos(pos);
                } 
                else 
                {
                    // _node.set_pos(_other, pos);
                }
                break;


            case F_end_hpr:
                if (!_other)
                {
                    _node->setOrientation(hpr);
                } 
                else 
                {
                //    _node.set_hpr(_other, hpr);
                }
                break;
            }

            /*

            case F_end_quat:
            if (_other.is_empty()) {
            _node.set_quat(quat);
            } else {
            _node.set_quat(_other, quat);
            }
            break;

            case F_end_scale:
            if (_other.is_empty()) {
            _node.set_scale(scale);
            } else {
            _node.set_scale(_other, scale);
            }
            break;

            case F_end_hpr | F_end_scale:
            if (_other.is_empty()) {
            _node.set_hpr_scale(hpr, scale);
            } else {
            _node.set_hpr_scale(hpr, scale);
            }
            break;

            case F_end_quat | F_end_scale:
            if (_other.is_empty()) {
            _node.set_quat_scale(quat, scale);
            } else {
            _node.set_quat_scale(quat, scale);
            }
            break;

            case F_end_pos | F_end_hpr:
            if (_other.is_empty()) {
            _node.set_pos_hpr(pos, hpr);
            } else {
            _node.set_pos_hpr(_other, pos, hpr);
            }
            break;

            case F_end_pos | F_end_quat:
            if (_other.is_empty()) {
            _node.set_pos_quat(pos, quat);
            } else {
            _node.set_pos_quat(_other, pos, quat);
            }
            break;

            case F_end_pos | F_end_scale:
            if (transform->quat_given()) {
            if (_other.is_empty()) {
            _node.set_pos_quat_scale(pos, transform->get_quat(), scale);
            } else {
            _node.set_pos_quat_scale(_other, pos, transform->get_quat(), scale);
            }
            } else {
            if (_other.is_empty()) {
            _node.set_pos_hpr_scale(pos, transform->get_hpr(), scale);
            } else {
            _node.set_pos_hpr_scale(_other, pos, transform->get_hpr(), scale);
            }
            }
            break;

            case F_end_pos | F_end_hpr | F_end_scale:
            if ((_flags & F_end_shear) != 0) {
            // Even better: we have all four components.
            if (_other.is_empty()) {
            _node.set_pos_hpr_scale_shear(pos, hpr, scale, shear);
            } else {
            _node.set_pos_hpr_scale_shear(_other, pos, hpr, scale, shear);
            }
            } else {
            // We have only the primary three components.
            if (_other.is_empty()) {
            _node.set_pos_hpr_scale(pos, hpr, scale);
            } else {
            _node.set_pos_hpr_scale(_other, pos, hpr, scale);
            }
            }
            break;

            case F_end_pos | F_end_quat | F_end_scale:
            if ((_flags & F_end_shear) != 0) {
            // Even better: we have all four components.
            if (_other.is_empty()) {
            _node.set_pos_quat_scale_shear(pos, quat, scale, shear);
            } else {
            _node.set_pos_quat_scale_shear(_other, pos, quat, scale, shear);
            }
            } else {
            // We have only the primary three components.
            if (_other.is_empty()) {
            _node.set_pos_quat_scale(pos, quat, scale);
            } else {
            _node.set_pos_quat_scale(_other, pos, quat, scale);
            }
            }
            break;

            default:
            // Some unhandled combination.  We should handle this.
            interval_cat.error()
            << "Internal error in TLerpSceneNodeInterval::priv_step().\n";
            }
            if ((_flags & F_end_shear) != 0) {
            // Also apply changes to shear.
            if (transform_flags == (F_end_pos | F_end_hpr | F_end_scale) ||
            transform_flags == (F_end_pos | F_end_quat | F_end_scale)) {
            // Actually, we already handled this case above.

            } else {
            if (_other.is_empty()) {
            _node.set_shear(shear);
            } else {
            _node.set_shear(_other, shear);
            }
            }
            }
            }

            if ((_flags & F_fluid) != 0) {
            // If we have the fluid flag set, we shouldn't mess with the prev
            // transform.  Therefore, restore it to what it was before we
            // started messing with it.
            _node.set_prev_transform(prev_transform);
            }

            if ((_flags & (F_end_color | F_end_color_scale)) != 0) {
            // We have some render state lerp.
            CPT(RenderState) state;

            if (_other.is_empty()) {
            // If there is no other node, it's a local state lerp.  This is
            // most common.
            state = _node.get_state();
            } else {
            // If there *is* another node, we get the state relative to that
            // node.  This is weird, but you could lerp color (for instance)
            // relative to some other node's color.
            state = _node.get_state(_other);
            }

            // Unlike in the transform case above, we can go ahead and modify
            // the state immediately with each attribute change, since these
            // attributes don't interrelate.

            if ((_flags & F_end_color) != 0) {
            Colorf color;

            if ((_flags & F_start_color) != 0) {
            lerp_value(color, d, _start_color, _end_color);

            } else {
            // Get the previous color.
            color.set(1.0f, 1.0f, 1.0f, 1.0f);
            const RenderAttrib *attrib =
            state->get_attrib(ColorAttrib::get_class_type());
            if (attrib != (const RenderAttrib *)NULL) {
            const ColorAttrib *ca = DCAST(ColorAttrib, attrib);
            if (ca->get_color_type() == ColorAttrib::T_flat) {
            color = ca->get_color();
            }
            }

            lerp_value_from_prev(color, d, _prev_d, color, _end_color);
            }

            state = state->add_attrib(ColorAttrib::make_flat(color));
            }

            if ((_flags & F_end_color_scale) != 0) {
            LVecBase4f color_scale;

            if ((_flags & F_start_color_scale) != 0) {
            lerp_value(color_scale, d, _start_color_scale, _end_color_scale);

            } else {
            // Get the previous color scale.
            color_scale.set(1.0f, 1.0f, 1.0f, 1.0f);
            const RenderAttrib *attrib =
            state->get_attrib(ColorScaleAttrib::get_class_type());
            if (attrib != (const RenderAttrib *)NULL) {
            const ColorScaleAttrib *csa = DCAST(ColorScaleAttrib, attrib);
            color_scale = csa->get_scale();
            }

            lerp_value_from_prev(color_scale, d, _prev_d, color_scale, _end_color_scale);
            }

            state = state->add_attrib(ColorScaleAttrib::make(color_scale));
            }    
            


            // Now apply the new state back to the node.
            if (!_other) 
            {
                _node.set_state(state);
            } 
            else 
            {
                _node.set_state(_other, state);
            }
            */
        } 
        _prev_d = d;
        _curr_t = t;

    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::reverse_initialize
    //       Access: Published, Virtual
    //  Description: Similar to priv_initialize(), but this is called when the
    //               interval is being played backwards; it indicates that
    //               the interval should start at the finishing state and
    //               undo any intervening intervals.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        priv_reverse_initialize(double t) {
            recompute();
            _state = S_started;
            _prev_d = 1.0;
            priv_step(t);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::reverse_instant
    //       Access: Published, Virtual
    //  Description: This is called in lieu of priv_reverse_initialize()
    //               .. priv_step() .. priv_reverse_finalize(), when everything is
    //               to happen within one frame.  The interval should
    //               initialize itself, then leave itself in the initial
    //               state.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        priv_reverse_instant() {
            recompute();
            _state = S_started;
            _prev_d = 1.0;
            priv_step(0.0);
            _state = S_initial;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::setup_slerp
    //       Access: Private
    //  Description: Sets up a spherical lerp from _start_quat to
    //               _end_quat.  This precomputes some important values
    //               (like the angle between the quaternions) and sets up
    //               the _slerp method pointer.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        setup_slerp() {
            /*
            if (_start_quat.dot(_end_quat) < 0.0f) {
            // Make sure both quaternions are on the same side.
            _start_quat = -_start_quat;
            }

            _slerp_angle = _start_quat.angle_rad(_end_quat);

            if (_slerp_angle < 0.1f) {
            // If the angle is small, use sin(angle)/angle as the denominator,
            // to provide better behavior with small divisors.  This is Don
            // Hatch's suggestion from http://www.hadron.org/~hatch/rightway.php .
            _slerp_denom = csin_over_x(_slerp_angle);
            _slerp = &TLerpSceneNodeInterval::slerp_angle_0;

            } else if (_slerp_angle > 3.14) {
            // If the angle is close to 180 degrees, the lerp is ambiguous.
            // which plane should we lerp through?  Better pick an
            // intermediate point to resolve the ambiguity up front.

            // We pick it by choosing a linear point between the quats and
            // normalizing it out; this will give an arbitrary point when the
            // angle is exactly 180, but will behave sanely as the angle
            // approaches 180.
            _slerp_c = (_start_quat + _end_quat);
            _slerp_c.normalize();
            _slerp_angle = _end_quat.angle_rad(_slerp_c);
            _slerp_denom = csin(_slerp_angle);

            _slerp = &TLerpSceneNodeInterval::slerp_angle_180;

            } else {
            // Otherwise, use the original Shoemake equation for spherical
            // lerp.
            _slerp_denom = csin(_slerp_angle);
            _slerp = &TLerpSceneNodeInterval::slerp_basic;
            }

            nassertv(_slerp_denom != 0.0f);
            _flags |= F_slerp_setup;
            */
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::slerp_basic
    //       Access: Private
    //  Description: Implements Ken Shoemake's spherical lerp equation.
    //               This is appropriate when the angle between the
    //               quaternions is not near one extreme or the other.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        slerp_basic(TQuaternion &result, float t) const {
            /*
            nassertv(_slerp_denom != 0.0f);
            float ti = 1.0f - t;
            float ta = t * _slerp_angle;
            float tia = ti * _slerp_angle;

            if (interval_cat.is_spam()) {
            interval_cat.spam()
            << "slerp_basic, (t = " << t << "), angle = " << _slerp_angle << "\n"
            << "_start_quat = " << _start_quat << ", _end_quat = "
            << _end_quat << ", denom = " << _slerp_denom << "\n";
            }

            result = (csin(tia) * _start_quat + csin(ta) * _end_quat) / _slerp_denom;
            nassertv(!result.is_nan());
            */
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::slerp_angle_0
    //       Access: Private
    //  Description: Implements Don Hatch's modified spherical lerp
    //               equation, appropriate for when the angle between the
    //               quaternions approaches zero.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        slerp_angle_0(TQuaternion &result, float t) const {
            /*
            nassertv(_slerp_denom != 0.0f);
            float ti = 1.0f - t;
            float ta = t * _slerp_angle;
            float tia = ti * _slerp_angle;

            if (interval_cat.is_spam()) {
            interval_cat.spam()
            << "slerp_angle_0, (t = " << t << "), angle = " << _slerp_angle
            << "\n_start_quat = " << _start_quat << ", _end_quat = "
            << _end_quat << ", denom = " << _slerp_denom << "\n";
            }

            result = (csin_over_x(tia) * ti * _start_quat + csin_over_x(ta) * t * _end_quat) / _slerp_denom;
            nassertv(!result.is_nan());
            */
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TLerpSceneNodeInterval::slerp_angle_180
    //       Access: Private
    //  Description: Implements a two-part slerp, to an intermediate point
    //               and out again, appropriate for when the angle between
    //               the quaternions approaches 180 degrees.
    ////////////////////////////////////////////////////////////////////
    void TLerpSceneNodeInterval::
        slerp_angle_180(TQuaternion &result, float t) const {
            /*
            nassertv(_slerp_denom != 0.0f);
            if (t < 0.5) {
            // The first half of the lerp: _start_quat to _slerp_c.

            t *= 2.0f;

            float ti = 1.0f - t;
            float ta = t * _slerp_angle;
            float tia = ti * _slerp_angle;

            if (interval_cat.is_spam()) {
            interval_cat.spam()
            << "slerp_angle_180, first half (t = " << t << "), angle = "
            << _slerp_angle << "\n_start_quat = " << _start_quat
            << ", _slerp_c = " << _slerp_c << ", denom = " 
            << _slerp_denom << "\n";
            }

            result = (csin(tia) * _start_quat + csin(ta) * _slerp_c) / _slerp_denom;

            } else {
            // The second half of the lerp: _slerp_c to _end_quat.
            t = t * 2.0f - 1.0f;

            float ti = 1.0f - t;
            float ta = t * _slerp_angle;
            float tia = ti * _slerp_angle;

            if (interval_cat.is_spam()) {
            interval_cat.spam()
            << "slerp_angle_180, second half (t = " << t << "), angle = "
            << _slerp_angle << "\n_slerp_c = " << _slerp_c
            << ", _end_quat = " << _end_quat << ", denom = " 
            << _slerp_denom << "\n";
            }

            result = (csin(tia) * _slerp_c + csin(ta) * _end_quat) / _slerp_denom;
            }

            nassertv(!result.is_nan());
            */
    }

}