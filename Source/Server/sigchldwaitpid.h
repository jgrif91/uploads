// NOTE: THIS CAME DIRECTLY FROM RICHARD STEVENS, ALL CREDIT GOES TO HIM FOR THIS CODE.
//  If any changes in the code exists, it is to assure that the code works with my changes
//  to the program.




// Inclusion Guard
// -----------------
#ifndef _SIGCHLDWAITPID_H_
#define _SIGCHLDWAITPID_H_
// -----------------




// Function Prototypes for Main Menu
// -----------------------------------
void sig_chld(int);         // Event Signal from Kernel
                            //  if the child process has
                            //  ended, thus preventing
                            //  zombie processes.
// -----------------------------------




// Concluding Inclusion Guard
#endif