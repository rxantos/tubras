-----------------------------------------------------------------------------
--                                m a i n
-----------------------------------------------------------------------------
require 'SplashState'
require 'MenuState'
require 'OptionsState'
require 'PlayState'
require 'PauseState'

tse:setWindowCaption('mokena')
tse:enableMovement(false)
return {SplashState, MenuState, OptionsState, PlayState, PauseState}

