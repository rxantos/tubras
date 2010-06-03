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


        class EvaluatorU8 : public IEvaluator<u8> {
        public:
            void evaluate(const u8& v0, const u8& v1, u8& out, float fraction) {
                out = v0 + (u8)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorS8 : public IEvaluator<s8> {
        public:
            void evaluate(const s8& v0, const s8& v1, s8& out, float fraction) {
                out = v0 + (s8)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorU16 : public IEvaluator<u16> {
        public:
            void evaluate(const u16& v0, const u16& v1, u16& out, float fraction) {
                out = v0 + (u16)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorS16 : public IEvaluator<s16> {
        public:
            void evaluate(const s16& v0, const s16& v1, s16& out, float fraction) {
                out = v0 + (s16)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorU32 : public IEvaluator<u32> {
        public:
            void evaluate(const u32& v0, const u32& v1, u32& out, float fraction) {
                out = v0 + (u32)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorS32 : public IEvaluator<s32> {
        public:
            void evaluate(const s32& v0, const s32& v1, s32& out, float fraction) {
                out = v0 + (s32)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorF32 : public IEvaluator<f32> {
        public:
            void evaluate(const f32& v0, const f32& v1, f32& out, float fraction) {
                out = v0 + (f32)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorF64 : public IEvaluator<f64> {
        public:
            void evaluate(const f64& v0, const f64& v1, f64& out, float fraction) {
                out = v0 + (f64)((v1 - v0) * fraction);
            }    
        };

        class EvaluatorSColor : public IEvaluator<SColor> {
        public:
            void evaluate(const SColor& v0, const SColor& v1, SColor& out, float fraction) {
                out = v0.getInterpolated(v1, fraction);
            }    
        };

        class EvaluatorVector2df : public IEvaluator<core::vector2d<f32>> {
        public: 
            void evaluate(core::vector2d<f32>& v0, core::vector2d<f32>& v1,
                core::vector2d<f32>& out, float fraction) {
                out.X = v0.X + ((v1.X - v0.X) * fraction);
                out.Y = v0.Y + ((v1.Y - v0.Y) * fraction);
            }
        };

        class EvaluatorVector2di : public IEvaluator<core::vector2d<s32>> {
        public: 
            void evaluate(core::vector2d<s32>& v0, core::vector2d<s32>& v1,
                core::vector2d<s32>& out, float fraction) {
                out.X = v0.X + (s32)((v1.X - v0.X) * fraction);
                out.Y = v0.Y + (s32)((v1.Y - v0.Y) * fraction);
            }
        };

        class EvaluatorVector3df : public IEvaluator<core::vector3d<f32>> {
        public: 
            void evaluate(core::vector3d<f32>& v0, core::vector3d<f32>& v1,
                core::vector3d<f32>& out, float fraction) {
                out.X = v0.X + ((v1.X - v0.X) * fraction);
                out.Y = v0.Y + ((v1.Y - v0.Y) * fraction);
                out.Z = v0.Z + ((v1.Z - v0.Z) * fraction);
            }
        };

        class EvaluatorVector3di : public IEvaluator<core::vector3d<s32>> {
        public: 
            void evaluate(core::vector3d<s32>& v0, core::vector3d<s32>& v1,
                core::vector3d<s32>& out, float fraction) {
                out.X = v0.X + (s32)((v1.X - v0.X) * fraction);
                out.Y = v0.Y + (s32)((v1.Y - v0.Y) * fraction);
                out.Z = v0.Z + (s32)((v1.Z - v0.Z) * fraction);
            }
        };
    }
}
#endif
