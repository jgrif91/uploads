// Main Menu Functionality
// ================================
// ================================
// This file will hold the Main Menu functionality,
//  thus providing the gateway for the user to
//  interact with the program and to perform their
//  desired request.




// Included Libraries
// ===============================
#include <stdio.h>              // Input\Output Stream
#include "GlobalDefs.h"         // Program Macro-Definitions
#include "CommonFunctions.h"    // Shared functions; to help minimize development cost between sub-projects.
#include "MainMenu.h"           // Main Menu
#include "myunp.h"				// For read()/write() and MAXLINE
// ===============================




// Main Menu
// -----------------------------------
// Documentation:
//  This function will allow the user to provide
//  their request - which will allow them to navigate
//  within the program.
// -----------------------------------
// Output:
//  0 = Store Page
//  1 = Update User Information
//  2 = Exit
//  3 = Bad request
// -----------------------------------
int MainMenu(int sockfd)
{
    DrawInstructionsMainMenu(sockfd);     // Draw Instructions
                                    //  regarding the main menu.
    DrawMenuMain(sockfd);                 // Provide the Main Menu
    return MainMenuUserRequest(sockfd);   // Fetch user input
} // MainMenu()




// Main Menu User Request
// -----------------------------------
// Documentation:
//  This will allow the user to provide input in regards to
//  the main menu, but the input will also be modified to work
//  within this program.
// -----------------------------------
// Output:
//  0 = Store Page
//  1 = Update User Information
//  2 = Exit
//  3 = Bad request
// -----------------------------------
int MainMenuUserRequest(int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    char userInput[_MAX_CHAR_INPUT_];    // This will hold the user input.
    // ----------------------------------
    
    // Display the prompt
    DisplayPrompt(sockfd);
    
    // Get the user input
    read(sockfd, userInput, _MAX_CHAR_INPUT_);
    
    // Lower case the user's input
    LowerCaseUserInput(userInput);
    
    // Try to determine the user's request
    if (userInput[0] == '1')
        // Store Page
        return 0;
    else if (userInput[0] == '2')
        // Update User Information
        return 1;
    else if (userInput[0] == 'x')
        // Exit from the Store
        return 2;
    else if (!CheckForUserQuit(userInput, _MAX_CHAR_INPUT_))
        // Exit from the store (Exit or Quit keywords)
        return 2;
    else
        // Unknown Request
        return 3;    
} // MainMenuUserRequest()




// Draw Main Menu
// -----------------------------------
// Documentation:
//  This will provide the main menu to the user.
// -----------------------------------
void DrawMenuMain(int sockfd)
{
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
	
    strcpy(sendbuffer, "Main Menu\n------------------------------------------------\n\n");
    // View Store Catalog
    strcat(sendbuffer, "[1] - View Game Store\n");
    strcat(sendbuffer, "       View what games are available within our store!\n");
    // Update Personal Information
    strcat(sendbuffer, "[2] - Update Personal Information\n");
    strcat(sendbuffer, "       View and change your personal account settings, such as email, address, etc.\n");
    // Leave terminate session
    strcat(sendbuffer, "[X] - Leave Store\n");
    strcat(sendbuffer, "       Exit from the store\n");
	
	write(sockfd, sendbuffer, MAXLINE);
} // DrawMenuMain()




// Draw Instructions
// -----------------------------------
// Documentation
//  This function will provide the instructions to the client,
//  in regards into how to use the main menu screen.
// -----------------------------------
void DrawInstructionsMainMenu(int sockfd)
{
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
	
    sprintf(sendbuffer, "Select the following options from the screen:\n");
	write(sockfd, sendbuffer, MAXLINE);
	
} // DrawInstructions()
