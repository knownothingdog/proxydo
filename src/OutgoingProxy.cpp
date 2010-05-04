#include "sockets/api.h"
#include <string>
#include <iostream>
#include "config.h"

#include "OutgoingProxy.h"

OutgoingProxy::OutgoingProxy() {
	
OutgoingProxy::OutgoingProxy(int port, vector<string> bloquedHost) : port(port), bloquedHost(bloquedHost)) {
	
}
void OutgoingProxy::run(){
	cout<<"[INFO] Starting..."<<endl;
	try{
		ServerSocket server (port);
		while ( true ){
			
			ServerSocket sock_server;
			server.accept ( sock_server );
			try{
				while ( true ){
					OutgoingProxy::DestinationThread(sock_server,v);	
				}
			}
			catch ( SocketException& ) {
			}
		}
	}
	catch ( SocketException& e ){
		cout << "[EXCEPTION] " << e.description() << "\n[INFO] Closing...\n";
	}
}
	
void OutgoingProxy::DestinationThread(ServerSocket sock_server,vector<string> bloquedHost){
		string data;
		sock_server >> data; //READ FROM ORIGIN
		//READ FROM VECTOR IF DESTINATION IS VALID
		cout << "[MESSAGE] " <<data<<endl; //MESSAGE
		//GET HOST
		//GET PORT
		try{
	      ClientSocket client_socket ( "google.com",80);
	      try{
		  client_socket << data;
		  client_socket >> data;
		}
	      catch ( SocketException& ) {}
	      cout << "We received this response from the server:\n\"" << data << "\"\n";;
	    }
	  catch ( SocketException& e ){
	     cout << "Exception was caught:" << e.description() << "\n";
	    }
		sock_server << data; //WRITE TO ORIGIN
	}
}