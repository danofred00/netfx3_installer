
#if !defined(__DIRECTORY__)

    #define __DIRECTORY__

    // some enum used by is_directory function
    typedef enum {
        DIR_OK,     // if file is an directory
        DIR_FAILED  // fi file is not a dir or file not exists
    };

    /*
     * This function list all avaliables drives path for the current OS (Windows)
     *
     * @return NULL if we have no avaliable drives
     * and array of drive path (char **) if we have any drive path here
    */
    char **get_drives(void);

    /**
     * This function if a file is directory or no
     * @return DIR_OK if file is dir
    */
    static int is_directory(char dirname[4]);

#endif // __DIRECTORY__
