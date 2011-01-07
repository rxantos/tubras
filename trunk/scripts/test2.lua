app = TubrasApp

function handleEvent(event)
    id = event:getID()
    app:logMessage('handleEvent() id=' .. tostring(id))
    if id == ID_QUIT then
        app:stopRunning()
    end
end

TubrasApp:logMessage('this is a test')

app:logMessage('test using "tse"')

s = 'Test Window'

app:setWindowCaption(s)

event_id = app:acceptEvent('quit', handleEvent)
ID_QUIT = event_id
app:logMessage('event_id: ' .. tostring(event_id))

event_id = app:acceptEvent('quit2', handleEvent)
app:logMessage('event_id: ' .. tostring(event_id))

return 0
