-----------------------------------------------------------------------------
--                                m a i n
-----------------------------------------------------------------------------
require 'SplashState'
require 'MenuState'
require 'OptionsState'
require 'PlayState'
require 'PauseState'

app = tubras.getApplication()

return {SplashState, MenuState, OptionsState, PlayState, PauseState}

