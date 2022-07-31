# vsgSDL
 
 Integrates VulkanSceneGraph with SDL
 https://github.com/vsg-dev/VulkanSceneGraph

## setup step

### On Windows
```
git clone https://github.com/ptrfun/vsgSDL.git
cd vsgSDL
cmake -S . -B build -A x64
```
After running CMake open the generated VSG.sln file and build the All target. Once built you can run the install target.If you used vspkg to manage your package,you can run
```
git clone https://github.com/ptrfun/vsgSDL.git
cd vsgSDL
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/vcpkg.cmake -A x64
```

## pseudo-example

```cpp
vsgSDL::Window window;

window.renderInit = [](const vsg::ref_ptr<vsg::Window> window,const vsg::ref_ptr<vsg::Viewer> viewer,const vsg::ref_ptr<vsg::WindowTraits> traits) 
{ 
    // needs defined first before called in Window::create() //vsg stuff 
}

window.renderDeinit = [](const vsg::ref_ptr vsg::Viewer viewer)
{ 
    // called in Window::~Window() stuff 
}

window.render = [](const vsg::ref_ptr vsg::Viewer viewer)
{ 
    //vsg stuff
}

window.focusGained = [](const vsg::ref_ptr<vsg::Window> window) {}

window.focusLost = [](const vsg::ref_ptr<vsg::Window> window) {}

window.textInput = [](const char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {}

window.create(title, x, y (or SDL_WINDOWPOS), w, h, sdl_window_flags, debug layer on/off, api dump layer on/off, path to dynamic library (e.g. libvulkan-1.so, libvulkan-1.dll) to override sdl default vulkan loader)

while(true)
{
    bool scanforcontinuouskeyinputs; // true、false -> on、off
    if(!window.process(scanforcontinouskeyinputs))
        break;
}
```

## code example

An [example](https://github.com/ptrfun/vsgSDL/tree/main/example/vsgSDLexample)