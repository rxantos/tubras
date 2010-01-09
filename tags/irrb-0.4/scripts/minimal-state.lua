-----------------------------------------------------------------------------
--                          m i n i m a l - s t a t e
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

-----------------------------------------------------------------------------
--                              o n Q u i t
-----------------------------------------------------------------------------
local function onQuit(event)
    print('handleQuit Invoked')
    tse:stopRunning()
    return 1
end

-----------------------------------------------------------------------------
--                          i n i t i a l i z e
-----------------------------------------------------------------------------
local function initialize()
    tse:setBGColor(100, 101, 140)
end

-----------------------------------------------------------------------------
--                              e n t e r
-----------------------------------------------------------------------------
local function enter() 
    tse:acceptEvent('quit', onQuit)
end

-----------------------------------------------------------------------------
--                               e x i t
-----------------------------------------------------------------------------
local function exit()
    tse:removeEvent('quit', onQuit)
end

-----------------------------------------------------------------------------
--                              p a u s e
-----------------------------------------------------------------------------
local function pause()
end

-----------------------------------------------------------------------------
--                             r e s u m e
-----------------------------------------------------------------------------
local function resume(stateInfo)
end

-----------------------------------------------------------------------------
--                            u p d a t e
-----------------------------------------------------------------------------
local function update(delta)
end

-----------------------------------------------------------------------------
--                      M i n i m a l S t a t e
-----------------------------------------------------------------------------
MinimalState = {
    name='Minimal',
    updateFrequency=1000,
    onQuit = onQuit,
    
    initialize = initialize,
    enter = enter,
    exit = exit,
    pause = pause,
    resume = resume,
    update = update,
}

-----------------------------------------------------------------------------
--                                m a i n
-----------------------------------------------------------------------------
--
-- Instead of return success/error (0, >0), we return a table of states.
-- 
-- The first state will be the initial state.
--
return {MinimalState}

