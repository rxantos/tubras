-- The tubras module is named "tubras" and is automatically added 
-- by tse. Save off a reference to the Application object.
app = tubras.getApplication()
renderer = tapp:getRenderer()

function handleEscape(event)
    print('handleEscape Invoked')
    app:stopRunning()
    return 1
end

function cycleRenderMode(event)
    print('cycleRenderMode Invoked')
    mode = renderer:getRenderMode()
    if mode == rmNormal then
        renderer:setRenderMode(rmWire)
    elseif mode == rmWire then
        renderer:setRenderMode(rmPointCloud)
    else
        renderer:setRenderMode(rmNormal)
    end

app:setBGColor(100, 101, 140)

app:acceptEvent('quit', handleEscape)
app:acceptEvent('key.down.f3', cycleRenderMode)
app:addHelpText('     F3 - Cycle Wire')
app:addHelpText(' Escape - Quit')

cube = app:loadModel('mdl/Cube.irrmesh')
cube.setPosition(0.0, 0.0, -50.0)
-- or
cube.pos = (0.0, 0,0, -50.0)

return 0
