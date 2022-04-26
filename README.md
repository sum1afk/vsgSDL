# vsgSDL
 https://github.com/vsg-dev/VulkanSceneGraph SDL Integration

------------pseudo-example:

vsgSDL::Window window;

window.renderInit = [](const vsg::ref_ptr vsg::Window window, const vsg::ref_ptr vsg::Viewer viewer, const vsg::ref_ptr vsg::WindowTraits traits) { // needs defined first before called in Window::create() //vsg stuff }

window.renderDeinit = [](const vsg::ref_ptr vsg::Viewer viewer) { // called in Window::~Window() //stuff }

window.render = [](const vsg::ref_ptr vsg::Viewer viewer) { //vsg stuff }

window.focusGained = { } window.focusLost = { } window.textInput = [](const char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) { }

window.create(title, x, y (or SDL_WINDOWPOS), w, h, sdl_window_flags, debug layer on/off, api dump layer on/off, path to dynamic library (e.g. libvulkan-1.so, libvulkan-1.dll) to override sdl default vulkan loader)

while(true) { bool scanforcontinuouskeyinputs = true/false on/off if(!window.process(scanforcontinouskeyinputs)) break; }