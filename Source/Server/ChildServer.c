// ============================================
// Programmers:     Nicholas Gautier
//                  Justin Griffith
//                  Marilyn Li
// Class:           CS3013; Network Programming
// Assignment #:    4
// Due Date:        12.December.2018
// Instructor:      Dr. Zhao
// Description:     This server holds user personal account data,
//                      and also the store itself.  The server merely
//                      is a service, in which allows the users to
//                      purchase products from the store.  The products,
//                      in this case, are video games.  The products and
//                      users that are available within this program are
//                      only accessible via Linked-List, no Databases are
//                      required for this program to work correctly.
//                  Functionality Notes:
//                      Because of the design of the server implementation,
//                          all clients are shifted to a child-server fork.
//                      TCP Sockets will be required; all data is to be
//                          accounted for.
//                      Communication is mainly from the server, client
//                          is only for user-input - nothing more.
//                      Server may waste more bandwidth than what is absolutely
//                          necessary.
//                  Design Flaws (Known Issues):
//                      All changes regarding a user's account - nothing is
//                          permanently saved within the user's account after the
//                          session has been terminated.  This requires the use
//                          of pipes from the child server to the parent server.
//                          This can not be implemented due to time constraints.
//                      Newly created user accounts are not saved after the
//                          session is terminated.  In order to keep user data,
//                          we will need to use both pipes and a reliable database.
// Credits:
//      Lewisk3 (from the ZDoom Community) [NG]
//          Greatly helped me unfuck the Pointeramania issues
//          Seriously, it was bad - like really bad.
//      Gutawer (from the ZDoom Community) [NG]
//          Provided further explanation of pointers to me.
//          I was a bit shaky with pointers, but - he greatly
//          helped me further understand them with simple
//          explanations.
//  Base Source Code provided by W. Richard Stevens in
//      Unix Network Programming, The Sockets Networking API
//      Volume 1, 3rd edition.  All credit goes to him for the framework
// Return Codes:
//  0 = Successful Operation
//  1 = User Requested to leave at Login (normal exit)
//  2 = User Account Validation Failure (Login failure)
//  3 = User Exceeded Login Retries (Bad credentials used)
//  255 = Vague error; usually something really bad.
// ============================================




// Included Libraries
// ===============================
#include <stdio.h>              // Input\Output Stream
#include <stdbool.h>            // Because I was spoiled with C++ and C#, just give me the Bool data types!
#include <ctype.h>              // tolower() functions for user input
#include <stddef.h>             // NULLPTR; used for pointers
#include <stdlib.h>             // Pointer Memory Allocation
#include <time.h>               // time() function for randomized seeds
#include "GlobalDefs.h"         // Program Macro-Definitions
#include "myunp.h"              // Our custom UNP Header file
#include "CommonFunctions.h"    // Shared functions; to help minimize development cost between sub-projects.
#include "CustomerData.h"       // Customer Data Object
#include "GameData.h"           // Game Data Object
#include "ProgInformation.h"    // Instructions and Informational Output
#include "GameLinkedList.h"     // Linked-List Support for Games
#include "CustomerLinkedList.h" // Linked-List Support for Customers
#include "Welcome.h"            // Welcome Menu
#include "MainMenu.h"           // Main Menu
#include "UpdateUserAccount.h"  // Update User Account Information (user card)
#include "ChildServer.h"		// Child Server header that includes function prototypes
// ===============================




// Child Server Implementation
// -----------------------------------
// Arguments:
//  sockfd - connected socket to client
// -----------------------------------
void ChildServer(int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    struct CustomerData*
        customerList = malloc(sizeof(CustomerData));    // Customer Data Linked-List
    struct GameData*
        gameList = malloc(sizeof(GameData));            // Game Data Linked-List
    struct CustomerData*
        sessionUser = malloc(sizeof(CustomerData));     // The user for this session
    bool isContinue = true;                             // User request to terminate the program
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
    // ----------------------------------
    
    // Immediate Execution
    // ===================================
    // All Linked-List heads point to NULL
    customerList = NULL;    // Customer List
    gameList = NULL;        // Game List
    
    // Prepare the linked-lists
    GenerateUserList(&customerList);    // Create the Customer List
    GenerateGameList(&gameList);        // Create the Game List (our catalog)
    // ===================================

    
    // Determine the user's request
    switch (WelcomeProtocol(sockfd))
    {
        case 0:
            printf("User requested to login\n");
			//write(sockfd, sendbuffer, MAXLINE);
            UserLogin(customerList, &sessionUser, sockfd);
            break;
        case 1:
            printf("User requested to register\n");
			//write(sockfd, sendbuffer, MAXLINE);
            ManuallyCreateNewUser(&customerList, &sessionUser, sockfd);
            break;
        case 2:
            printf("User requested to leave\n");
			//write(sockfd, sendbuffer, MAXLINE);
            exit(1);
            break;
        default:
            exit(255);
            break;
    } // switch()
    
    do
    {
        // Clear some space for the main menu screen
        ClearScreen(sockfd);
        
        // Display the program's header
        DrawHeader(sockfd);
        
        // Display the program's about section
        DrawAbout(sockfd);
        
        // Push a few line-feeds to separate the contents
        strcpy(sendbuffer, "\n\n");
		write(sockfd, sendbuffer, MAXLINE);
        ClearBuffer(sendbuffer, MAXLINE);
		
        // Display the user that is presently logged into the system
        DrawUserLoggedIn(sessionUser->userID, sockfd);
        
        // Push a few line-feeds to separate the contents
        strcpy(sendbuffer, "\n\n\n");
		write(sockfd, sendbuffer, MAXLINE);
        ClearBuffer(sendbuffer, MAXLINE);
        
        // Provide the Main Menu and determine the user's request
        switch (MainMenu(sockfd))
        {
            case 0: // Store Page
                StoreDriver(gameList, sessionUser, sockfd);
                break;
            case 1: // Update User Information
                UpdateUserInfoMenu(&sessionUser, sockfd);
                break;
            case 2: // Leave the Store
                isContinue = false;     // Negate this flag; leave the loop
                break;
            default: // Incorrect input or request
                strcpy(sendbuffer, "<!> BAD REQUEST <!>\n");
                strcat(sendbuffer, "-------------------------------\n");
                strcat(sendbuffer, "Please select an option from the menu provided\n");
				write(sockfd, sendbuffer, MAXLINE);
				ClearBuffer(sendbuffer, MAXLINE);
                break;
        } // switch()
    } while(isContinue);
    
    // Prepare to close the program
    CloseProgram(sockfd);
    
    // Terminate the program

} // main()




// Closing Program
// -----------------------------------
// Documentation
//  This function will perform any protocols necessary before the program's instance is destroyed or terminated.
// -----------------------------------
void CloseProgram(int sockfd)
{
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
	
    strcpy(sendbuffer, "Closing program. . .\n\n\n");
} // CloseProgram()
