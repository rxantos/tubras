//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __I_EVALUATOR_H_INCLUDED__
#define __I_EVALUATOR_H_INCLUDED__
namespace irr
{
    namespace timing
    {
        template <class T>
        class IEvaluator
        {
        public:
            virtual void evaluate(const T& v0, const T& v1, T& out, float fraction) = 0;
        };


        class CEvaluatorU8 : public IEvaluator<u8> {
        public:
            void evaluate(const u8& v0, const u8& v1, u8& out, float fraction) {
                out = v0 + (u8)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorS8 : public IEvaluator<s8> {
        public:
            void evaluate(const s8& v0, const s8& v1, s8& out, float fraction) {
                out = v0 + (s8)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorU16 : public IEvaluator<u16> {
        public:
            void evaluate(const u16& v0, const u16& v1, u16& out, float fraction) {
                out = v0 + (u16)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorS16 : public IEvaluator<s16> {
        public:
            void evaluate(const s16& v0, const s16& v1, s16& out, float fraction) {
                out = v0 + (s16)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorU32 : public IEvaluator<u32> {
        public:
            void evaluate(const u32& v0, const u32& v1, u32& out, float fraction) {
                out = v0 + (u32)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorS32 : public IEvaluator<s32> {
        public:
            void evaluate(const s32& v0, const s32& v1, s32& out, float fraction) {
                out = v0 + (s32)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorF32 : public IEvaluator<f32> {
        public:
            void evaluate(const f32& v0, const f32& v1, f32& out, float fraction) {
                out = v0 + (f32)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorF64 : public IEvaluator<f64> {
        public:
            void evaluate(const f64& v0, const f64& v1, f64& out, float fraction) {
                out = v0 + (f64)((v1 - v0) * fraction);
            }    
        };

        class CEvaluatorSColor : public IEvaluator<SColor> {
        public:
            void evaluate(const SColor& v0, const SColor& v1, SColor& out, float fraction) {
                out = v0.getInterpolated(v1, fraction);
            }    
        };

        class CEvaluatorVector2df : public IEvaluator<core::vector2d<f32>> {
        public: 
            void evaluate(core::vector2d<f32>& v0, core::vector2d<f32>& v1,
                core::vector2d<f32>& out, float fraction) {
                out.X = v0.X + ((v1.X - v0.X) * fraction);
                out.Y = v0.Y + ((v1.Y - v0.Y) * fraction);
            }
        };

        class CEvaluatorVector2di : public IEvaluator<core::vector2d<s32>> {
        public: 
            void evaluate(core::vector2d<s32>& v0, core::vector2d<s32>& v1,
                core::vector2d<s32>& out, float fraction) {
                out.X = v0.X + (s32)((v1.X - v0.X) * fraction);
                out.Y = v0.Y + (s32)((v1.Y - v0.Y) * fraction);
            }
        };

        class CEvaluatorVector3df : public IEvaluator<core::vector3d<f32>> {
        public: 
            void evaluate(core::vector3d<f32>& v0, core::vector3d<f32>& v1,
                core::vector3d<f32>& out, float fraction) {
                out.X = v0.X + ((v1.X - v0.X) * fraction);
                out.Y = v0.Y + ((v1.Y - v0.Y) * fraction);
                out.Z = v0.Z + ((v1.Z - v0.Z) * fraction);
            }
        };

        class CEvaluatorVector3di : public IEvaluator<core::vector3d<s32>> {
        public: 
            void evaluate(core::vector3d<s32>& v0, core::vector3d<s32>& v1,
                core::vector3d<s32>& out, float fraction) {
                out.X = v0.X + (s32)((v1.X - v0.X) * fraction);
                out.Y = v0.Y + (s32)((v1.Y - v0.Y) * fraction);
                out.Z = v0.Z + (s32)((v1.Z - v0.Z) * fraction);
            }
        };

        class CEvaluatorLine2df : public IEvaluator<core::line2d<f32>> {
        public:
            void evaluate(const core::line2d<f32>& v0, const core::line2d<f32>& v1,
                core::line2d<f32>& out, float fraction) {
                out.start.X =  v0.start.X + ((v1.start.X - v0.start.X) * fraction);
                out.start.Y =  v0.start.Y + ((v1.start.Y - v0.start.Y) * fraction);
                out.end.X =  v0.end.X + ((v1.end.X - v0.end.X) * fraction);
                out.end.Y =  v0.end.Y + ((v1.end.Y - v0.end.Y) * fraction);
            }
        };

        class CEvaluatorLine2di : public IEvaluator<core::line2d<s32>> {
        public:
            void evaluate(const core::line2d<s32>& v0, const core::line2d<s32>& v1,
                core::line2d<s32>& out, float fraction) {
                out.start.X =  v0.start.X + (s32)((v1.start.X - v0.start.X) * fraction);
                out.start.Y =  v0.start.Y + (s32)((v1.start.Y - v0.start.Y) * fraction);
                out.end.X =  v0.end.X + (s32)((v1.end.X - v0.end.X) * fraction);
                out.end.Y =  v0.end.Y + (s32)((v1.end.Y - v0.end.Y) * fraction);
            }
        };

        class CEvaluatorRectf : public IEvaluator<core::rectf> {
        public:
            void evaluate(const core::rectf& v0, const core::rectf& v1,
                core::rectf& out, float fraction) {
                out.UpperLeftCorner.X =  v0.UpperLeftCorner.X + ((v1.UpperLeftCorner.X - v0.UpperLeftCorner.X) * fraction);
                out.UpperLeftCorner.Y =  v0.UpperLeftCorner.Y + ((v1.UpperLeftCorner.Y - v0.UpperLeftCorner.Y) * fraction);
                out.LowerRightCorner.X =  v0.LowerRightCorner.X + ((v1.LowerRightCorner.X - v0.LowerRightCorner.X) * fraction);
                out.LowerRightCorner.Y =  v0.LowerRightCorner.Y + ((v1.LowerRightCorner.Y - v0.LowerRightCorner.Y) * fraction);
            }
        };

        class CEvaluatorRecti : public IEvaluator<core::recti> {
        public:
            void evaluate(const core::recti& v0, const core::recti& v1,
                core::recti& out, float fraction) {
                out.UpperLeftCorner.X =  v0.UpperLeftCorner.X + (s32)((v1.UpperLeftCorner.X - v0.UpperLeftCorner.X) * fraction);
                out.UpperLeftCorner.Y =  v0.UpperLeftCorner.Y + (s32)((v1.UpperLeftCorner.Y - v0.UpperLeftCorner.Y) * fraction);
                out.LowerRightCorner.X =  v0.LowerRightCorner.X + (s32)((v1.LowerRightCorner.X - v0.LowerRightCorner.X) * fraction);
                out.LowerRightCorner.Y =  v0.LowerRightCorner.Y + (s32)((v1.LowerRightCorner.Y - v0.LowerRightCorner.Y) * fraction);
            }
        };

        class CEvaluatorQuat : public IEvaluator<core::quaternion> {
        public:
            void evaluate(const core::quaternion& v0, const core::quaternion& v1,
                core::quaternion& out, float fraction) {
                    out.slerp(v0, v1, fraction);
            }
        };

        class CEvaluatorMatrix4 : public IEvaluator<core::matrix4> {
        public:
            void evaluate(const core::matrix4& v0, const core::matrix4& v1,
                core::matrix4& out, float fraction) {
                    out = v0.interpolate(v1, fraction);
            }
        };

        class CEvaluatorDimension2df : public IEvaluator<core::dimension2df> {
        public:
            void evaluate(const core::dimension2df& v0, const core::dimension2df& v1,
                core::dimension2df& out, float fraction) {
                out.Width = v0.Width + ((v1.Width - v0.Width) * fraction);
                out.Height = v0.Height + ((v1.Height - v0.Height) * fraction);
            }
        };

        class CEvaluatorDimension2di : public IEvaluator<core::dimension2di> {
        public:
            void evaluate(const core::dimension2di& v0, const core::dimension2di& v1,
                core::dimension2di& out, float fraction) {
                out.Width = v0.Width + (s32)((v1.Width - v0.Width) * fraction);
                out.Height = v0.Height + (s32)((v1.Height - v0.Height) * fraction);
            }
        };

        class CEvaluatorDimension2du : public IEvaluator<core::dimension2du> {
        public:
            void evaluate(const core::dimension2du& v0, const core::dimension2du& v1,
                core::dimension2du& out, float fraction) {
                out.Width = v0.Width + (u32)((v1.Width - v0.Width) * fraction);
                out.Height = v0.Height + (u32)((v1.Height - v0.Height) * fraction);
            }
        };

    }
}
#endif
