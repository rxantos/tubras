local ambientSound = nil
-----------------------------------------------------------------------------
--                              o n Q u i t
-----------------------------------------------------------------------------
local function onQuit(event)
    app:stopRunning()
    return 1
end

-----------------------------------------------------------------------------
--                          i n i t i a l i z e
-----------------------------------------------------------------------------
local function initialize()
    ambientSound = app:loadSound('mokena/snd/ambient.ogg')
    ambientSound:setLoop(true)
end

-----------------------------------------------------------------------------
--                              e n t e r
-----------------------------------------------------------------------------
local function enter() 
    app:setBGColor(100, 101, 140)
    app:acceptEvent('quit', onQuit)
    app:setGUICursorEnabled(true)
    app:centerGUICursor()
    ambientSound:play()
end

-----------------------------------------------------------------------------
--                               e x i t
-----------------------------------------------------------------------------
local function exit()
    ambientSound:stop()
    app:removeEvent('quit', onQuit)
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
--                          M e n u S t a t e
-----------------------------------------------------------------------------
MenuState = {
    name='Menu',
    initialize = initialize,
    enter = enter,
    exit = exit,
    pause = pause,
    resume = resume,
}

