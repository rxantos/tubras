-----------------------------------------------------------------------------
--                          m i n i m a l - t s e
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
--                           h a n d l e Q u i t
-----------------------------------------------------------------------------
function handleQuit(event)
    print('handleQuit Invoked')
    app:stopRunning()
    return 1
end

-----------------------------------------------------------------------------
--                               M i n i m a l
-----------------------------------------------------------------------------
-- "Minimal" tse state handler. Required functions:
--      "initialize" - called once during application initialization.
--           "enter" - called when the state is entered.
--           "exit"  - called when the state is exited.
--          "pause"  - called when the state is paused.
--         "resume"  - called when the state is resumed from being paused.
--
-- Optional functions:
--         "update"  - called every "updateFrequency" milli-seconds.  If 
--                     func or "updateFrequence" is undefined, then "update
--                     isn't invoked.  "delta" will contain the number of 
--                     milli-seconds since the last invocation.
-----------------------------------------------------------------------------
Minimal = {name='Minimal',updateFrequency=1000}

function Minimal.initialize()
    app:setBGColor(100, 101, 140)
end

function Minimal.enter()
    app:acceptEvent('quit', handleQuit)
end

function Minimal.exit()
    app:removeEvent('quit', handleQuit)
end

function Minimal.pause()
end

function Minimal.resume()
end

function Minimal.update(delta)
end

--
-- tse script required function.  Return one or more state names.
-- The first state will be the initial state.
--
function getStates()
    return {Minimal}
end

-----------------------------------------------------------------------------
--                                m a i n
-----------------------------------------------------------------------------
app = tubras.getApplication()

