//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TVECTOR3_H_
#define _TVECTOR3_H_

namespace Tubras
{
    class TVector3 : public vector3df
    {
    public:
        TVector3(f32 nx=0.f, f32 ny=0.f, f32 nz=0.f) : vector3df(nx,ny,nz) {}
        TVector3(const vector3d<f32>& other) : vector3df(other) {}
        TVector3 toRadians();
        TVector3 toDegrees();
        ~TVector3() {}

        TVector3* operator=(const irr::core::vector3df& other) { X = other.X; Y = other.Y; Z = other.Z; return this; }

		TVector3 operator+(const TVector3& other) const { return TVector3(X + other.X, Y + other.Y, Z + other.Z); }
		TVector3& operator+=(const TVector3& other) { X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }

        // special points
        static const TVector3 ZERO;
        static const TVector3 UNIT_X;
        static const TVector3 UNIT_Y;
        static const TVector3 UNIT_Z;
        static const TVector3 NEGATIVE_UNIT_X;
        static const TVector3 NEGATIVE_UNIT_Y;
        static const TVector3 NEGATIVE_UNIT_Z;
        static const TVector3 UNIT_SCALE;
    };    

    // Proxy Class
    class LVector3 : public LProxyBase<TVector3> {
    public: 
        LVector3(TVector3& other);
        LVector3(lua_State* L);

        int getProperty(lua_State* L, const char* propName);
        int setProperty(lua_State* L, const char* propName, const TValue* propValue);

        int normalize(lua_State* L)
        {
            m_ptr->normalize();
            return 0;
        }

        int toRadians(lua_State* L)
        {
            TVector3 temp(m_ptr->toRadians());
            push_to_lua(L, new LVector3(temp));
            return 1;
        }

        int toDegrees(lua_State* L)
        {
            TVector3 temp(m_ptr->toDegrees());
            push_to_lua(L, new LVector3(temp));
            return 1;
        }

        int getLength(lua_State* L)
        {
            lua_pushnumber(L, m_ptr->getLength());
            return 1;
        }

        int getLengthSQ(lua_State* L)
        {
            lua_pushnumber(L, m_ptr->getLengthSQ());
            return 1;
        }

        int dotProduct(lua_State* L)
        {
            lua_pushnumber(L, 0);
            lua_rawget(L, 1);

            TVector3** obj = static_cast<TVector3**>(luaL_checkudata(L, -1, LVector3::className));
            lua_pop(L, 1); // remove userdata from the stack

            lua_pushnumber(L, m_ptr->dotProduct(**obj));
            return 1;
        }

        int getDistanceFrom(lua_State* L)
        {
            lua_pushnumber(L, 0);
            lua_rawget(L, 1);

            TVector3** obj = static_cast<TVector3**>(luaL_checkudata(L, -1, LVector3::className));
            lua_pop(L, 1); // remove userdata from the stack

            lua_pushnumber(L, m_ptr->getDistanceFrom(**obj));
            return 1;
        }

        int getDistanceFromSQ(lua_State* L)
        {
            lua_pushnumber(L, 0);
            lua_rawget(L, 1);

            TVector3** obj = static_cast<TVector3**>(luaL_checkudata(L, -1, LVector3::className));
            lua_pop(L, 1); // remove userdata from the stack

            lua_pushnumber(L, m_ptr->getDistanceFromSQ(**obj));
            return 1;
        }

        int crossProduct(lua_State* L)
        {
            lua_pushnumber(L, 0);
            lua_rawget(L, 1);

            TVector3** obj = static_cast<TVector3**>(luaL_checkudata(L, -1, LVector3::className));
            lua_pop(L, 1); // remove userdata from the stack

            TVector3 temp(m_ptr->crossProduct(**obj));
            push_to_lua(L, new LVector3(temp));
            return 1;
        }

        int getHorizontalAngle(lua_State* L)
        {
            TVector3 temp(m_ptr->getHorizontalAngle());
            push_to_lua(L, new LVector3(temp));
            return 1;
        }

        // meta method overrides
        int __tostring(lua_State* L);
        int __math(lua_State* L, const TValue* ovalue, LProxyBase<TVector3>* other, LPMathOp op);

        virtual int __compare(lua_State* L, LProxyBase<TVector3>* other, LPCompareOp op);

        static const TLuaProxy<LVector3>::RegType Register[];
    };

} 
#endif
