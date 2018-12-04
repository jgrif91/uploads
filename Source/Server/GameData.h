// Game Data Structure
// ================================
// ================================
// This file holds the Game Data's Structure.  This will hold all of the
//  information necessary for the Linked-List Node-Chain.  Thus allowing
//  a basic template for holding the game data.




// Inclusion Guard
// -----------------
#ifndef _GAMEDATASTRUCT_H_
#define _GAMEDATASTRUCT_H_
// -----------------




// Game Data Structure
// -----------------------------------
typedef struct GameData
{
    char* title;            // Title of the game
    char* description;      // Description of the game
    char* publisher;        // Publisher of the game
    char* developers;       // Developers (or company) that created the game
    char* genre;            // Genre of the game
    char* notes;            // Specialized notes regarding the game
    
    // Linked List Functionality
    struct GameData *next;
} GameData;




// Concluding Inclusion Guard
#endif
