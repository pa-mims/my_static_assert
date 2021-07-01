#ifndef MY_STATIC_ASSERT

// Check if we can use built-in _Static_assert
#if defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 201112L
    #define MY_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)

#else // We make our own
    // MY_JOIN macro tricks the preprocessor into generating a unique token
    #define MY_JOIN2(pre, post) MY_JOIN3(pre, post)
    #define MY_JOIN3(pre, post) pre ## post

    #if defined( __COUNTER__ ) // try to do it the smart way...
        #define MY_JOIN(pre) MY_JOIN2(pre, __COUNTER__)
        #define MY_STATIC_ASSERT(cond, msg) \
        static const char *MY_JOIN(static_assert)[(cond) * 2 - 1] = { msg }

    #else // we did our best...
    //will break if static assert is on same line in different files
        #define MY_JOIN(pre) MY_JOIN2(pre, __LINE__)
        #define MY_STATIC_ASSERT(cond, msg) \
        static const char *MY_JOIN(static_assert)[(cond) * 2 - 1] = { msg }
    #endif
#endif

#endif // MY_STATIC_ASSERT
