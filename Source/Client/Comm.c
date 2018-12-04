// Client Communications (listener and responder)
// ================================
// ================================
// This file holds functions that will be necessary
//  for the client to properly communicate back and
//  forth with the Online Service server.




// Included Libraries
// ============================
#include <stdbool.h>            // Because I was spoiled with C++ and C#, just give me the Bool data types!
#include "myunp.h"              // Our custom UNP Header file
#include "CommonFunctions.h"    // Shared functions; to help minimize development cost between sub-projects.
// ============================




// String Client
// -----------------------------------
// Arguments:
//  fp [FILE]
//      File to print to the server [UNUSED]
//  sockfd [int]
//      Socket File descriptor
// -----------------------------------
void str_cli(FILE *fp, int sockfd)
{
    // Declarations and Initializations
    // ----------------------------------
    char sendBuffer[MAXLINE];       // Sending message buffer
    char receiveBuffer[MAXLINE];    // Receiving message buffer
    int maxfdp1;                    // Number of sockets within the array
    fd_set rset;                    // Master file descriptor array
    bool stdinEOF;                  // Shutdown; EOF from keyboard
    int signalCache;                // Cache the signal from the read\write functions
    // ----------------------------------

    // Immediately clear out the entire buffer; avoid garbage
    ClearBuffer(sendBuffer, MAXLINE);
    ClearBuffer(receiveBuffer, MAXLINE);
    // ----
    
    // mark the Shutdown as false
    stdinEOF = false;
    
    // Prepare our File Descriptor
    FD_ZERO(&rset); // Reset all of the descriptor bit-fields
    
    
    // Read and Write to and from the server
    for(;;)
    {
        // Check if the user requested a shutdown; if true - we are no longer listening the STDIN from user
        if (!stdinEOF)
            FD_SET(fileno(fp), &rset);          // Turn on the bit setting for FD in FDSET - STDIN
        FD_SET(sockfd, &rset);                  // Turn on the bit setting for FD in FDSET - Server Connectivity
        maxfdp1 = max(fileno(fp), sockfd) + 1;  // How many to sockets are in the array
        
        
        // BLOCK - STOP_WAIT() for any available updates
        select(maxfdp1, &rset, NULL, NULL, NULL);
        
        // Server responded
        if (FD_ISSET(sockfd, &rset))
        {
            if (stdinEOF)
                return;         // Server responded but EOF was already reached.
            // Server Terminated
            if ((signalCache = read(sockfd, receiveBuffer, MAXLINE)) == 0)
            {
                printf("<!> SERVER DISCONNECTED <!>\n");
                printf("The server is no longer available.\n");
                exit(1);    // System call to stop the program
            } // Server Terminated
            else
            {
                // Display the message
                printf("%s", receiveBuffer);
				fflush(stdout);
            } // Server responded - Message
        } // Server Responded
		
        // End-User Responded (STDIN)
        if (FD_ISSET(fileno(fp), &rset))
        {
			
            // Check if the user wanted to quit
            if ((signalCache = read(fileno(fp), sendBuffer, MAXLINE) == 0) ||     // HotKey to cancel
                !CheckForUserQuit(sendBuffer, strlen(sendBuffer)))  // User typed quit or exit
            {
                printf("Closing Connection. . .\n");
                stdinEOF = 1;
                shutdown(sockfd, SHUT_WR);  // Send Shutdown Signal
                FD_CLR(fileno(fp), &rset);
                printf("Closing program. . .\n");
                exit(0);
            } // User Requested: Termination
            else
            {
                // Throw the message provided from the end-user to the socket.
                write(sockfd, sendBuffer, strlen(sendBuffer));
            } //
        } // End-User Responded (STDIN)
        
        // Clear the buffers
        ClearBuffer(sendBuffer, strlen(sendBuffer));
        ClearBuffer(receiveBuffer, strlen(receiveBuffer));
    } // for()
} // str_cli()
