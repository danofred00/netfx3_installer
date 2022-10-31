
#if !defined(__DIRECTORY__)

    #define __DIRECTORY__

    // some enum used by is_directory function
    typedef enum {
        DIR_OK,     // if file is an directory
        DIR_FAILED  // fi file is not a dir or file not exists
    };

    char **get_drives(void);

    /**
     * This function if a file is directory or no
     * @return DIR_OK if file is dir
    */
    int is_directory(char dirname[3]);

#endif // __DIRECTORY__
