local finterval = nil
local finterval2 = nil
local ALPHA_DURATION = 2
local ALPHA_DIRECTION = 1
local splashImage = nil
local sound = nil

-----------------------------------------------------------------------------
--                          a d j u s t A l p h a
-----------------------------------------------------------------------------
local function adjustAlpha(delta)
    if ALPHA_DIRECTION == 1 then
        splashImage:setAlpha(delta / ALPHA_DURATION)
    else
        splashImage:setAlpha(1.0 - (delta / ALPHA_DURATION))
    end
end

-----------------------------------------------------------------------------
--                           a l p h a D o n e
-----------------------------------------------------------------------------
local function alphaDone(event)
    if ALPHA_DIRECTION == 1 then
        ALPHA_DIRECTION = 0
        finterval2:start()
    else
        splashImage:setAlpha(1.0)
        sound:play()
    end
    return 1
end

-----------------------------------------------------------------------------
--                           a l p h a D o n e
-----------------------------------------------------------------------------
local function splashDone(event)
    -- splash is a one-off so pop it before moving on to the next state.
    tse:popState()
    tse:pushState('Menu')
    return 1
end

-----------------------------------------------------------------------------
--                          i n i t i a l i z e
-----------------------------------------------------------------------------
local function initialize()
    tse:setBGColor(0,0,0)
    tse:setCursorVisible(false)
    tse:setGUICursorEnabled(false)

    finterval = tse:addFunctionInterval('alphaUp', adjustAlpha, 
        ALPHA_DURATION, tubras.btNoBlend, '', 'alphaDoneEvent')
    finterval2 = tse:addFunctionInterval('alphaDown', adjustAlpha, 
        ALPHA_DURATION, tubras.btNoBlend, '', 'alphaDoneEvent')
    tse:acceptEvent('alphaDoneEvent', alphaDone)

    sound = tse:loadSound('mokena/snd/tubras.ogg','soundFinishedEvent')
    tse:acceptEvent('soundFinishedEvent', splashDone)

    splashImage = tse:addGUIImage('mokena/tex/splash.tga',-1,-1,-1,-1,false)
    splashImage:setVisible(false)
    splashImage:setUseAlphaChannel(true)
    splashImage:setAlpha(0)
end

-----------------------------------------------------------------------------
--                              e n t e r
-----------------------------------------------------------------------------
local function enter() 
    finterval:start()
    splashImage:setVisible(true)
end

-----------------------------------------------------------------------------
--                               e x i t
-----------------------------------------------------------------------------
local function exit()
    splashImage:setVisible(false)
end

-----------------------------------------------------------------------------
--                        S p l a s h S t a t e
-----------------------------------------------------------------------------
SplashState = {
    name='Splash',
    initialize = initialize,
    enter = enter,
    exit = exit,
}

