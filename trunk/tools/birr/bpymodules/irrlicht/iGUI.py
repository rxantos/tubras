import Blender
from Blender import Draw, BGL

mystring = ""
mymsg = ""
toggle = 0
scriptsLocation = Blender.Get('scriptsdir')+Blender.sys.sep+'bpymodules'+Blender.sys.sep+'irrlicht'+Blender.sys.sep

#-----------------------------------------------------------------------------
#                                   g u i 
#-----------------------------------------------------------------------------
def gui():
    global mystring, mymsg, toggle, scriptsLocation


    BGL.glClearColor(0.6,0.6,0.6,1) 
    BGL.glClear(Blender.BGL.GL_COLOR_BUFFER_BIT)
    size = Blender.Window.GetAreaSize()
    try:
        bheight=10
        boffset = 8
        logoImage = Blender.Image.Load(scriptsLocation + 'irrblend.png')
        isize = logoImage.getSize()
        BGL.glColor3f(0.8,0.8,0.8) 

        BGL.glRectd(11+isize[0],size[1]-bheight-boffset,size[0]-5,size[1]-boffset)

        Blender.BGL.glEnable(Blender.BGL.GL_BLEND ) # Only needed for alpha blending images with background.
        Blender.BGL.glBlendFunc(Blender.BGL.GL_SRC_ALPHA, Blender.BGL.GL_ONE_MINUS_SRC_ALPHA)	  
        Blender.Draw.Image(logoImage, 6, size[1]-isize[1]-5)
        Blender.BGL.glDisable(Blender.BGL.GL_BLEND)

    except IOError: 
        Blender.BGL.glColor3i(255,255,2)
        Blender.BGL.glRasterPos2i(45, size[1]-30)
        Blender.Draw.Text("Irrlicht Plugin for Blender", "large") 

    if len(mystring) > 90: mystring = ""
    BGL.glColor3f(0,0,0)
    Draw.Toggle("Toggle", 1, 10, 10, 55, 20, toggle,"A toggle button")
    BGL.glRasterPos2i(72, 16)
    if toggle: toggle_state = "down"
    else: toggle_state = "up"
    Draw.Text("The toggle button is %s." % toggle_state, "small")
    BGL.glRasterPos2i(10, 230)
    Draw.Text("Type letters from a to z, ESC to leave.")
    BGL.glRasterPos2i(20, 200)
    Draw.Text(mystring)
    BGL.glRasterPos2i(340, 70)
    Draw.Text(mymsg, "tiny")
    
#-----------------------------------------------------------------------------
#                                  e v e n t
#-----------------------------------------------------------------------------
def event(evt, val):
    global mystring, mymsg

    if not val:  # val = 0: it's a key/mbutton release
        if evt in [Draw.LEFTMOUSE, Draw.MIDDLEMOUSE, Draw.RIGHTMOUSE]:
            mymsg = "You released a mouse button."
            Draw.Redraw(1)
        return

    if evt == Draw.ESCKEY:
        Draw.Exit()                 # exit when user presses ESC
        return

    elif Draw.AKEY <= evt <= Draw.ZKEY: mystring += chr(evt)
    elif evt == Draw.SPACEKEY: mystring += ' '
    elif evt == Draw.BACKSPACEKEY and len(mystring):
        mystring = mystring[:-1]
    else: return # no need to redraw if nothing changed

    Draw.Redraw(1)
    
#-----------------------------------------------------------------------------
#                             b u t t o n E v e n t
#-----------------------------------------------------------------------------
def buttonEvent(evt):
    global mymsg, toggle
    if evt == 1:
        mymsg = "You pressed the toggle button."
        toggle = 1 - toggle
        Draw.Redraw(1)
    
