// Customer Linked List Functionality
// ================================
// ================================
// This file holds functions related into supporting the Customer
//  Data Linked-List object.  With the functions provided in this
//  file, the functions will allow scanning through, generating,
//  and manipulate the list and nodes as necessary.




// Inclusion Guard
// -----------------
#ifndef _CUSTOMERLINKEDLISTFUNCS_H_
#define _CUSTOMERLINKEDLISTFUNCS_H_
// -----------------




// Function Prototypes for Customer Data
// -----------------------------------
void GenerateUserList(struct CustomerData**);       // Generate predefined users.
static void CreateNewCustomer(CustomerData**,       // Create a new Customer entry
                            const char*, const char*,
                            const char*, const char*,
                            const char*, const char*,
                            const char*, const char*,
                            const char*, const char*,
                            const char*, int);
static void AppendNewCustomer(CustomerData**,       // Add the new customer to
                                CustomerData *);    //   the primary Linked-List.
void ManuallyCreateNewUser(struct CustomerData**,   // Manually create a new user
                            struct CustomerData**, int);
                                                    //  account for our store.
bool FindUser_ReturnUserInfo(CustomerData*,         // Provides the ability to scan
                            CustomerData**,         //  for a user and checks if the
                            char*, char*, int);          //  credentials match.
void UserLogin(CustomerData*,                       // This will provide the procedures
                    CustomerData**, int);                //  for the login system.
void AskUserLogin(char**, char**, int);                  // Ask the user for login information
                                                    //  Required for the login system.
void CreateNewUser_ValueFiltering(char**,           // Filter the newly provided values
                            char**, char**,         //  to the user's account by removing
                            char**, char**,         //  the '\n' char from the values.
                            char**, char**,
                            char**, char**,
                            char**, char**);
// -----------------------------------




// Concluding Inclusion Guard
#endif
