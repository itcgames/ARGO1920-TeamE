#include "Server.h"
#include <iostream>

int main()
{
	Server m_server(8888,true);
	for (int i = 0; i < 100; i++)
	{
		m_server.ListenForNewConnection();
	}
	return 0;
	system("PAUSE");
}