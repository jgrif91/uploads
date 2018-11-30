#include	"myunp.h"

int
main()
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	//void				sig_chld(int);

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

		if ( (childpid = fork()) == 0) {	//creates child server
			close(listenfd);	// closes listening server socket
			
			//calls the main driver for the child server function and passes the socket used to connect to the client
			childServer(connfd);	
			
			exit(0);				//exits the child process
		}
		close(connfd);			// close the connection socket
	}
}
