#pragma once
//#define WIN32_LEAN_AND_MEAN
#include <cstdio>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
#include <winsock2.h>

#define DATALEN 255*1024
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
typedef void (*Sock_DealFun)(char*, int);

struct wsa_info {
	u_short port = 0;
	std::string IP = "";
	sockaddr_in addr = { 0 };
	SOCKET socket = { 0 };
	WSADATA wsaData = { 0 };
	WORD sockVersion = MAKEWORD(2, 2);
};
struct ClientConnect {
	SOCKET socket = { 0 };
	sockaddr_in addr = { 0 };
	std::string ipform = "";
	bool m_accept = false;//是否处于连接状态
	std::thread* cl_thr = nullptr;
};

class CSocket_Server//服务器
{
public:
	CSocket_Server(int port, IPPROTO net = IPPROTO_TCP);
	~CSocket_Server();

	bool SetBind(int port);
	bool OpenClient(ClientConnect* Client);
	bool CloseClient(std::string ip);

	bool Ssend(const char* mes, std::string ip);
	void Srecv(Sock_DealFun Fun, std::string &ip);
	std::vector<std::string> GetClientIPlist() { return IPList; };

	static bool StarListen(CSocket_Server* server);
	static bool StopListen(CSocket_Server* server);
public:

protected:
	IPPROTO m_net;
	wsa_info Sever_info;
	bool m_wsa;		//初始化
	bool m_bind;	//绑定IP
	bool m_socket;	//套接字
	bool m_listen;	//是否正在监听  
	Sock_DealFun fun = nullptr;
	std::thread* m_listener = nullptr;
	std::vector<std::string> IPList;
	std::vector<ClientConnect*> ClientList;
};

class CSocket_Client//客户端
{
public:
	CSocket_Client(std::string ip, int port, IPPROTO net = IPPROTO_TCP);
	~CSocket_Client();

	bool GetConnect() { return m_connect; };
	bool SetConnect(std::string ip, int port);
	bool Csend(const char* mes);
	void Crecv(Sock_DealFun Fun);
protected:
	IPPROTO m_net;
	wsa_info Client_info;
	bool m_wsa;		//初始化
	bool m_socket;	//套接字
	bool m_connect;	//链接与否
};
