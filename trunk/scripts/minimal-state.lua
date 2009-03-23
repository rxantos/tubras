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
--
-- Instantiate our state and public methods
--
Minimal = {
    name='Minimal',
    updateFrequency=1000,

    onQuit = function (event)
        print('handleQuit Invoked')
        app:stopRunning()
        return 1
    end,
    
    initialize = function()
        app:setBGColor(100, 101, 140)
    end,

    enter = function() 
        app:acceptEvent('quit', Minimal.onQuit)
    end,

    exit = function()
        app:removeEvent('quit', Minimal.onQuit)
    end,

    pause = function()
    end,

    resume = function(stateInfo)
    end,

    update = function(delta)
    end,
}

--
-- tse script required function for state logic.  Return one or more state names.
-- The first state will be the initial state.
--
function getStates()
    return {Minimal}
end

-----------------------------------------------------------------------------
--                                m a i n
-----------------------------------------------------------------------------
app = tubras.getApplication()

