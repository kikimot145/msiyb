#include "stdafx.h"
#include "server.h"

Server::Server()
{
	// call config reader
}

Server::~Server()
{

}

void Server::Start()
{
	/*
		Initialize listener port
		Bind and start listen
	*/


	while (1)
	{
		/*
			Waiting for request
			Handle request with single thread
			Each thread handle comands 
			So:
			TODO: thread.h (also divided for different OS)
		*/
	}
}
