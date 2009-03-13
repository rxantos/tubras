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
-- All of our state related functions are "private" by default via "local".
-- This allows us to later which of those functions are publicly exposed.
-----------------------------------------------------------------------------
local function initialize()
    app:setBGColor(100, 101, 140)
end

local function enter()
    app:acceptEvent('quit', handleQuit)
end

local function exit()
    app:removeEvent('quit', handleQuit)
end

local function pause()
end

local function resume()
end

local function update(delta)
end

--
-- Instantiate our state and public methods
--
Minimal = {
    name='Minimal',
    updateFrequency=1000,
    initialize = initilaize,
    enter = enter,
    exit = exit,
    pause = pause,
    resume = resume,
    update = update,
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

