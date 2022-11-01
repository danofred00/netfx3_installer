
#include <directory.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_DRIVES_COUNT 26


char **get_drives(void) {
    
    char **avaliables_drives = (char **) malloc(MAX_DRIVES_COUNT*4*sizeof(char));
    char current_drive[4];
    int i=0;

    // zero the space allocated
    memset(avaliables_drives, 0, MAX_DRIVES_COUNT*4);

    for (char c = 'A'; c <= 'Z'; c++)
    {
        // format string in the current_drive var
        sprintf(current_drive, "%c:\\", c);
        // trying to open the current_dir

        // if opendir return NULL, it means that the current dir
        // doesn't exists
        if(is_directory(current_drive) == DIR_OK){
            strcpy(avaliables_drives[i], current_drive);
            i++;
        }

    }

    if(i == 0) {
        // free unused space
        free(avaliables_drives);
        return NULL;
    }
    
    return avaliables_drives;

}


static int is_directory(char dirname[4]) {
    
    // no thins here for the moment
    DIR *dir = opendir(dirname);
    if(dir){
        // if sucessfully opened, we close it 
        closedir(dir);
        return DIR_OK;
    }

    return DIR_FAILED;
}