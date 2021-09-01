#ifndef B2_API_H
#define B2_API_H

#ifdef B2_SHARED
    #if defined _WIN32 || defined __CYGWIN__
        #ifdef box2d_EXPORTS
            #ifdef __GNUC__
                #define B2_API __attribute__ ((dllexport))
            #else
                #define B2_API __declspec(dllexport)
            #endif
        #else
            #ifdef __GNUC__
                #define B2_API __attribute__ ((dllimport))
            #else
                #define B2_API __declspec(dllimport)
            #endif
        #endif
    #else
        #if __GNUC__ >= 4
            #define B2_API __attribute__ ((visibility ("default")))
        #else
            #define B2_API
        #endif
    #endif
#else
    #define B2_API
#endif

#endif