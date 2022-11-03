
#if !defined(__DIRECTORY__)

    #define __DIRECTORY__

    #define MAX_DRIVES_COUNT 26

    // some enum used by is_directory function
    typedef enum _DIR_RESULT {
        DIR_OK,     // if file is an directory
        DIR_FAILED  // fi file is not a dir or file not exists
    } _DIR_RESULT;

    /**
     * @brief This function list all avaliables drives path for the current OS (Windows)
     * @return NULL if we have no avaliable drives
     * and array of drive path (char **) if we have any drive path here
    */
    void get_drives(char **avaliables_drive);

    int save_currents_drives(const char *file_name);

    /**
     * @brief This function if a file is directory or no
     * @return DIR_RESULT enum
    */
    static int is_directory(char dirname[4]);

#endif // __DIRECTORY__
