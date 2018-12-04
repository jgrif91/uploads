// Update User Account Information
// ================================
// ================================
// This file holds functions that allows the user to update their
//  personal account information.  Thus, their settings are changed
//  in real time during their active session with the service.




// Included Libraries
// ===============================
#include <stdio.h>              // Required for input and output
#include <stdbool.h>            // Because I was spoiled with C++ and C#, just give me the Bool data types!
#include <string.h>             // strcmp() for User Account Authentication Challenge
#include <stdlib.h>             // Pointer Memory Allocation
#include "CommonFunctions.h"    // Prompt
#include "CustomerData.h"       // Game Data Object
#include "GlobalDefs.h"         // Program Macro-Definitions
#include "MainMenu.h"           // Main Menu
#include "UpdateUserAccount.h"  // Update User Account Information (user card)
#include "myunp.h"				// For MAXLINE
// ===============================




// Update User Information Menu
// -----------------------------------
// Documentation:
//  This will provide the user with the ability
//  to choose what they want to update regarding
//  their personal information that is stored on
//  their account.
// -----------------------------------
// Parameters:
//  userCard [CustomerData]
//      session user's information that will be
//      update during this process.
// -----------------------------------
void UpdateUserInfoMenu(CustomerData **userCard, int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    bool isContinue = true;     // User request to leave this menu
    int userRequest;            // User's request
	char sendbuffer[MAXLINE];
    // ----------------------------------
    
    // Run the User Update Menu Loop
    do
    {
		ClearBuffer(sendbuffer, MAXLINE);
		DrawUserLoggedIn((*userCard)->userID, sockfd);  // Show who is currently logged into the session
		strcpy(sendbuffer, "\n\n");   	// Provide extra padding for readability
		write(sockfd, sendbuffer, MAXLINE);
		UpdateUserInfoShowMenu(*userCard, sockfd);      // Display the Menu
    
		userRequest =                           // Get the user's request and cache the value
			UpdateUserInfoMenuGetInput(sockfd);       //  to process it.
    
		// Inspect the user's input
		if (userRequest < 10)       // Execute the user's request
			UpdateUserInfoMenuUpdateChoice(userCard, userRequest, sockfd);
		else if (userRequest == 10) // Return to main menu
			isContinue = false;
		else
		{
			ClearBuffer(sendbuffer, MAXLINE);
			strcpy(sendbuffer, "<!> BAD REQUEST <!>\n");
			strcat(sendbuffer, "-------------------------------\n");
			strcat(sendbuffer, "Please select an option from the menu provided\n");
			write(sockfd, sendbuffer, MAXLINE);
		}
	} while(isContinue);
} // UpdateUserInfoMenu()




// Update User Information - Get Input
// -----------------------------------
// Documentation:
//  This function will retrieve the input from the
//  user and then report back what the user has
//  requested regarding from the User Information
//  Update Menu.
// -----------------------------------
// Output:
//  Returns the user's request
//      0 = Selected was First Name
//      1 = Selected was Last Name
//      2 = Selected was Account Password
//      3 = Selected was E-Mail Address
//      4 = Selected was Phone Number
//      5 = Selected was Address [City]
//      6 = Selected was Address [State]
//      7 = Selected was Address [Country]
//      8 = Selected was Address [Street]
//      9 = Selected was Address [Zip]
//     10 = Return to main menu
//    255 = Bad Request
// -----------------------------------
int UpdateUserInfoMenuGetInput(int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    char userInput[MAXLINE];    // This will hold the user input.
	ClearBuffer(userInput, MAXLINE);
    // ----------------------------------
    
    // Display the prompt
    DisplayPrompt(sockfd);
    
    // Get the user input
    read(sockfd, userInput, MAXLINE);
    
    // Lower case the user's input
    LowerCaseUserInput(userInput);
    
    // I am dreading the fact that I can't use a switch() to pull this off...
    //  I am sorry for those that are reading this; there has to be a better
    //  way to handle this, but due to time-constraint - I can't do reasonable
    //  research to figure this out.  Instead, I know If(cond.) will work
    //  just - - I'd rather use something nicer... [NG]
    if (!strncmp(userInput, "1\n", 2)) // already regretting my life's decisions.... [NG]
        return 0;   // First Name
    else if (!strncmp(userInput, "2\n", 2)) // ugh...
        return 1;   // Last Name
    else if (!strncmp(userInput, "3\n", 2)) // I
        return 2;   // Account Password
    else if (!strncmp(userInput, "4\n", 2)) // Hate
        return 3;   // E-Mail Address
    else if (!strncmp(userInput, "5\n", 2)) // This
        return 4;   // Phone Number
    else if (!strncmp(userInput, "6\n", 2)) // Seriously
        return 5;   // Address - City
    else if (!strncmp(userInput, "7\n", 2)) // I am
        return 6;   // Address - State
    else if (!strncmp(userInput, "8\n", 2)) // sorry
        return 7;   // Address - Country
    else if (!strncmp(userInput, "9\n", 2)) // that you
        return 8;   // Address - Street
    else if (!strncmp(userInput, "10\n", 3))// are reading this...
        return 9;   // Address - Zip
        
    // -------------------
    // CHECK FOR RETURN TO MAIN MENU REQUEST
    // -------------------
    else if (!CheckForUserQuit(userInput, MAXLINE))
        return 10;  // Return to Main Menu
    else if ((!strncmp(userInput, "x\n", 2)) ||
            (!strncmp(userInput, "X\n", 2)))
        return 10;  // Return to Main Menu
    
    // -------------------
    // UNKNOWN REQUEST
    // -------------------
    else 
        return 255; // Unknown Request
} // UpdateUserInfoMenuGetInput()




// Update User Information - Update Request
// -----------------------------------
// Documentation:
//  This function will allow the user to actually
//  update their information based on their request.
// -----------------------------------
// Parameters:
//  userCard [CustomerData]
//      The user's personal information that will be modified.
//  request [int]
//      What is to be modified on the user's User Card.
// -----------------------------------
void UpdateUserInfoMenuUpdateChoice(CustomerData **userCard, int request, int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    char *userInput = (char*)malloc(sizeof(char)*_MAX_CHAR_INPUT_);
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
    // ----------------------------------
    
    
    // Execute the user's request
    switch(request)
    {
        case 0: // First Name
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->firstName, &userInput, sockfd);
            (*userCard)->firstName = userInput;
            break;
        case 1: // Last Name
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->lastName, &userInput, sockfd);
            (*userCard)->lastName = userInput;
            break;
        case 2: // Account Password
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->userKey, &userInput, sockfd);
            (*userCard)->userKey = userInput;
            break;
        case 3: // E-Mail Address
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->email, &userInput, sockfd);
            (*userCard)->email = userInput;
            break;
        case 4: // Phone Number
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->phoneNumber, &userInput, sockfd);
            (*userCard)->phoneNumber = userInput;
            break;
        case 5: // Address [City]
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->addressCity, &userInput, sockfd);
            (*userCard)->addressCity = userInput;
            break;
        case 6: // Address [State]
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->addressState, &userInput, sockfd);
            (*userCard)->addressState = userInput;
            break;
        case 7: // Address [Country]
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->addressCountry, &userInput, sockfd);
            (*userCard)->addressCountry = userInput;
            break;
        case 8: // Address [Street]
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->addressStreet, &userInput, sockfd);
            (*userCard)->addressStreet = userInput;
            break;
        case 9: // Address [Zip]
            UpdateUserInfoMenuUpdateChoice_MSG((*userCard)->addressPostalCode, &userInput, sockfd);
            (*userCard)->addressPostalCode = userInput;
            break;
        default:// Bad key; don't fatally error out - no reason too.
			ClearBuffer(sendbuffer, MAXLINE);
            strcpy(sendbuffer, "<!> ERROR <!>\n");
            strcat(sendbuffer, "--------------------------------\n");
            strcat(sendbuffer, "Unknown User Card Request!\nRequest was canceled!\n");
			write(sockfd, sendbuffer, MAXLINE);
            break;
    } // switch()
} // UpdateUserInfoMenuUpdateChoice()




// Update User Information Menu Update Choice - Message [Because long function names are cool!]
// -----------------------------------
// Documentation:
//  This function, merely reducing repetitiveness, allows
//  the user to provide an update on their personal information.
//  After which, the user's input will be cleaned-up and sent
//  back for further instructions.
// -----------------------------------
// Parameters:
//  msg [char]
//      The present value that currently exists.
//  response [char]
//      The new value that will replace the older-value
//      [relating to the 'msg' variable above]
// -----------------------------------
void UpdateUserInfoMenuUpdateChoice_MSG(char* msg, char **response, int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    bool isContinue = true;     // Handle's the loop; if input is valid
	char sendbuffer[MAXLINE];
    // ----------------------------------
    
    // Capture a valid response from the user
    do
    {
		ClearBuffer(sendbuffer, MAXLINE);
        // Display the current value
        strcpy(sendbuffer, "Currently: ");
		strcat(sendbuffer, msg);
		strcat(sendbuffer, "\n");
        
        // Tell the user to provide a new value
        strcat(sendbuffer, "Provide a new value\n");
		write(sockfd, sendbuffer, MAXLINE);
		ClearBuffer(sendbuffer, MAXLINE);
		
        DisplayPrompt(sockfd);
        
        // Fetch the new value
		ClearBuffer(*response, MAXLINE);
        read(sockfd, *response, MAXLINE);
        
        // Clean it up; otherwise the '\n' char
        //  will still remain in the new value.
        FilterUserInputArray(*response, MAXLINE);
        
        if (!strncmp(*response, "\0", 1))
		{
			ClearBuffer(sendbuffer, MAXLINE);
            strcpy(sendbuffer, "!ERR!: Please provide a valid value!\n\n");   // Bootless Star's old error messages :) [NG]
			write(sockfd, sendbuffer, MAXLINE);
			ClearBuffer(sendbuffer, MAXLINE);
		}
		
		else
		{
            isContinue = false;
		}
    } while(isContinue);
} // UpdateUserInfoMenuUpdateChoice_MSG()




// Update User Information - Show Menu
// -----------------------------------
// Documentation:
//  This function will provide the user with the
//  Update User Information Menu and any instructions
//  necessary when dealing with the this menu.
// -----------------------------------
// Parameters:
//  userCard [CustomerData]
//      Only used to display the user's current information.
// -----------------------------------
void UpdateUserInfoShowMenu(CustomerData *userCard, int sockfd)
{    
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
	
    strcpy(sendbuffer, "Update User Information Menu\n");
    strcat(sendbuffer, "------------------------------------------------\n\n");
    // User's First Name
    strcat(sendbuffer, "[1] - First Name\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->firstName);
	strcat(sendbuffer, "\n");
    // User's Last Name
    strcat(sendbuffer, "[2] - Last Name\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->lastName);
	strcat(sendbuffer, "\n");
    // User's Account Password
    strcat(sendbuffer, "[3] - Account Password\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->userKey);
	strcat(sendbuffer, "\n");
    // User's E-Mail Address
    strcat(sendbuffer, "[4] - E-Mail Address\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->email);
	strcat(sendbuffer, "\n");
    // User's Phone Number
    strcat(sendbuffer, "[5] - Phone Number\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->phoneNumber);
	strcat(sendbuffer, "\n");
    // User's Address [City]
    strcat(sendbuffer, "[6] - Address [City]\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->addressCity);
	strcat(sendbuffer, "\n");
    // User's Address [State]
    strcat(sendbuffer, "[7] - Address [State]\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->addressState);
	strcat(sendbuffer, "\n");
    // User's Address [Country]
    strcat(sendbuffer, "[8] - Address [Country]\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->addressCountry);
	strcat(sendbuffer, "\n");
    // User's Address [Street]
    strcat(sendbuffer, "[9] - Address [Street]\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->addressStreet);
	strcat(sendbuffer, "\n");
    // User's Address [Zip]
    strcat(sendbuffer, "[10] - Address [Zip Code]\n");
    strcat(sendbuffer, "       Current Value: ");
	strcat(sendbuffer, userCard->addressPostalCode);
	strcat(sendbuffer, "\n");
    // Leave the menu
    strcat(sendbuffer, "[X] - Return to Main Menu\n");
	
	write(sockfd, sendbuffer, MAXLINE);
	ClearBuffer(sendbuffer, MAXLINE);
} // UpdateUserInfoShowMenu()
