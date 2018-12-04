// Update User Account Information
// ================================
// ================================
// This file holds functions that allows the user to update their
//  personal account information.  Thus, their settings are changed
//  in real time during their active session with the service.




// Inclusion Guard
// -----------------
#ifndef _UPDATEUSRACCINFOFUNCS_H_
#define _UPDATEUSRACCINFOFUNCS_H_
// -----------------




// Function Prototypes for Update Account Information
// -----------------------------------
void UpdateUserInfoMenu(CustomerData**, int);                    // Provides the driver for the Update Account functionality.
int UpdateUserInfoMenuGetInput(int);                             // Retrieves the user's input and tries to provide the signal regarding the user's request.
void UpdateUserInfoMenuUpdateChoice(CustomerData**, int, int);   // Provide the ability to edit a specific value; organized mess!
void UpdateUserInfoShowMenu(CustomerData*, int);                 // Provide the menu to the user.
void UpdateUserInfoMenuUpdateChoice_MSG(char*, char**, int);     // Retrieves the input from the user and filters it.
// -----------------------------------




// Concluding Inclusion Guard
#endif
