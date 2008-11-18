--[[
The following definitions are identical in that 
CLSL::getStringMap("bindings", scopedID=false) will return:

'key.down.w' : 'frwd'
'key.down.a' : 'left'
'key.down.s' : 'back'
'key.down.d' : 'right'
'key.up.w' : 'frwd up'
'key.up.a' : 'left up'
'key.up.s' : 'back up'
'key.up.d' : 'rght up'

if "scopedID" = true, then the map keys are prefixed with 
"bindings.".

and 

CLSL::getString('bindings.key.down.w') => 'frwd'

--]]

bindings =
{
    key =
    {
        down = 
        {
            w = 'frwd',
            a = 'left',
            s = 'back',
            d = 'rght',
        },

        up = 
        {
            w = 'frwd up',
            a = 'left up',
            s = 'back up',
            d = 'rght up',
        }
    }
}

bindings = {}
bindings['key.down.w'] = 'frwd'
bindings['key.down.a'] = 'left'
bindings['key.down.s'] = 'back'
bindings['key.down.d'] = 'right'
bindings['key.up.w'] = 'frwd up'
bindings['key.up.a'] = 'left up'
bindings['key.up.s'] = 'back up'
bindings['key.up.d'] = 'rght up'

