local finterval=nil
local ALPHA_DURATION = 0.8

-----------------------------------------------------------------------------
--                          a d j u s t A l p h a
-----------------------------------------------------------------------------
local function adjustAlpha(delta)
    print('adjustAlpha:', delta)
end

-----------------------------------------------------------------------------
--                           a l p h a D o n e
-----------------------------------------------------------------------------
local function alphaDone(event)
    print('alphaDone')
    -- splash is a one-off so pop it before moving on to the next state.
    app:popState()
    app:pushState('Menu')
    return 1
end

-----------------------------------------------------------------------------
--                          i n i t i a l i z e
-----------------------------------------------------------------------------
local function initialize()
    app:setBGColor(100, 101, 140)

    finterval = app:addFunctionInterval('alphaUp', adjustAlpha, 
        ALPHA_DURATION, tubras.btNoBlend, '', 'alphaDoneEvent')

    app:acceptEvent('alphaDoneEvent', alphaDone)
end

-----------------------------------------------------------------------------
--                              e n t e r
-----------------------------------------------------------------------------
local function enter() 
    finterval:start()
end

-----------------------------------------------------------------------------
--                               e x i t
-----------------------------------------------------------------------------
local function exit()
    print('SplashState exit()')

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

