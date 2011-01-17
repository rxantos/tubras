app = TubrasApp
print('app: ' .. tostring(app))
app:logMessage('Hello from test.lua')

-- vector3 tests
v = TVector3(1.45, 2.0, 3.0)
print(v)
print(tostring(v,1))

v.x = v.x + 2.5
v.xyz = 123

print('v: ' .. tostring(v))

v:normalize()
print('v (normalized): ' .. tostring(v))

v.x = 33
print('v: ' .. tostring(v))

v1 = TVector3(1.5, 2.5, 3.5)
v2 = TVector3(3.5, 2.5, 1.5)

v3 = v1 + v2
print('v3: ' .. tostring(v3))
v3 = v3 + 1.5
print('v3: ' .. tostring(v3))

v3 = v1 + 'test'
print('v3: ' .. tostring(v3))

v3 = v3 * 2.0
v3.y = -v3.y
print('v3: ' .. tostring(v3))

v4 = -v3
print('v4: ' .. tostring(v4))

v2.x = v1.x
v2.y = v1.y
v2.z = v1.z
print(tostring(v1))
print(tostring(v2))

if v1 == v2 then
    print('v1 == v2')
else
    print('v1 != v2')
end

if v1 == v1 then
    print('v1 == v1')
else
    print('v1 != v1')
end

print('***: ' .. tostring(v1, true))

-- registered enum
print('rmWire: ' .. tostring(rmWire))

--]]
-- event handler
function handleEvent(event)
    id = event.id
    app:logMessage('handleEvent() id=' .. tostring(id))
    if id == ID_QUIT then
        app:stopRunning()
    end
    return 1
end

-- handle 'quit' event
ID_QUIT = app:acceptEvent('quit', handleEvent)

return 0

--[[
-----------------------------------------------------------------------------
--                          h a n d l e E v e n t
-----------------------------------------------------------------------------
function handleEvent(event)
    id = event:getID()
   
    print('handleEvent Invoked')

    if id == ID_QUIT then
        tse:stopRunning()
        return 1
    elseif id == ID_PLAY then
        if asound:isPlaying() then            
            asound:stop()
            mdl:setVisible(false)
        else
            asound:play()
            mdl:setVisible(true)
        end
        return 1
    end
    
    return 0
end

-----------------------------------------------------------------------------
--                                m a i n
-----------------------------------------------------------------------------
tse:setWindowCaption('tse - test.lua')
tse:setBGColor(100, 101, 140)
ID_QUIT = tse:acceptEvent('quit', handleEvent)
ID_PLAY = tse:acceptEvent('key.down.p', handleEvent)

--
-- config (TSL) tests
--
config = tse:getConfig()
colordepth = config:getInteger('video.colordepth')
guiskin = config:getString('video.guiskin')
velocity = config:getFloat('options.velocity')
teststring = config:getString('options.teststring')
deftest = config:getString('options.badvar', 'defvalue')

print('colordepth=' .. tostring(colordepth))
print('guiskin=' .. guiskin)
print('velocity=' .. tostring(velocity))
print('teststring=' .. teststring)
print('deftest=' .. deftest)

--
-- new config instance
--
nconfig = tubras.TSL()
status = nconfig:loadScript('test.tsl')
print('loadScript returned: ' .. tostring(status))
if status == E_OK then
    print('loadScript successful')
else
    print('loadScript failed')
end

--
-- TVector3 tests
--
vec = tubras.TVector3(0.0, 0.0, -70)
vec2 = tubras.TVector3(1.1, 2.2, 3.3)

print('vec', vec, vec.X, vec.Y, vec.Z)

vec3 = vec + vec2
print('vec3', vec3.X, vec3.Y, vec3.Z)

--
-- Model/Scene Node testing
--
--mdl = tse:loadModel('mdl/Cube.irrmesh')
--bigMesh = tse:loadModel('mdl/BigMesh.irrmesh')
--
-- set position via "Pos" attribute
--mdl.Pos = tubras.TVector3(0.0, 0.0, -30.0)
--mdlPosition = mdl.Pos
-- or
--mdl:setPosition(vec)

--
-- Particle testing - programmatic creation
--
ptype = tubras.PP_BILLBOARD
--ptype = tubras.PP_POINT
--ptype = tubras.PP_POINTSPRITE

pnode = tse:createParticleNode('testNode', 500, ptype)

domain = tubras.TCylinderDomain(tubras.TVector3(0.0, 0.25, -0.01), 
    tubras.TVector3(0.0, 0.27, -0.01), 0.021, 0.019)
--domain = tubras.TParticleDomain()

pnode:setVelocity(domain)
pnode:setColor(tubras.TLineDomain(tubras.TVector3(0.8, 0.9,1.0),
    tubras.TVector3(0.0, 0.0, 1.0)))

source = tubras.TSourceAction(5,tubras.TLineDomain(tubras.TVector3(0,0,0),
    tubras.TVector3(0,0.4,0)))
pnode:addAction(source)

gravity = tubras.TGravityAction(tubras.TVector3(0,-0.0025,0))
pnode:addAction(gravity)

bounce = tubras.TBounceAction(-0.05, 0.35, 0, 
    tubras.TDiscDomain(tubras.TVector3(0,0,0),
    tubras.TVector3(0,1,0),5))
pnode:addAction(bounce)

sink = tubras.TSinkAction(false,tubras.TPlaneDomain(tubras.TVector3(0,-3,0), 
    tubras.TVector3(0,1,0)))
pnode:addAction(sink)

size = tubras.TSizeAction(tubras.TVector3(0.1,0.1,1), tubras.TVector3(0.01, 0.01, 0.01))
pnode:addAction(size)

-- 2nd parm enables/disables alpha blending
--pnode:setSpriteImage('tex/lamp.tga', true)
pnode:setSpriteImage('tex/star.png', true)

pnode:setPointSize(15.0)
pnode:setSpeed(0.5)

--
-- Eventually we'll be able to define particles in a .tsl file 
-- and simply load them via:
--
-- pnode = tse:loadParticle('particles.tsl', 'TestParticle')
--
--
TestParticle = {
    primitive = tubras.PP_POINTSPRITE,
    source = { 
        actionType = tubras.ET_SOURCEACTION,
        domain = { 
            tubras.ET_LINEDOMAIN, 
            {0, 0, 0}, 
            {0, 0.4, 0}
        }
    },
    color = {0.8, 0.8, 0.8}, 
    -- or
    color = {
        domain = {
            tubras.ET_LINEDOMAIN, 
            {0.8, 0.9,1.0}, 
            {0, 0, 1}
        }
    },
    
    velocity = TCylinderDomain {
        {0, 0.25, -0.01},
        {0, 0.27, -0.01},
        0.021,
        0.019
    }
    gravity = {
        actionType = tubras.ET_GRAVITYACTION,
        domain = {
            tubras.ET_VECTOR3,
            {0, -0.0025, 0}
        }
    }
    bounce = {
        actionType = tubras.ET_BOUNCEACTION,
        domain = {
            tubras.ET_DISCDOMAIN,
            {0, 0, 0},
            {0, 1, 0},
            5
        }
    }
    sink  = {
        actionType = tubras.ET_SINKACTION,
        domain = {
            tubras.ET_PLANEDOMAIN,
            {0, -3, 0},
            {0, 1, 0}
        }
    }
}


--
-- Controller testing
--
rotController = tubras.TRotateController('cubeRotator', mdl, -75.0)

--
-- Sound testing
--
asound = tse:loadSound('snd/mokena/ambient.ogg')
asound:play()


-- return status:  0 (or no return) - success, !=0 - error
return 0
--]]

