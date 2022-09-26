#ifndef VSGSDL_EXPORT_HPP
#define VSGSDL_EXPORT_HPP

#if defined(vsgSDL_EXPORT)
#define vsgSDL_LIB __declspec(dllexport)
#elif defined(vsgSDL_IMPORT)
#define vsgSDL_LIB __declspec(dllimport)
#else
#define vsgSDL_LIB
#endif

#endif
