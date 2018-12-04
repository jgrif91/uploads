// Included Libraries
// ===============================
#include "myunp.h" 		// included for write()
#include "CommonFunctions.h"
#include "../Server/GlobalDefs.h" // included for _MAX_CHAR_INPUT_
// ===============================

// Common Functions
// ================================
// ================================
// This file will hold common functions that may be necessary
//  for both the server program and the client program.  With
//  the use of this file, it is possibly to share common
//  resources with minimal redundancies as possible and minimal
//  impact on code maintenance.


// Lowercase User Input
// ------------------------
// Documentation
//  This function takes the input provided by the user and
//  lowers all cases within the string.
// ------------------------
// Parameters
//  string [char*]
//      string to lower all alphabets letters
// ------------------------
// Includes
//  Used for 'tolower()'
#include <ctype.h>
// ------------------------
void LowerCaseUserInput(char string[])
{
    for(int i = 0; string[i] != '\0'; i++)
        string[i] = tolower(string[i]);
} // LowerCaseUserInput




// Check for User Quit
// ------------------------
// Documentation
//  This function will inspect the user's input and check to see
//  if the user has requested a termination.
// ------------------------
// Parameters
//  string [char*]
//      char[] to inspect; this is the user's request to examine.
//  stringSize [int]
//      the size of the char array size.
// ------------------------
// Dependency List
//  LowerCaseUserInput()
// ------------------------
// Includes
//  Used for 'strcmp()'
#include <string.h>
// ------------------------
int CheckForUserQuit(char string[], int stringSize)
{
    // Declarations and Initializations
    // ----------------------------------
    char workingString[stringSize]; // Holds 'string' var
                                    //  Because we are going to alter 'string' var,
                                    //  we do NOT want to alter the final result.
                                    //  We cache the value and allow that to be changed.
    // ----------------------------------
    
    // Copy the string value to our cache var.
    strcpy(workingString, string);
    
    // Lower all alphabet letters in the array
    LowerCaseUserInput(workingString);

    // Check for termination requests
    if (strcmp("exit\n", workingString) == 0)
        return 0; // Match!
    else if (strcmp("quit\n", workingString) == 0)
        return 0; // Match!
    else if (strcmp("exit", workingString) == 0)
        return 0; // Match!
    else if (strcmp("quit", workingString) == 0)
        return 0; // Match!
    else
        return 1; // Not a match!
} // CheckForUserQuit()




// Display Prompt (Pythonish)
// ------------------------
// Documentation
//  This function will display the prompt message; this is
//      to indicate that we are ready for user input.
// ------------------------
// Includes
//  Used for 'strcmp()'
#include <stdio.h>
// ------------------------
void DisplayPrompt(int sockfd)
{
	char indicator[] = ">>>>> \0";
	write(sockfd, indicator, MAXLINE);
} // DisplayPrompt()



// Clear Buffer
// ------------------------
// Documentation
//  This function will clear the char[] buffer.  This is useful to clear
//      out any pre-existing char's left over from the previous messages.
// ------------------------
// Parameters
//  stringBuffer [char*]
//      string char array to clear.
//  bufferSize [int]
//      Buffer size of the char array.
// ------------------------
void ClearBuffer(char stringBuffer[], int bufferSize)
{
    memset(stringBuffer, '\0', bufferSize);
} // ClearBuffer()




// Clear Screen
// -----------------------------------
// Documentation:
//  This function will provide enough spacing to avoid having a cluttered
//  wall of text.  Thus, providing a cleaner look when accessing a new
//  option or field.
// -----------------------------------
void ClearScreen(int sockfd)
{
    char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer,MAXLINE);

	strcpy(sendbuffer, "\n\n\n\n\n\n\n");
	write(sockfd, sendbuffer, MAXLINE);
} // ClearScreen()




// Draw User Logged-In Status
// -----------------------------------
// Documentation
//  This function will simply provide who is presently logged into the store.
// -----------------------------------
// Parameters:
//  screenName [char*]
//      The User ID that this session is attached to presently.
// -----------------------------------
void DrawUserLoggedIn(char *screenName, int sockfd)
{
    char sendbuffer[MAXLINE];
	ClearBuffer(sendbuffer,MAXLINE);
	
	strcpy(sendbuffer, "You are logged in as: ");
	strcat(sendbuffer, screenName);
	strcat(sendbuffer, "\n");
	
	write(sockfd, sendbuffer, MAXLINE);
} // DrawUserLoggedIn()




// Filter User's Input [Buffer]
// -----------------------------------
// Documentation:
//  This function will filter the user's input within
//  the buffer by determining where the user's input 'ended'
//  and applying a terminator at that point.  Otherwise,
//  the buffer will contain the null terminator at the end
//  of the array.
// -----------------------------------
// Methodology:
//  Scan the array for a white space and check if the next index
//  also contains a white space.  If there are two consecutive
//  white spaces, _assume_ that the rest is empty.
//  At the first white-space of the two consecutive spaces, add
//  the termination at that index.  For example:
//      +---+---+---+---+---+--+--+--+--+--+--+
//      | H | E | L | L | O |  |  |  |  |  |\0|
//      +---+---+---+---+---+--+--+--+--+--+--+
//  We will add the '\o' at the next index after
//  'O', because following 'O' we have at least two
//  consecutive spaces (more than that, actually).
//  HOWEVER, this leads to an issue where the buffer
//  purposely cut out any text that may exist after the two
//  spaces.  For example:
//      +---+---+---+---+---+--+--+---+---+---+---+--+
//      | H | E | L | L | O |  |  | C | A | T | S |\0|
//      +---+---+---+---+---+--+--+---+---+---+---+--+
//  "CATS" will be ignored because of the two consecutive spaces
//  after the 'O' in "HELLO".  Meaning, all that exists is
//  simply:
//      +---+---+---+---+---+--+--+---+---+---+---+--+
//      | H | E | L | L | O |\0|  | C | A | T | S |\0|
//      +---+---+---+---+---+--+--+---+---+---+---+--+
//  Or simply "HELLO".
//
//  The methodology is simple by design and because of that
//  it is subject-able to it's own limitations.
//  NOTE: This rule now also applies to the '\n' character.
// -----------------------------------
// Parameters:
//  buffer[] [char]
//      The buffer used to get user input.
//  bufferSize [int]
//      The size of the buffer.
// -----------------------------------
void FilterUserInputArray(char buffer[], int bufferSize)
{
    // We are going to inspect the buffer
    for (int i = 0; i < bufferSize; ++i)
    {
        if((buffer[i] == ' ' && buffer[1+i] == ' ')     // Two consecutive white spaces?
            || buffer[i] == '\n')                       // Or did we find the '\n' char?
        {
            buffer[i] = '\0';                           // Replace that instance with a null-terminator.
            return;                                     // Leave the function, we are done here!
        } // if :: Two White Spaces
    } // for()
} // FilterUserInputArray()
