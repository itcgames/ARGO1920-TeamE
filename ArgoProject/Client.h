#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <WinSock2.h> //For win sockets
#include <string> //For std::string
#include <iostream> 
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "Server.h"
#include<assert.h>

class Game;


class Client
{
public: //Public functions
	Client(std::string IP, int PORT);
	bool Connect();

	bool SendString(std::string& _string);
	bool SendCircle();
	bool CloseConnection();

	std::vector<std::string> vec;
    std::vector<std::string> vec1;

private: //Private functions
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//Sending Funcs
	bool sendall(char* data, int totalbytes);
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);


	//Getting Funcs
	bool recvall(char* data, int totalbytes);
	bool GetInt(int& _int);
	bool GetPacketType(Packet& _packettype);
	bool GetString(std::string& _string);
	bool GetEntity(std::string& _string);



private:
	SOCKET Connection;//This client's connection to the server
	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
};

static Client* clientptr; //This client ptr is necessary so that the ClientThread method can access the Client instance/methods. Since the ClientThread method is static, this is the simplest workaround I could think of since there will only be one instance of the client.


