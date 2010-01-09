-----------------------------------------------------------------------------
--                             0 1 - t e s t
-----------------------------------------------------------------------------

-----------------------------------------------------------------------------
--                         h a n d l e E s c a p e
-----------------------------------------------------------------------------
function handleEscape(event)
    print('handleEscape Invoked')
    tse:stopRunning()
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
renderer = tse:getRenderer()

tse:setBGColor(100, 101, 140)

tse:acceptEvent('quit', handleEscape)
tse:acceptEvent('key.down.f3', cycleRenderMode)
tse:addHelpText('     F3 - Cycle Wire')
tse:addHelpText(' Escape - Quit')

cube = tse:loadModel('mdl/Cube.irrmesh')
cube.setPosition(0.0, 0.0, -50.0)
-- or
pos = TVector3.new(0.0, 0.0, -50.0)
cube.setPosition(pos)
-- or
cube.pos = {0.0, 0.0, -50.0}
-- or
cube.pos = pos

return 0
