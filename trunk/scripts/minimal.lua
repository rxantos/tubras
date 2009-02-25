--
-- The tubras module is named "tubras" and is automatically added 
-- by tse. 
--
-- All "print" output is redirected to the application log file.
-- 
app = tubras.getApplication() -- save Application reference

function handleEscape(event)
    id = event:getID()
    
    print('handleEscape Invoked')

    if id == IDEscape then
        app:stopRunning()
        return 1
    end
    
    return 0
end

app:setWindowCaption('tse - minimal.lua')

app:setBGColor(100, 101, 140)

IDEscape = app:acceptEvent('quit', handleEscape)

-- return status:  0 (or no return) - success, !=0 - error
return 0
