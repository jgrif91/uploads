// Program Information and Instructions
// ================================
// ================================
// This file holds some of the program information and instructions
//  that could be useful for the user within the program.  Allowing
//  the user read some of the program's contents and help documentation
//  if any are to be provided.




// Included Libraries
// ===============================
#include <stdio.h>              // Input\Output Stream
#include "myunp.h"
#include "GlobalDefs.h"         // Program Macro-Definitions
#include "CommonFunctions.h"    // For Clear Buffer
// ===============================




// Draw Header
// -----------------------------------
// Documentation
//  This function is designed to provide a header to the top-most space on the terminal buffer.
// -----------------------------------
void DrawHeader(int sockfd)
{
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
	
    strcpy(sendbuffer, _NAME_);
	strcat(sendbuffer, " - Version: ");
	strcat(sendbuffer, _VERSION_);
	strcat(sendbuffer, "\n");
    strcat(sendbuffer, _VERSION_NAME_);
	strcat(sendbuffer, "\n-----------------------------------------------\n\n");
	
	write(sockfd, sendbuffer, MAXLINE);
} // DrawHeader()




// Draw About
// -----------------------------------
// Documentation
//  This function provides the 'About' section of the program
// -----------------------------------
void DrawAbout(int sockfd)
{
	char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer, MAXLINE);
	
    strcpy(sendbuffer, "Welcome to the "); 
	strcat(sendbuffer, _NAME_);
	strcat(sendbuffer, " Store!\n");
    strcat(sendbuffer, "--------------------------------------------\n");
    strcat(sendbuffer, "Browse through our collection of games and purchase as many games as you want.  When you purchase a game, the game will be sent to your house by the slowest means possible.  Do note that the game you purchase is mere copies of the game, thus it is a non-genuine copy of the game.  Because of that, we charge extra for the activation or authentication keys.  In addition, there is no refunds if any game CD's and\\or floppies are damaged during shipping.\n");
	write(sockfd, sendbuffer, MAXLINE);
	
	ClearBuffer(sendbuffer, MAXLINE);
	
    strcpy(sendbuffer, "--------\nSee what others are saying about us!\n");
    strcat(sendbuffer, "Reviewer from NY Times: Stay clear from this store!  I ordered a game from there and the experience was totally crappy!  The game took three months to arrive in the mail and the company is merely two __BLOCKS__ away from my house!  The CD I ordered was badly scratch - but magically my computer could still read it just fine.  But what caught me off guard, I need an Activation Key in order to play my game!  I called the company furiously over the phone, but the representatives promptly laughed at me while saying \"SUCKER\"!  Seriously, STAY_AWAY_FROM_THIS_STORE!\n");
	write(sockfd, sendbuffer, MAXLINE);
} // DrawAbout()
