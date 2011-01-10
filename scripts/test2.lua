app = TubrasApp

app:logMessage('Hello App')

v = TVector3()

x = v.x

v:normalize()

--[[
function handleEvent(event)
    id = event:getID()
    app:logMessage('handleEvent() id=' .. tostring(id))
    if id == ID_QUIT then
        app:stopRunning()
    end
end

print('app: ' .. tostring(app))

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
