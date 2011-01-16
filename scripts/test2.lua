app = TubrasApp
print('app: ' .. tostring(app))
app:logMessage('Hello from test.lua')

-- vector3 tests
v = TVector3(1.45, 2.0, 3.0)
print(v)
print(tostring(v,1))

v.x = v.x + 2.5
v.xyz = 123

print('v: ' .. tostring(v))

v:normalize()
print('v (normalized): ' .. tostring(v))

v.x = 33
print('v: ' .. tostring(v))

v1 = TVector3(1.5, 2.5, 3.5)
v2 = TVector3(3.5, 2.5, 1.5)

v3 = v1 + v2
print('v3: ' .. tostring(v3))
v3 = v3 + 1.5
print('v3: ' .. tostring(v3))

v3 = v1 + 'test'
print('v3: ' .. tostring(v3))

v3 = v3 * 2.0
v3.y = -v3.y
print('v3: ' .. tostring(v3))

v4 = -v3
print('v4: ' .. tostring(v4))

v2.x = v1.x
v2.y = v1.y
v2.z = v1.z
print(tostring(v1))
print(tostring(v2))

if v1 == v2 then
    print('v1 == v2')
else
    print('v1 != v2')
end

if v1 == v1 then
    print('v1 == v1')
else
    print('v1 != v1')
end

print('***: ' .. tostring(v1, true))

-- registered enum
print('rmWire: ' .. tostring(rmWire))


-- event handler
function handleEvent(event)
    id = event.id
    app:logMessage('handleEvent() id=' .. tostring(id))
    if id == ID_QUIT then
        app:stopRunning()
    end
    return 1
end

-- handle 'quit' event
ID_QUIT = app:acceptEvent('quit', handleEvent)

return 0
