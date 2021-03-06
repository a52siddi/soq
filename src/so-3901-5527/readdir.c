/* SO 3901-5527 - attempt to demonstrate renaming moving entries */
#include "posixver.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *stop_after = "a";

static void process_directory(const char *dirname)
{
    DIR *dp = opendir(dirname);

    if (dp == 0)
        fprintf(stderr, "Failed to open directory %s\n", dirname);
    else
    {
        struct dirent *entry;
        while ((entry = readdir(dp)) != 0)
        {
            /* Ignore current and parent directory */
#ifdef HAVE_DIRENT_D_NAMLEN
            int name_len = entry->d_namlen;          /* Not available on Cygwin */
#else
            int name_len = strlen(entry->d_name);    /* Works everywhere */
#endif
            printf("%8d: (%3d) %s\n", (int)entry->d_ino, name_len, entry->d_name);
            if (strcmp(entry->d_name, stop_after) == 0)
            {
                printf("Found entry '%s' - hit return to continue: ", stop_after);
                fflush(stdout);
                char *buffer = 0;
                size_t buflen = 0;
                if (getline(&buffer, &buflen, stdin) == -1)
                    exit(1);
                free(buffer);
                printf("Continuing...\n");
            }
        }
        closedir(dp);
    }
}

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1)
    {
        switch (opt)
        {
        case 's':
            stop_after = optarg;
            break;;
        default:
            fprintf(stderr, "%s: Unrecognized option '-%c'\n", argv[0], optopt);
            fprintf(stderr, "Usage: %s [-s stop_after] [directory ...]\n", argv[0]);
            return(EXIT_FAILURE);
        }
    }
    if (optind == argc)
        process_directory(".");
    else
    {
        for (int i = optind; i < argc; i++)
            process_directory(argv[i]);
    }
    return(0);
}

