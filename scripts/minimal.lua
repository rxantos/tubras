--
-- The tubras module is named "tubras" and is automatically added 
-- by tse. 
--
-- All "print" output is redirected to the application log file.
-- 
app = tubras.getApplication() -- save Application reference

function handleEvent(event)
    id = event:getID()
   
    print('handleEvent Invoked')

    if id == ID_QUIT then
        app:stopRunning()
        return 1
    end
    
    return 0
end

app:setWindowCaption('tse - minimal.lua')

app:setBGColor(100, 101, 140)

ID_QUIT = app:acceptEvent('quit', handleEvent)

-- return status:  0 (or no return) - success, !=0 - error
return 0
