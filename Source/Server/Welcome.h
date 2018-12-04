// Welcome Menu
// ================================
// ================================
// This file contains the Welcome Menu functions,
//  which will help guide the user into accessing
//  the store.  Because the user must be registered
//  in order to access the store, we will provide
//  the user with some assistance - by asking them
//  if they want to register, login, or exit.




// Inclusion Guard
// -----------------
#ifndef _WELCOMEFUNCS_H_
#define _WELCOMEFUNCS_H_
// -----------------




// Function Prototypes for Welcome Functions
// -----------------------------------
void WelcomeMessage(int);      // Displays the welcome message to the end-user.
int WelcomeProtocol(int);      // Provides the Welcome Protocols
void WelcomeMenu(int);         // Display the welcome menu
int WelcomeFetchInput(int);    // Fetch input regarding the welcome menu
// -----------------------------------




// Concluding Inclusion Guard
#endif
