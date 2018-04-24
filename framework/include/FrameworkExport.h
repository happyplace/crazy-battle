#pragma once

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #ifdef __GNUC__
            #define FRAMEWORKDLL __attribute__ ((dllexport))
        #else
            #define FRAMEWORKDLL __declspec(dllexport)
        #endif // __GNUC__
    #else
        #ifdef __GNUC__
            #define FRAMEWORKDLL __attribute__ ((dllimport))
        #else
            #define FRAMEWORKDLL __declspec(dllimport)
        #endif // __GNUC__
    #endif // BUILDING_DLL
#else
    #define FRAMEWORKDLL
#endif // _WIN32
