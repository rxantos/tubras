app = TubrasApp
print('app: ' .. tostring(app))
app:logMessage('Hello from test.lua')

-- list program arguments
args = app:args()
argc = table.getn(args)
print('args size: ' .. argc)
for i=1,argc do
    print(string.format('args[%d]: %s', i, args[i]))
end

-- config test
cfg = TConfig()
print('cfg: ' .. tostring(cfg))

cfg = app:getConfig()
print('cfg: ' .. tostring(cfg))
colordepth = cfg:getInteger('video.colordepth')
guiskin = cfg:getString('video.guiskin')
velocity = cfg:getFloat('options.velocity')
teststring = cfg:getString('options.teststring')
deftest = cfg:getString('options.badvar', 'defvalue')
v = cfg:getVector3('options:test')

print('colordepth=' .. tostring(colordepth))
print('guiskin=' .. guiskin)
print('velocity=' .. tostring(velocity))
print('teststring=' .. teststring)
print('deftest=' .. deftest)

-- color tests
c = TColor(255, 255, 255, 255)  -- r, g, b, a

print('c: ' .. tostring(c))

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

