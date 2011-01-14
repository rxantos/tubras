app = TubrasApp
v = TVector3(1.45, 2.0, 3.0)
v.x = v.x + 2.5
v.xyz = 123
app:logMessage('Hello from test2.lua')

print('v.x: ' .. tostring(v.x))
print('v.y: ' .. tostring(v.y))

v:normalize()
print('v.x: ' .. tostring(v.x))
print('v.y: ' .. tostring(v.y))

v.x = 33
print('v.x: ' .. tostring(v.x))
print('v.xyz: ' .. tostring(v.xyz))


-- registered enum
print('rmWire: ' .. tostring(rmWire))


function handleEvent(event)
    id = event.id
    app:logMessage('handleEvent() id=' .. tostring(id))
    if id == ID_QUIT then
        app:stopRunning()
    end
    return 1
end

print('app: ' .. tostring(app))
ID_QUIT = app:acceptEvent('quit', handleEvent)

--[[
v = TVector3()

v = TVector3:new()
x = v:get_X(1.5, 2.0, 3.0)

app:logMessage('v.X: ' .. x)

TubrasApp:logMessage('this is a test')

app:logMessage('test using "tse"')

s = 'Test Window'

app:setWindowCaption(s)

event_id = app:acceptEvent('quit', handleEvent)
ID_QUIT = event_id
app:logMessage('event_id: ' .. tostring(event_id))

event_id = app:acceptEvent('quit2', handleEvent)
app:logMessage('event_id: ' .. tostring(event_id))
]]--

return 0
