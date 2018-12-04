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
#include	"myunp.h"
#include	"sigchldwaitpid.h"
#include	"ChildServer.h"
// ===============================




// Main
// -----------------------------------
int main()
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

	//creates listening socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr)); //clears the server address bits before creating a new socket
	
	//IPv4 family for socket
	servaddr.sin_family      = AF_INET;

	//sets the server address to the IP address assigned to INADDR_ANY
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//sets the server in port to the value assigned to the SERV_PORT value
	servaddr.sin_port        = htons(SERV_PORT);

	//Binds the listening socket to the listenfd
	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));	

	listen(listenfd, LISTENQ);			//listens for client request

	signal(SIGCHLD, sig_chld);			//creates a signal handler for child processes

	for ( ; ; ) {
		clilen = sizeof(cliaddr);		//used to detail the length of the client's address
		connfd = accept(listenfd, (SA *) &cliaddr, &clilen); //stores value returned from "accept()" in "connfd"
		childpid = fork();
		
		if (childpid == 0) {	//creates child server
			close(listenfd);	// closes listening server socket
			
			//calls the main driver for the child server function and passes the socket used to connect to the client
			ChildServer(connfd);	
			close(connfd);			// close the connection socket
			exit(0);				//exits the child process
		}
		
	}
}
