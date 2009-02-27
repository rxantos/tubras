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
vec = tubras.TVector3(15.5)
vec2 = tubras.TVector3(1.1, 2.2, 3.3)

print('vec', vec, vec.X, vec.Y, vec.Z)

vec3 = vec + vec2
print('vec3', vec3.X, vec3.Y, vec3.Z)

-- return status:  0 (or no return) - success, !=0 - error
return 0
