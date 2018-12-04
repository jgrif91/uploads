// ============================================
// Programmers:     Nicholas Gautier
//                  Justin Griffith
//                  Marilyn Li
// Class:           CS3013; Network Programming
// Assignment #:    4
// Due Date:        12.December.2018
// Instructor:      Dr. Zhao
// Description:     The client requires a stable connection
//                      to the server, which the server performs
//                      all transactions and services.  The client
//                      program is needed in order to interact
//                      with the server's services.  The client,
//                      by itself, depends heavily on the select()
//                      functionality.  This is required as the
//                      server will push multiple messages through
//                      the TCP socket; the client is only required
//                      to send the end-user's request to the server.
//                      The client program is incapable of operating
//                      without the server being active.
// Credits:
//      Lewisk3 (from the ZDoom Community) [NG]
//          Greatly helped me unfuck the Pointeramania issues
//          Seriously, it was bad - like really bad.
//  Base Source Code provided by W. Richard Stevens in
//      Unix Network Programming, The Sockets Networking API
//      Volume 1, 3rd edition.  All credit goes to him for the framework
// Return Codes:
//  0 = Successful Operation
//  1 = Connection to the server was disconnected abruptly
//  2 = Incorrect arguments when program was invoked
// ============================================




// Included Libraries
// ============================
#include "myunp.h"              // Our custom UNP Header file
#include "CommonFunctions.h"    // This contains our common functions
                                //  will be available through out the
                                //  entire program.
#include "Comm.h"               // Client Communication
// ============================




// Main
// -----------------------------------
// Arguments:
//  argc [int]
//      How many arguments has been passed
//  argv [multi-string]
//      Arguments passed
// -----------------------------------
int main(int argc, char **argv)
{
    // Declarations and Initializations
    // ----------------------------------
    int sockfd;                     // Socket File Descriptor
    struct sockaddr_in servaddr;    // Server Info Struct.
    // ----------------------------------

    // Make sure that the program was invoked correctly.
    if (argc != 2)
    {
        printf("<!> Insufficient parameters <!>\n");
        printf("---------------------------------\n");
        printf("Please include the IP Address of the server that you want to connect.\n");
        printf("For example: client <server address>\n");
        printf("             client 127.0.0.1\n");
        exit(2);
    } // Incorrect arguments
    
    // Create the Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Reset all of the bits of servaddr to null
    bzero(&servaddr, sizeof(servaddr));

    // Internet Protocol [v4]
    servaddr.sin_family = AF_INET;

    // Port Number
    servaddr.sin_port = htons(SERV_PORT);

    // Converts the address to binary form
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    // Connect to the server
    connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    // Execute the client's Read\Write echo
    str_cli(stdin, sockfd);

    // Terminate the program
    exit(0);
} // main()
