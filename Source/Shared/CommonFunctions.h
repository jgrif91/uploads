// Common Functions
// ================================
// ================================
// This file will hold common functions that may be necessary
//  for both the server program and the client program.  With
//  the use of this file, it is possibly to share common
//  resources with minimal redundancies as possible and minimal
//  impact on code maintenance.




// Inclusion Guard
// -----------------
#ifndef _COMMONFUNCTIONS_H_
#define _COMMONFUNCTIONS_H_
// -----------------




// Function Prototypes
// -----------------------------------
void LowerCaseUserInput(char []);       // Lower cases the entire string provided from the user.
int CheckForUserQuit(char [], int);     // Inspect user's input for a quit\exit request.
void DisplayPrompt(int);                   // Display the Python'ish prompt to the end-user
void ClearBuffer(char [], int);         // Clear the buffer
void FilterUserInputArray(char[], int); // Clean the user's input by removing extra spacing.
void ClearScreen(int);                     // This function will try to 'clear' the terminal buffer.
                                        //  Really, it's just new lines.
void DrawUserLoggedIn(char*, int);                // Display who is viewing the store.
// -----------------------------------




// Concluding Inclusion Guard
#endif
