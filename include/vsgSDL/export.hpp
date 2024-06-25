#if defined(vsgSDL_EXPORT)
#define vsgSDL_LIB __declspec(dllexport)
#elif defined(vsgSDL_IMPORT)
#define vsgSDL_LIB __declspec(dllimport)
#else
#define vsgSDL_LIB
#endif

namespace vsgSDL {
}
