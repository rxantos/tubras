-----------------------------------------------------------------------------
--                             0 1 - t e s t
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
--                         h a n d l e E s c a p e
-----------------------------------------------------------------------------
function handleEscape(event)
    print('handleEscape Invoked')
    app:stopRunning()
    return 1
end

-----------------------------------------------------------------------------
--                         c y c l R e n d e r M o d e
-----------------------------------------------------------------------------
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

-----------------------------------------------------------------------------
--                              m a i n
-----------------------------------------------------------------------------
app = tubras.getApplication()
renderer = app:getRenderer()

app:setBGColor(100, 101, 140)

app:acceptEvent('quit', handleEscape)
app:acceptEvent('key.down.f3', cycleRenderMode)
app:addHelpText('     F3 - Cycle Wire')
app:addHelpText(' Escape - Quit')

cube = app:loadModel('mdl/Cube.irrmesh')
cube.setPosition(0.0, 0.0, -50.0)
-- or
pos = TVector3.new(0.0, 0.0, -50.0)
cube.setPosition(pos)
-- or
cube.pos = {0.0, 0.0, -50.0}
-- or
cube.pos = pos

return 0
