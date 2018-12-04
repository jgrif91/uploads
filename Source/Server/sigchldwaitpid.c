// NOTE: THIS CAME DIRECTLY FROM RICHARD STEVENS, ALL CREDIT GOES TO HIM FOR THIS CODE.
//  If any changes in the code exists, it is to assure that the code works with my changes
//  to the program.




// Included Libraries
// ===============================
#include <sys/types.h>  // Kernal Sig. Types [ng]
#include <sys/wait.h>   // wait() and waitpid() [ng]
#include "myunp.h"      // Our custom UNP Header file
// ===============================




// Child Signal Event
// -----------------------------------
// Documentation:
//  This function will wait for the child process to
//  terminate - thus ending the child process from the
//  system.
// -----------------------------------
// Parameters:
//  signo [int]
//      The signal number of the process at the
//      given time.
// -----------------------------------
void sig_chld(int signo)
{
    // Declarations and Initializations
    // ----------------------------------
    pid_t pid;      // Process ID
    int stat;       // Cache
    // ----------------------------------

    // Scan the processes for possible terminations
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    
    // Leave from function
    return;
} // sig_chld()
