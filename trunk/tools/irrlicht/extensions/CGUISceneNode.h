//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef __C_GUI_SCENE_NODE_H_INCLUDED__
#define __C_GUI_SCENE_NODE_H_INCLUDED__

#include "ISceneNode.h"
#include "IMeshSceneNode.h"
#include "IGUIElement.h"
#include "IGUIImage.h"
#include "IGUIEnvironment.h"
#include "IGUIFont.h"
#include "IGUIFontBitmap.h"
#include "IEventReceiver.h"
#include "ITexture.h"
#include "ISceneCollisionManager.h"
#include "S3DVertex.h"
#include "os.h"
#include "IGUISkin.h"
#include "CGUIButton.h"
#include "CGUIModalScreen.h"
#include "CGUIWindow.h"
#include "CGUIMessageBox.h"
#include "CGUIScrollBar.h"
#include "CGUITable.h"
#include "CGUIImage.h"
#include "CGUICheckBox.h"
#include "CGUIListBox.h"
#include "CGUITreeView.h"
#include "CGUIMeshViewer.h"
#include "CGUIFileOpenDialog.h"
#include "CGUIColorSelectDialog.h"
#include "CGUIStaticText.h"
#include "CGUIEditBox.h"
#include "CGUISpinBox.h"
#include "CGUIInOutFader.h"
#include "CGUITabControl.h"
#include "CGUIContextMenu.h"
#include "CGUIMenu.h"
#include "CGUIToolBar.h"
#include "CGUIComboBox.h"

namespace irr
{
    namespace scene
    {
        enum GSN_ACTIVATION_MODE
        {
            GSNAM_3D,        // 3d camera position and target.
            GSNAM_2D         // User supplied 2d screen coordinates.
        };

        enum EGUI_NODE_EVENT_TYPE
        {
            EGNET_ACTIVATED = 0x00010000,
            EGNET_MAX = 0xFFFF0000
        };

        class CGUISceneNode : public scene::ISceneNode, protected gui::IGUIEnvironment, protected gui::IGUIElement
        {
        public:

            //! constructor -plane construction and rendering (normal +z)
            CGUISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
                const core::stringc& cursorImageFileName,
                GSN_ACTIVATION_MODE activationMode=GSNAM_3D,
                IEventReceiver* eventReceiver=0,
                f32 activationDistance=5.f,
                const video::SColor& backgroundColor = video::SColor(255,128,128,128),
                const core::dimension2du& textureSize = core::dimension2du(256, 256),
                const core::vector2df& size = core::vector2df(1, 1),
                const core::vector3df& position = core::vector3df(0,0,0),
                const core::vector3df& rotation = core::vector3df(0,0,0),
                const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));
            
            //! constructor - plane points. (texture rendering only).
            CGUISceneNode(IMeshSceneNode* parent, ISceneManager* mgr, s32 id,
                const core::stringc& cursorImageFileName,
                const core::stringc& textureName,
                IEventReceiver* eventReceiver=0,
                f32 activationDistance=5.f,
                const video::SColor& backgroundColor = video::SColor(255,128,128,128),
                const core::dimension2du& textureSize = core::dimension2du(256, 256));


            //! destructor
            virtual ~CGUISceneNode();

            //! application must feed events...
            virtual bool postEventFromUser(const SEvent& event);

            virtual bool OnEvent(const SEvent& event);

            virtual void OnRegisterSceneNode();

            //! renders the node.
            virtual void render();

            //! forces a GUI texture update regardless of the activation state.
            virtual void updateGUITexture() {Draw = true;}

            virtual void update2DCursorPos(const core::position2di& value) {CursorPos2D = value;}

            //! returns the axis aligned bounding box of this node
            virtual const core::aabbox3d<f32>& getBoundingBox() const;

            //! Returns type of the scene node
            virtual ESCENE_NODE_TYPE getType() const { return ESNT_TEXT; }

            virtual video::SMaterial& getMaterial(u32 num)
            {
                return Material;
            }

            //! Get amount of materials used by this scene node.
            /** \return Current amount of materials of this scene node. */
            virtual u32 getMaterialCount() const
            {
                return 1;
            }

            void setEnabled(bool value)
            {
                IGUIElement::setEnabled(value);
            }

            virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
            virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

            void updateHoveredElement(core::position2d<s32> mousePos);
            bool setFocus(gui::IGUIElement* element);
            gui::IGUIElement* getNextElement(bool reverse, bool group);

            //
            // CGUIEnvironment shims
            //
            //! Draws all gui elements by traversing the GUI environment starting at the root node.
            virtual void drawAll() {
                draw();
                OnPostRender ( os::Timer::getTime () );
            }

            //! Returns the element which holds the focus.
            /** \return Pointer to the element with focus. */
            virtual IGUIElement* getFocus() const {
                return Focus;
            }

            //! Removes the focus from an element.
            /** Causes a EGET_ELEMENT_FOCUS_LOST event. If the event is absorbed
            then the focus will not be changed.
            \param element Pointer to the element which shall lose the focus.
            \return True on success, false on failure */
            virtual bool removeFocus(IGUIElement* element) {
                if (Focus && Focus==element)
                {
                    SEvent e;
                    e.EventType = EET_GUI_EVENT;
                    e.GUIEvent.Caller = Focus;
                    e.GUIEvent.Element = 0;
                    e.GUIEvent.EventType = gui::EGET_ELEMENT_FOCUS_LOST;
                    if (Focus->OnEvent(e))
                    {
                        _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                        return false;
                    }
                }
                if (Focus)
                {
                    Focus->drop();
                    Focus = 0;
                }

                return true;
            }

            //! Returns whether the element has focus
            /** \param element Pointer to the element which is tested.
            \return True if the element has focus, else false. */
            virtual bool hasFocus(IGUIElement* element) const {
                _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
                return (element == Focus);
            }

            //! Returns the current video driver.
            /** \return Pointer to the video driver. */
            virtual video::IVideoDriver* getVideoDriver() const {
                return Environment->getVideoDriver();
            }

            //! Returns the file system.
            /** \return Pointer to the file system. */
            virtual io::IFileSystem* getFileSystem() const {
                return Environment->getFileSystem();
            }

            //! returns a pointer to the OS operator
            /** \return Pointer to the OS operator. */
            virtual IOSOperator* getOSOperator() const {
                return Environment->getOSOperator();
            }

            //! Removes all elements from the environment.
            virtual void clear() {
                Environment->clear();
            }

            //! This sets a new event receiver for gui events.
            /** Usually you do not have to
            use this method, it is used by the engine internally.
            \param evr Pointer to the new receiver. */
            virtual void setUserEventReceiver(IEventReceiver* evr) {}

            //! Returns pointer to the current gui skin.
            /** \return Pointer to the GUI skin. */
            virtual gui::IGUISkin* getSkin() const {
                return Environment->getSkin();
            }

            //! Sets a new GUI Skin
            /** You can use this to change the appearance of the whole GUI
            Environment. You can set one of the built-in skins or implement your
            own class derived from IGUISkin and enable it using this method.
            To set for example the built-in Windows classic skin, use the following
            code:
            \code
            gui::IGUISkin* newskin = environment->createSkin(gui::EGST_WINDOWS_CLASSIC);
            environment->setSkin(newskin);
            newskin->drop();
            \endcode
            \param skin New skin to use.
            */
            virtual void setSkin(gui::IGUISkin* skin) {
                Environment->setSkin(skin);
            }

            //! Creates a new GUI Skin based on a template.
            /** Use setSkin() to set the created skin.
            \param type The type of the new skin.
            \return Pointer to the created skin.
            If you no longer need it, you should call IGUISkin::drop().
            See IReferenceCounted::drop() for more information. */
            virtual gui::IGUISkin* createSkin(gui::EGUI_SKIN_TYPE type) {
                return Environment->createSkin(type);
            }


            //! Creates the image list from the given texture.
            /** Loads the font if it was not loaded before.
            \param filename Filename of the Font.
            \return Pointer to the font. Returns 0 if the font could not be loaded.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIImageList* createImageList( video::ITexture* texture, 
                core::dimension2d<s32>	imageSize, bool useAlphaChannel ) {
                    return Environment->createImageList(texture,imageSize,useAlphaChannel);
            }


            //! Returns pointer to the font with the specified filename.
            /** Loads the font if it was not loaded before.
            \param filename Filename of the Font.
            \return Pointer to the font. Returns 0 if the font could not be loaded.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIFont* getFont(const io::path& filename) {
                return Environment->getFont(filename);
            }

	        //! add an externally loaded font
            virtual gui::IGUIFont* addFont(const io::path& name, gui::IGUIFont* font) {
                return Environment->addFont(name, font);
            }

	        //! remove loaded font
            virtual void removeFont(gui::IGUIFont* font) {
                return Environment->removeFont(font);
            }

            //! Returns the default built-in font.
            /** \return Pointer to the default built-in font.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIFont* getBuiltInFont() const {
                return Environment->getBuiltInFont();
            }

            //! Returns pointer to the sprite bank with the specified file name.
            /** Loads the bank if it was not loaded before.
            \param filename Filename of the sprite bank's origin.
            \return Pointer to the sprite bank. Returns 0 if it could not be loaded.
            This pointer should not be dropped. See IReferenceCounted::drop() for more information. */
            virtual gui::IGUISpriteBank* getSpriteBank(const io::path& filename) {
                return Environment->getSpriteBank(filename);
            }

            //! Adds an empty sprite bank to the manager
            /** \param name Name of the new sprite bank.
            \return Pointer to the sprite bank.
            This pointer should not be dropped. See IReferenceCounted::drop() for more information. */
            virtual gui::IGUISpriteBank* addEmptySpriteBank(const io::path& name) {
                return Environment->addEmptySpriteBank(name);
            }

            //! Returns the root gui element.
            /** This is the first gui element, the (direct or indirect) parent of all 
            other gui elements.  It is a valid IGUIElement, with dimensions the same 
            size as the screen.	You should not need to use this method directly, unless 
            you wish to reparent GUI elements to the top level.
            \return Pointer to the root element of the GUI. The returned pointer
            should not be dropped. See IReferenceCounted::drop() for more
            information. */
            virtual gui::IGUIElement* getRootGUIElement() {return this;}

            //! Adds a button element.
            /** \param rectangle Position and dimension of the button.
            \param parent Parent gui element of the button.
            \param id Id with which the gui element can be identified.
            \param text Text displayed on the button.
            \param tooltiptext Text displayed in the tooltip.
            \return Pointer to the created button. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIButton* addButton(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0, const wchar_t* tooltiptext = 0) 
            {
                gui::IGUIButton* button = new gui::CGUIButton(this, parent ? parent : this, id, rectangle);
                if (text)
                    button->setText(text);

                if ( tooltiptext )
                    button->setToolTipText ( tooltiptext );

                button->drop();
                return button;
            }


            //! Adds an empty window element.
            /** \param rectangle Position and dimension of the window.
            \param modal Defines if the dialog is modal. This means, that all other
            gui elements which were created before the window cannot be used until
            it is removed.
            \param text Text displayed as the window title.
            \param parent Parent gui element of the window.
            \param id Id with which the gui element can be identified.
            \return Pointer to the created window. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIWindow* addWindow(const core::rect<s32>& rectangle, bool modal = false,
                const wchar_t* text=0, gui::IGUIElement* parent=0, s32 id=-1) {
                    parent = parent ? parent : this;

                    if (modal)
                    {
                        parent = new gui::CGUIModalScreen(this, parent, -1);
                        parent->drop();
                    }

                    gui::IGUIWindow* win = new gui::CGUIWindow(this, parent, id, rectangle);
                    if (text)
                        win->setText(text);
                    win->drop();

                    return win;
            }

            //! Adds a modal screen.
            /** This control stops its parent's members from being able to receive
            input until its last child is removed, it then deletes itself.
            \param parent Parent gui element of the modal.
            \return Pointer to the created modal. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIElement* addModalScreen(gui::IGUIElement* parent) {
                parent = parent ? parent : this;

                gui::IGUIElement *win = new gui::CGUIModalScreen(this, parent, -1);
                win->drop();

                return win;
            }

            //! Adds a message box.
            /** \param caption Text to be displayed the title of the message box.
            \param text Text to be displayed in the body of the message box.
            \param modal Defines if the dialog is modal. This means, that all other
            gui elements which were created before the message box cannot be used
            until this messagebox is removed.
            \param flags Flags specifying the layout of the message box. For example
            to create a message box with an OK and a CANCEL button on it, set this
            to (EMBF_OK | EMBF_CANCEL).
            \param parent Parent gui element of the message box.
            \param id Id with which the gui element can be identified.
            \return Pointer to the created message box. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIWindow* addMessageBox(const wchar_t* caption, const wchar_t* text=0,
                bool modal = true, s32 flags = gui::EMBF_OK, gui::IGUIElement* parent=0, s32 id=-1) {
                    if (!Environment->getSkin())
                        return 0;

                    parent = parent ? parent : this;

                    core::rect<s32> rect;
                    core::dimension2d<u32> screenDim, msgBoxDim;

                    screenDim.Width = parent->getAbsolutePosition().getWidth();
                    screenDim.Height = parent->getAbsolutePosition().getHeight();
                    msgBoxDim.Width = Environment->getSkin()->getSize(gui::EGDS_MESSAGE_BOX_WIDTH);
                    msgBoxDim.Height = Environment->getSkin()->getSize(gui::EGDS_MESSAGE_BOX_HEIGHT);

                    rect.UpperLeftCorner.X = (screenDim.Width - msgBoxDim.Width) / 2;
                    rect.UpperLeftCorner.Y = (screenDim.Height - msgBoxDim.Height) / 2;
                    rect.LowerRightCorner.X = rect.UpperLeftCorner.X + msgBoxDim.Width;
                    rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + msgBoxDim.Height;

                    if (modal)
                    {
                        parent = new gui::CGUIModalScreen(this, parent, -1);
                        parent->drop();
                    }

                    gui::IGUIWindow* win = new gui::CGUIMessageBox(this, caption, text, flags,
                        parent, id, rect);

                    win->drop();
                    return win;

            }

	        //! Adds a message box.
            virtual gui::IGUIWindow* addMessageBox(const wchar_t* caption, const wchar_t* text=0,
                bool modal = true, s32 flag = gui::EMBF_OK, gui::IGUIElement* parent=0, s32 id=-1, video::ITexture* image=0);

            //! Adds a scrollbar.
            /** \param horizontal Specifies if the scroll bar is drawn horizontal
            or vertical.
            \param rectangle Position and dimension of the scroll bar.
            \param parent Parent gui element of the scroll bar.
            \param id Id to identify the gui element.
            \return Pointer to the created scrollbar. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIScrollBar* addScrollBar(bool horizontal, const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1) {
                    gui::IGUIScrollBar* bar = new gui::CGUIScrollBar(horizontal, this, parent ? parent : this, id, rectangle);
                    bar->drop();
                    return bar;
            }

            //! Adds an image element.
            /** \param image Image to be displayed.
            \param pos Position of the image. The width and height of the image is
            taken from the image.
            \param useAlphaChannel Sets if the image should use the alpha channel
            of the texture to draw itself.
            \param parent Parent gui element of the image.
            \param id Id to identify the gui element.
            \param text Title text of the image.
            \return Pointer to the created image element. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIImage* addImage(video::ITexture* image, core::position2d<s32> pos,
                bool useAlphaChannel=true, gui::IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0) {
                    core::dimension2d<s32> sz(0,0);
                    if (image)
                        sz = core::dimension2d<s32>(image->getOriginalSize());

                    gui::IGUIImage* img = new gui::CGUIImage(this, parent ? parent : this,
                        id, core::rect<s32>(pos, sz));

                    if (text)
                        img->setText(text);

                    if (useAlphaChannel)
                        img->setUseAlphaChannel(true);

                    if (image)
                        img->setImage(image);

                    img->drop();
                    return img;
            }

            //! Adds an image element.
            /** Use IGUIImage::setImage later to set the image to be displayed.
            \param rectangle Position and dimension of the image.
            \param parent Parent gui element of the image.
            \param id Id to identify the gui element.
            \param text Title text of the image.
            \return Pointer to the created image element. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIImage* addImage(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0) {
                    gui::IGUIImage* img = new gui::CGUIImage(this, parent ? parent : this,
                        id, rectangle);

                    if (text)
                        img->setText(text);

                    img->drop();
                    return img;

            }

            //! Adds a checkbox element.
            /** \param checked Define the initial state of the check box.
            \param rectangle Position and dimension of check box.
            \param parent Parent gui element of the check box.
            \param id Id to identify the gui element.
            \param text Title text of the check box.
            \return Pointer to the created check box. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUICheckBox* addCheckBox(bool checked, const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0) {
                    gui::IGUICheckBox* b = new gui::CGUICheckBox(checked, this,
                        parent ? parent : this , id , rectangle);

                    if (text)
                        b->setText(text);

                    b->drop();
                    return b;
            }

            //! Adds a list box element.
            /** \param rectangle Position and dimension of list box.
            \param parent Parent gui element of the list box.
            \param id Id to identify the gui element.
            \param drawBackground Flag whether the background should be drawn.
            \return Pointer to the created list box. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIListBox* addListBox(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, bool drawBackground=false) {
                    gui::IGUIListBox* b = new gui::CGUIListBox(this, parent ? parent : this, id, rectangle,
                        true, drawBackground, false);

                    if (Environment->getSkin() && Environment->getSkin()->getSpriteBank())
                    {
                        b->setSpriteBank(Environment->getSkin()->getSpriteBank());
                    }
                    else if (getBuiltInFont() && getBuiltInFont()->getType() == gui::EGFT_BITMAP)
                    {
                        b->setSpriteBank( ((gui::IGUIFontBitmap*)getBuiltInFont())->getSpriteBank());
                    }
                    b->drop();
                    return b;
            }

            //! Adds a tree view element.
            /** \param rectangle Position and dimension of list box.
            \param parent Parent gui element of the list box.
            \param id Id to identify the gui element.
            \param drawBackground Flag whether the background should be drawn.
            \return Pointer to the created list box. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUITreeView* addTreeView(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, bool drawBackground=false,
                bool scrollBarVertical = true, bool scrollBarHorizontal = false) {
                    gui::IGUITreeView* b = new gui::CGUITreeView(this, parent ? parent : this, id, rectangle,
                        true, drawBackground, scrollBarVertical, scrollBarHorizontal);

                    b->setIconFont ( getBuiltInFont () );
                    b->drop();
                    return b;
            }

            //! Adds a mesh viewer. Not 100% implemented yet.
            /** \param rectangle Position and dimension of mesh viewer.
            \param parent Parent gui element of the mesh viewer.
            \param id Id to identify the gui element.
            \param text Title text of the mesh viewer.
            \return Pointer to the created mesh viewer. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIMeshViewer* addMeshViewer(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0) {
                    gui::IGUIMeshViewer* v = new gui::CGUIMeshViewer(this, parent ? parent : this,
                        id, rectangle);

                    if (text)
                        v->setText(text);

                    v->drop();
                    return v;
            }

            //! Adds a file open dialog.
            /** \param title Text to be displayed as the title of the dialog.
            \param modal Defines if the dialog is modal. This means, that all other
            gui elements which were created before the message box cannot be used
            until this messagebox is removed.
            \param parent Parent gui element of the dialog.
            \param id Id to identify the gui element.
            \return Pointer to the created file open dialog. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIFileOpenDialog* addFileOpenDialog(const wchar_t* title = 0,
                bool modal=true, gui::IGUIElement* parent=0, s32 id=-1) {
                    parent = parent ? parent : this;

                    if (modal)
                    {
                        parent = new gui::CGUIModalScreen(this, parent, -1);
                        parent->drop();
                    }

                    gui::IGUIFileOpenDialog* d = new gui::CGUIFileOpenDialog(title, this, parent, id);

                    d->drop();
                    return d;

            }

            //! Adds a color select dialog.
            /** \param title The title of the dialog.
            \param modal Defines if the dialog is modal. This means, that all other
            gui elements which were created before the dialog cannot be used
            until it is removed.
            \param parent The parent of the dialog.
            \param id The ID of the dialog.
            \return Pointer to the created file open dialog. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIColorSelectDialog* addColorSelectDialog(const wchar_t* title = 0,
                bool modal=true, gui::IGUIElement* parent=0, s32 id=-1) {
                    parent = parent ? parent : this;

                    if (modal)
                    {
                        parent = new gui::CGUIModalScreen(this, parent, -1);
                        parent->drop();
                    }

                    gui::IGUIColorSelectDialog* d = new gui::CGUIColorSelectDialog( title,
                        this, parent, id);

                    d->drop();
                    return d;
            }

            //! Adds a static text.
            /** \param text Text to be displayed. Can be altered after creation by SetText().
            \param rectangle Position and dimension of the static text.
            \param border Set to true if the static text should have a 3d border.
            \param wordWrap Enable if the text should wrap into multiple lines.
            \param parent Parent item of the element, e.g. a window.
            \param id The ID of the element.
            \param fillBackground Enable if the background shall be filled.
            Defaults to false.
            \return Pointer to the created static text. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIStaticText* addStaticText(const wchar_t* text, const core::rect<s32>& rectangle,
                bool border=false, bool wordWrap=true, gui::IGUIElement* parent=0, s32 id=-1,
                bool fillBackground = false) {
                    gui::IGUIStaticText* d = new gui::CGUIStaticText(text, border, this,
                        parent ? parent : this, id, rectangle, fillBackground);

                    d->setWordWrap(wordWrap);
                    d->drop();

                    return d;
            }

            //! Adds an edit box.
            /** Supports unicode input from every keyboard around the world,
            scrolling, copying and pasting (exchanging data with the clipboard
            directly), maximum character amount, marking, and all shortcuts like
            ctrl+X, ctrl+V, ctrl+C, shift+Left, shift+Right, Home, End, and so on.
            \param text Text to be displayed. Can be altered after creation
            by setText().
            \param rectangle Position and dimension of the edit box.
            \param border Set to true if the edit box should have a 3d border.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the edit box directly in the environment.
            \param id The ID of the element.
            \return Pointer to the created edit box. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIEditBox* addEditBox(const wchar_t* text, const core::rect<s32>& rectangle,
                bool border=true, gui::IGUIElement* parent=0, s32 id=-1) {
                    gui::IGUIEditBox* d = new gui::CGUIEditBox(text, border, this,
                        parent ? parent : this, id, rectangle);

                    d->drop();
                    return d;
            }

            //! Adds a spin box.
            /** An edit box with up and down buttons
            \param text Text to be displayed. Can be altered after creation by setText().
            \param rectangle Position and dimension of the spin box.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the spin box directly in the environment.
            \param id The ID of the element.
            \return Pointer to the created spin box. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUISpinBox* addSpinBox(const wchar_t* text, const core::rect<s32>& rectangle,
                bool border=true,gui::IGUIElement* parent=0, s32 id=-1) {
                    gui::IGUISpinBox* d = new gui::CGUISpinBox(text, border,this,
                        parent ? parent : this, id, rectangle);

                    d->drop();
                    return d;
            }

            //! Adds an element for fading in or out.
            /* \param rectangle Rectangle specifying the borders of the element.
            If the pointer is NULL, the whole screen is used.
            \param parent Parent item of the element, e.g. a window.
            \param id An identifier for the fader.
            \return Pointer to the created in-out-fader. Returns 0 if an error
            occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIInOutFader* addInOutFader(const core::rect<s32>* rectangle=0, gui::IGUIElement* parent=0, s32 id=-1) {
                core::rect<s32> rect;

                if (rectangle)
                    rect = *rectangle;
                else 
                    rect = core::rect<s32>(core::position2d<s32>(0,0), RenderTarget->getSize());

                if (!parent)
                    parent = this;

                gui::IGUIInOutFader* fader = new gui::CGUIInOutFader(this, parent, id, rect);
                fader->drop();
                return fader;
            }

            //! Adds a tab control to the environment.
            /** \param rectangle Position and dimension of the tab control.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the tab control directly in the environment.
            \param fillbackground Specifies if the background of the tab control
            should be drawn.
            \param border Specifies if a flat 3d border should be drawn. This is
            usually not necessary unless you place the control directly into
            the environment without a window as parent.
            \param id An identifier for the tab control.
            \return Pointer to the created tab control element. Returns 0 if an
            error occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUITabControl* addTabControl(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, bool fillbackground=false,
                bool border=true, s32 id=-1) {
                    gui::IGUITabControl* t = new gui::CGUITabControl(this, parent ? parent : this,
                        rectangle, fillbackground, border, id);
                    t->drop();
                    return t;
            }

            //! Adds tab to the environment.
            /** You can use this element to group other elements. This is not used
            for creating tabs on tab controls, please use IGUITabControl::addTab()
            for this instead.
            \param rectangle Position and dimension of the tab.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the tab directly in the environment.
            \param id An identifier for the tab.
            \return Pointer to the created tab. Returns 0 if an
            error occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUITab* addTab(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1) {
                    gui::IGUITab* t = new gui::CGUITab(-1, this, parent ? parent : this,
                        rectangle, id);
                    t->drop();
                    return t;
            }

            //! Adds a context menu to the environment.
            /** \param rectangle Position and dimension of the menu. Note that the
            menu is resizing itself based on what items you add.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the menu directly in the environment.
            \param id An identifier for the menu.
            \return Pointer to the created context menu. Returns 0 if an
            error occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIContextMenu* addContextMenu(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1) {
                    gui::IGUIContextMenu* c = new gui::CGUIContextMenu(this,
                        parent ? parent : this, id, rectangle, true);
                    c->drop();
                    return c;
            }

            //! Adds a menu to the environment.
            /** This is like the menu you can find on top of most windows in modern
            graphical user interfaces.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the menu directly in the environment.
            \param id An identifier for the menu.
            \return Pointer to the created menu. Returns 0 if an
            error occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIContextMenu* addMenu(gui::IGUIElement* parent=0, s32 id=-1) {
                if (!parent)
                    parent = this;

                gui::IGUIContextMenu* c = new gui::CGUIMenu(this,
                    parent, id, core::rect<s32>(0,0,
                    parent->getAbsolutePosition().getWidth(),
                    parent->getAbsolutePosition().getHeight()));

                c->drop();
                return c;
            }

            //! Adds a toolbar to the environment.
            /** It is like a menu that is always placed on top of its parent, and
            contains buttons.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the tool bar directly in the environment.
            \param id An identifier for the tool bar.
            \return Pointer to the created tool bar. Returns 0 if an
            error occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIToolBar* addToolBar(gui::IGUIElement* parent=0, s32 id=-1) {
                if (!parent)
                    parent = this;

                gui::IGUIToolBar* b = new gui::CGUIToolBar(this, parent, id, core::rect<s32>(0,0,10,10));
                b->drop();
                return b;
            }

            //! Adds a combo box to the environment.
            /** \param rectangle Position and dimension of the combo box.
            \param parent Parent item of the element, e.g. a window.
            Set it to 0 to place the combo box directly in the environment.
            \param id An identifier for the combo box.
            \return Pointer to the created combo box. Returns 0 if an
            error occured. This pointer should not be dropped. See
            IReferenceCounted::drop() for more information. */
            virtual gui::IGUIComboBox* addComboBox(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1) {
                    gui::IGUIComboBox* t = new gui::CGUIComboBox(this, parent ? parent : this,
                        id, rectangle);
                    t->drop();
                    return t;
            }

            //! Adds a table to the environment
            /** \param rectangle Position and dimension of the table.
            \param parent Parent item of the element, e.g. a window. Set it to 0
            to place the element directly in the environment.
            \param id An identifier for the table.
            \param drawBackground Flag whether the background should be drawn.
            \return Pointer to the created table. Returns 0 if an error occured.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUITable* addTable(const core::rect<s32>& rectangle,
                gui::IGUIElement* parent=0, s32 id=-1, bool drawBackground = false) {
                    gui::CGUITable* b = new gui::CGUITable(this, parent ? parent : this, id, rectangle, true, drawBackground, false);
                    b->drop();
                    return b;

            }

            //! Returns the default element factory which can create all built in elements
            /** \return Pointer to the factory.
            This pointer should not be dropped. See IReferenceCounted::drop() for
            more information. */
            virtual gui::IGUIElementFactory* getDefaultGUIElementFactory() const {
                return Environment->getDefaultGUIElementFactory();
            }

            //! Adds an element factory to the gui environment.
            /** Use this to extend the gui environment with new element types which
            it should be able to create automatically, for example when loading
            data from xml files.
            \param factoryToAdd Pointer to new factory. */
            virtual void registerGUIElementFactory(gui::IGUIElementFactory* factoryToAdd) {
                Environment->registerGUIElementFactory(factoryToAdd);
            }

            //! Returns amount of registered gui element factories.
            /** \return Amount of registered gui element factories. */
            virtual u32 getRegisteredGUIElementFactoryCount() const {
                return Environment->getRegisteredGUIElementFactoryCount();
            }

            //! Returns a gui element factory by index
            virtual gui::IGUIElementFactory* getGUIElementFactory(u32 index) const {
                return Environment->getGUIElementFactory(index);
            }

            //! Adds a GUI Element by its name
            virtual gui::IGUIElement* addGUIElement(const c8* elementName, gui::IGUIElement* parent=0) {
                return Environment->addGUIElement(elementName, parent);
            }

            //! Saves the current gui into a file.
            /** \param filename Name of the file.
            \param start The GUIElement to start with. Root if 0. */
            virtual bool saveGUI(const io::path& filename, gui::IGUIElement* start=0) {
                return false;
            }

            //! Saves the current gui into a file.
            /** \param file The file to write to.
            \param start The GUIElement to start with. Root if 0. */
            virtual bool saveGUI(io::IWriteFile* file, gui::IGUIElement* start=0) {
                return false;
            }

            //! Loads the gui. Note that the current gui is not cleared before.
            /** \param filename Name of the file.
            \param parent Parent for the loaded GUI, root if 0. */
            virtual bool loadGUI(const io::path& filename, gui::IGUIElement* parent=0) {
                return false;
            }

            //! Loads the gui. Note that the current gui is not cleared before.
            /** \param file The file to load from.
            \param parent Parent for the loaded GUI, root if 0. */
            virtual bool loadGUI(io::IReadFile* file, gui::IGUIElement* parent=0) {
                return false;
            }

            //! writes an element
            virtual void writeGUIElement(io::IXMLWriter* writer, IGUIElement* node) {
            }

            //! reads an element
            virtual void readGUIElement(io::IXMLReader* reader, gui::IGUIElement* node) {
            }

        public:
            core::vector3df debug;
            //private:
            ISceneManager*  SceneManager;
            ISceneCollisionManager* CollisionManager;
            core::aabbox3d<f32> Box;
            video::ITexture*   RenderTarget;
            video::SMaterial Material;
            video::S3DVertex Vertices[4];
            u16 Indices[6];
            video::SColor   BColor;
            core::plane3df Plane;
            core::triangle3df Triangle,Triangle2;
            gui::IGUIImage* Cursor;
            core::position2di RTTCursorPos;
            core::position2di CursorPos2D;
            bool Activated, Draw, RenderGeometry;
            core::vector3df UpperLeftCorner,UpperRightCorner;
            core::vector2df GeometrySize;
            IEventReceiver* EventReceiver;   
            GSN_ACTIVATION_MODE ActivationMode;

            core::position2d<s32> LastHoveredMousePos;
            f32 ActivationDistance;
            gui::IGUIElement* Hovered;
            gui::IGUIElement* Focus;
            gui::IGUIEnvironment* Environment;
        };

    } // end namespace scene
} // end namespace irr

#endif

