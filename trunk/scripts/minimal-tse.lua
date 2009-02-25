-- The tubras module is named "tubras" and is automatically added 
-- by tse. Save off a reference to the Application object.
app = tubras.getApplication()

function handleEscape(event)
    print('handleEscape Invoked')
    app:stopRunning()
    return 1
end

--
-- state functions
--
Minimal = {}

function Minimal.initialize()
    tapp:setBGColor(100, 101, 140)
    tapp:acceptEvent('quit', handleEscape)
end

function Minimal.enter()
end

function Minimal.exit()
end

function Minimal.pause()
end

function Minimal.resume()
end

--
-- tse script required function.  Return one or more state names.
-- The first state will be the initial state.
--
function getStates()
    return {'Minimal'}
end

