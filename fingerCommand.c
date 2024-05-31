#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <utmp.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>


char* getDateFromTimestamp (long timestamp) {
    time_t times= timestamp;
    struct tm *local_time = localtime(&timestamp);
    char* time_str = (char*)malloc(sizeof(char) * 100);
    strftime(time_str, 100, "%b %d %Y %H:%M:%S", local_time );
    return time_str;
}

int main (int argc, char *argv[]) {
    

    struct passwd *pw;
    int ch, lflag, mflag, pplan, sflag;
    char* users[10];
    int optionsProvided = 0;
    int numberOfOperands = argc - 1;
    int nextArg = 1;

	while ((ch = getopt(argc, argv, "lmps")) != EOF) {
        optionsProvided = 1;
        nextArg = 2;
        numberOfOperands -= 1;
        switch(ch) {
		  case 'l':
			lflag = 1;		/* long format */
			break;
		  case 'm':
			mflag = 1;		/* do exact match of names */
			break;
		  case 'p':
			pplan = 1;		/* don't show .plan/.project */
			break;
		  case 's':
			sflag = 1;		/* short format */
			break;
		  default:
			printf("usage: finger [-lmps] [login ...]\n");
			return 0;
		}
	}
    
    if (argc == 1) {
        sflag = 1;
        numberOfOperands = 0;
    }
    if (argc != 1 && optionsProvided == 0) {
        lflag = 1;
    }

    /**
     * If the user provided operands ( usernames)
     * we check if they all exist and return a warning
     * for each non-existing user
    */
    if (numberOfOperands != 0) {
        for (int i=nextArg; i < nextArg + numberOfOperands; i++) {
            if ( ( pw = getpwnam( argv[i] ) ) == NULL ) {
                printf("finger: %s: no such user.\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }

    struct utmp *ut;
    setutent(); // Rewind the utmp file
    if ( (ut = getutent()) == NULL ) {
        printf("No one logged on.\n");
    }


    while ((ut = getutent()) != NULL) {
        if (ut->ut_type == USER_PROCESS) {
            printf("Login: %s\t\t\tName: %s\n", pw->pw_name, pw->pw_gecos);
            printf("Directory: %s\t\t\tShell: %s\n", pw->pw_dir, pw->pw_shell);
            printf("User %s logged in at: %s\n", ut->ut_user, getDateFromTimestamp(ut->ut_tv.tv_sec) );
            break;
        }
    }

}

