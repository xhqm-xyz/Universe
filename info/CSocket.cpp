#include "CSocket.h"

CSocket_Server::CSocket_Server(int port, IPPROTO net) :
	m_wsa(false), m_bind(false), m_socket(false), m_listen(false)
{
	if (WSAStartup(Sever_info.sockVersion, &Sever_info.wsaData) == 0)
		m_wsa = true;//初始化WSA

	Sever_info.socket = socket(AF_INET, SOCK_STREAM, net);

	if (Sever_info.socket != INVALID_SOCKET)
		m_socket = true;//创建套接字

	SetConnect(port);
}
CSocket_Server::CSocket_Server(IPPROTO net) :
	m_wsa(false), m_bind(false), m_socket(false), m_listen(false)
{
	if (WSAStartup(Sever_info.sockVersion, &Sever_info.wsaData) == 0)
		m_wsa = true;//初始化WSA

	Sever_info.socket = socket(AF_INET, SOCK_STREAM, net);
	if (Sever_info.socket != INVALID_SOCKET)
		m_socket = true;//创建套接字
}

CSocket_Server::~CSocket_Server()
{
	CSocket_Server::StopListen(this);
	std::vector<ClientConnect*>::iterator it;
	std::vector<std::string>::iterator ipit;
	for (it = ClientList.begin(), ipit = IPList.begin();
		it != ClientList.end(), ipit != IPList.end(); it++, ipit++) {
		ClientConnect* Client = (*it);
		closesocket(Client->socket);
		ClientList.erase(it);
		IPList.erase(ipit);
		delete Client;
	}closesocket(Sever_info.socket);
	WSACleanup();
}

ClientConnect* CSocket_Server::GetClient(std::string ip)
{
	std::vector<ClientConnect*>::iterator it;
	for (it = ClientList.begin(); it != ClientList.end(); it++) {
		if ((*it)->ipform == ip)
			return (*it);
	}return nullptr;
}

bool CSocket_Server::SetConnect(int port)
{
	if (m_bind == true)
		m_bind = closesocket(Sever_info.socket);
	Sever_info.addr.sin_family = AF_INET;
	Sever_info.addr.sin_port = htons(port);
	Sever_info.addr.sin_addr.S_un.S_addr = (ULONG)INADDR_ANY;//0x1d91ca3601;//inet_addr(ip.c_str());//
	if (bind(Sever_info.socket, (LPSOCKADDR)&Sever_info.addr, sizeof(Sever_info.addr)) != SOCKET_ERROR)
		m_bind = true;//绑定IP和端口
	if (m_bind)
		m_listener = new std::thread(StarListen, this);
	return m_bind;
}

bool CSocket_Server::OpenClient(ClientConnect* Client)
{
	std::vector<ClientConnect*>::iterator it;
	for (it = ClientList.begin(); it != ClientList.end(); it++)
		if ((*it)->ipform == Client->ipform)
			return false;
	ClientList.push_back(Client);
	IPList.push_back(Client->ipform);
	return Client->m_accept = true;
}

bool CSocket_Server::CloseClient(std::string ip)
{
	std::vector<ClientConnect*>::iterator it;
	std::vector<std::string>::iterator ipit;
	for (it = ClientList.begin(), ipit = IPList.begin();
		it != ClientList.end(), ipit != IPList.end(); it++, ipit++)
		if ((*it)->ipform == ip) {
			ClientConnect* Client = (*it);
			closesocket(Client->socket);
			ClientList.erase(it);
			IPList.erase(ipit);
			delete Client;
			return true;
		}
	return false;
}

bool CSocket_Server::Ssend(const char* mes, std::string ip)
{
	std::vector<ClientConnect*>::iterator it;
	for (it = ClientList.begin(); it != ClientList.end(); it++)
		if ((*it)->ipform == ip)
			return CSocket_Server::Ssend(mes, (*it)->socket);
	return false;
}

void CSocket_Server::Srecv(Sock_DealFun Fun, std::string ip)
{
	std::vector<ClientConnect*>::iterator it;
	for (it = ClientList.begin(); it != ClientList.end(); it++)
		if ((*it)->ipform == ip)
			CSocket_Server::Srecv(Fun, (*it)->socket);
}

bool CSocket_Server::StarListen(CSocket_Server* server)
{
	if (server->m_listen)
		return server->m_listen;
	if (listen(server->Sever_info.socket, 5) != SOCKET_ERROR)
		server->m_listen = true;//开始监听
	ClientConnect* OneClient = new ClientConnect;
	int nAddrlen = sizeof(OneClient->addr);
	while (server->m_listen) {
		printf("等待连接...\n");
		OneClient->socket = accept(server->Sever_info.socket, (SOCKADDR*)&OneClient->addr, &nAddrlen);
		if (OneClient->socket == INVALID_SOCKET)
			continue;
		OneClient->ipform = inet_ntoa(OneClient->addr.sin_addr);
		server->OpenClient(OneClient);
	}if (server->m_listener)
		delete server->m_listener;
	return server->m_listen = false;
}

bool CSocket_Server::StopListen(CSocket_Server* server)
{
	if (server->m_listen) {
		delete server->m_listener;
		server->m_listen = false;
		return !server->m_listen;
	}return server->m_listen;//未开始监听
}

bool CSocket_Server::Ssend(const char* mes, SOCKET socket)
{
	if (send(socket, mes, strlen(mes), 0) == 0)
		return true;
	return false;
}

void CSocket_Server::Srecv(Sock_DealFun Fun, SOCKET socket)
{
	char* mes = new char[DATALEN];
	int ret = recv(socket, mes, DATALEN, 0);
	if (ret > 0)
		if (Fun)
			(*Fun)(mes, ret);
	delete[] mes;
}
















CSocket_Client::CSocket_Client(std::string ip, int port, IPPROTO net) :
	m_wsa(false), m_connect(false), m_socket(false)
{
	Client_info.sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(Client_info.sockVersion, &Client_info.wsaData) == 0)
		m_wsa = true;

	Client_info.socket = socket(AF_INET, SOCK_STREAM, net);
	if (Client_info.socket != INVALID_SOCKET)
		m_socket = true;//创建套接字

	SetConnect(ip, port);
}

CSocket_Client::CSocket_Client(IPPROTO net) :
	m_wsa(false), m_connect(false), m_socket(false)
{
	Client_info.sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(Client_info.sockVersion, &Client_info.wsaData) == 0)
		m_wsa = true;

	Client_info.socket = socket(AF_INET, SOCK_STREAM, net);
	if (Client_info.socket != INVALID_SOCKET)
		m_socket = true;//创建套接字
}

CSocket_Client::~CSocket_Client()
{
	closesocket(Client_info.socket);
	WSACleanup();
}

bool CSocket_Client::SetConnect(std::string ip, int port)
{
	if (m_connect == true)
		m_connect = closesocket(Client_info.socket);
	Client_info.addr.sin_family = AF_INET;
	Client_info.addr.sin_port = htons(port);
	Client_info.addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	if (connect(Client_info.socket, (sockaddr*)&Client_info.addr, sizeof(Client_info.addr)) != SOCKET_ERROR)
		m_connect = true;//绑定IP和端口
	return m_connect;
}

bool CSocket_Client::Csend(const char* mes)
{
	if (send(Client_info.socket, mes, strlen(mes), 0) == 0)
		return true;
	return false;
}

void CSocket_Client::Crecv(Sock_DealFun Fun)
{
	char* mes = new char[DATALEN];
	int ret = recv(Client_info.socket, mes, DATALEN, 0);
	if (ret > 0)
		if (Fun)
			(*Fun)(mes, ret);
	delete[] mes;
}

