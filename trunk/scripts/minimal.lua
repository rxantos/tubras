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

-- return (number/bool):  0 (or no return) - success, !=0 - error
-- return (table): - success, but also enables state initialization. see
--    minimal-state.lua for an example.
return 0
