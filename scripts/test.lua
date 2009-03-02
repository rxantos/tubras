-----------------------------------------------------------------------------
--                              m i n i m a l
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
--                          h a n d l e E v e n t
-----------------------------------------------------------------------------
function handleEvent(event)
    id = event:getID()
   
    print('handleEvent Invoked')

    if id == ID_QUIT then
        app:stopRunning()
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
app = tubras.getApplication() -- save Application reference

app:setWindowCaption('tse - minimal.lua')
app:setBGColor(100, 101, 140)
ID_QUIT = app:acceptEvent('quit', handleEvent)
ID_PLAY = app:acceptEvent('key.down.p', handleEvent)

--
-- config (CLSL) tests
--
config = app:getConfig()
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
nconfig = tubras.CLSL()
status = nconfig:loadScript('test.lsl')
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
mdl = app:loadModel('mdl/Cube.irrmesh')
--
-- set position via "Pos" attribute
mdl.Pos = tubras.TVector3(0.0, 0.0, -30.0)
mdlPosition = mdl.Pos
-- or
mdl:setPosition(vec)

--
-- Controller testing
--
rotController = tubras.TRotateController('cubeRotator', mdl, -75.0)

--
-- Sound testing
--
asound = app:loadSound('snd/ambient.ogg')
asound:play()

-- return status:  0 (or no return) - success, !=0 - error
return 0
