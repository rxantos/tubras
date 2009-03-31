local ambientSound = nil
local background = nil
local finterval = nil
local mokenaLogo = nil
local INTERVAL_DURATION=7
local DIRECTION=0
local MAX_BLUE=128

-----------------------------------------------------------------------------
--                              o n Q u i t
-----------------------------------------------------------------------------
local function onQuit(event)
    tse:stopRunning()
    return 1
end

-----------------------------------------------------------------------------
--                     a d j us t B a c k g r o u n d
-----------------------------------------------------------------------------
local function adjustBackground(delta)
    if DIRECTION == 1 then
        v = delta / INTERVAL_DURATION
    else
        v = 1.0 - (delta / INTERVAL_DURATION)
    end
    value = MAX_BLUE * v
    tse:setBGColor(0,0,value)
end

-----------------------------------------------------------------------------
--                          m e n u B G D o n e
-----------------------------------------------------------------------------
local function menuBGDone(event)
    if DIRECTION == 1 then
        DIRECTION = 0
    else
        DIRECTION = 1
    end
    finterval:start()
end

-----------------------------------------------------------------------------
--                          i n i t i a l i z e
-----------------------------------------------------------------------------
local function initialize()
    ambientSound = tse:loadSound('snd/mokena/ambient.ogg')
    ambientSound:setLoop(true)

    background = tse:addBackgroundNode('tex/mokena/menubg.tga')
    background:setVisible(false)

    finterval = tse:addFunctionInterval('menu:adjustBackground', adjustBackground, 
        INTERVAL_DURATION, btNoBlend)
    finterval:setStopEvent('MenuBGDone')
    tse:acceptEvent('MenuBGDone', menuBGDone)

    mokenaLogo = tse:addGUIImage('tex/mokena/mokena.tga')
    mokenaLogo:setVisible(false)
    mokenaLogo:setUseAlphaChannel(true)
    
end

-----------------------------------------------------------------------------
--                              e n t e r
-----------------------------------------------------------------------------
local function enter() 
    tse:setBGColor(0,0,128)
    tse:acceptEvent('quit', onQuit)
    tse:setGUICursorEnabled(true)
    tse:centerGUICursor()
    background:setVisible(true)
    mokenaLogo:setVisible(true)
    ambientSound:play()
    finterval:start()
end

-----------------------------------------------------------------------------
--                               e x i t
-----------------------------------------------------------------------------
local function exit()
    ambientSound:stop()
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

