// Customer Data Structure
// ================================
// ================================
// This file holds the Customer Data's Structure.  This will hold all of the 
//  information necessary for the Linked-List Node-Chain.  Thus allowing
//  a basic template for holding user data.




// Inclusion Guard
// -----------------
#ifndef _CUSTOMERDATASTRUCT_H_
#define _CUSTOMERDATASTRUCT_H_
// -----------------




// Customer Data Structure
// -----------------------------------
typedef struct CustomerData
{
    char* firstName;            // The user's First Name
    char* lastName;             // The user's Last Name
    char* userID;               // The user's Sign-In and User Name for the service.
    char* userKey;              // The user's Password in a non-secured fashion.
        // SECURITY NOTE: Because the password is in _RAW_TEXT_ form, security is NOT
        //  being practiced here.  This is merely a simulation program, not a REAL WORLD
        //  Application!  Please take that into consideration.  [NG]
    char* email;                // The user's Email Address.
    char* phoneNumber;          // The user's Phone Number.
    char* addressCity;          // The user's Address: City/Village
    char* addressState;         // The user's Address: State
    char* addressCountry;       // The user's Address: Country
    char* addressStreet;        // The user's Address: Street
    char* addressPostalCode;    // The user's Address: Postal Code
    int admin;                  // Is this user part of the Administration team?
    
    // Linked List Functionality
    struct CustomerData *next;
} CustomerData;




// Concluding Inclusion Guard
#endif
