#pragma once
#include <ctime>
#include <string>
#include <vector>
#include <thread>
#include <windows.h>
#pragma warning(disable : 4996)

#include "./mqtt/include/MQTTAsync.h"
#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3a-static.lib")	//最好使用release版
#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3as-static.lib")	//最好使用release版

//#include "./mqtt/include/MQTTClient.h"
//#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3c-static.lib")	//最好使用release版
//#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3cs-static.lib")//最好使用release版

typedef void (*MQTT_LostCon)(void*, char*);								//丢失连接
typedef void (*MQTT_DealSub)(void*, char*, int, MQTTAsync_message*);	//订阅信息处理
//typedef void (*MQTT_DealSub5)(void*, char*, int, MQTTAsync_message*);	//订阅信息处理

typedef void (*MQTT_ConSuss)(void*, MQTTAsync_successData*);			//连接成功
typedef void (*MQTT_ConFail)(void*, MQTTAsync_failureData*);			//连接失败
typedef void (*MQTT_DisaCon)(void*, MQTTAsync_successData*);			//关闭连接
typedef void (*MQTT_PubSuss)(void*, MQTTAsync_successData*);			//发布成功
typedef void (*MQTT_PubFail)(void*, MQTTAsync_failureData*);			//发布失败
typedef void (*MQTT_SubSuss)(void*, MQTTAsync_successData*);			//订阅成功
typedef void (*MQTT_SubFail)(void*, MQTTAsync_failureData*);			//订阅失败
typedef void (*MQTT_DisaSub)(void*, MQTTAsync_successData*);			//关闭订阅

typedef void (*MQTT_ConSuss5)(void*, MQTTAsync_successData5*);			//连接成功
typedef void (*MQTT_ConFail5)(void*, MQTTAsync_failureData5*);			//连接失败
typedef void (*MQTT_DisaCon5)(void*, MQTTAsync_successData5*);			//关闭连接
typedef void (*MQTT_PubSuss5)(void*, MQTTAsync_successData5*);			//发布成功
typedef void (*MQTT_PubFail5)(void*, MQTTAsync_failureData5*);			//发布失败
typedef void (*MQTT_SubSuss5)(void*, MQTTAsync_successData5*);			//订阅成功
typedef void (*MQTT_SubFail5)(void*, MQTTAsync_failureData5*);			//订阅失败
typedef void (*MQTT_DisaSub5)(void*, MQTTAsync_successData5*);			//关闭订阅


struct MQTT_Topic
{
	int qos = 0;
	std::string topic = "";
	MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;			//发布
	MQTTAsync_responseOptions sub_opts = MQTTAsync_responseOptions_initializer;			//开启订阅
	MQTTAsync_responseOptions dis_opts = MQTTAsync_responseOptions_initializer;			//关闭订阅
};

struct MQTT_client
{
	MQTTAsync client = nullptr;
	bool create = false;
	bool connect = false;
	bool subtopic = false;
	std::string username = "admin";
	std::string password = "admin";
	std::string ress = "tcp://";
	std::string id = "";
	MQTTAsync_createOptions crea_opts = MQTTAsync_createOptions_initializer;			//创建
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;			//开启连接
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;	//关闭连接
};

class CMQTT
{
public:
	CMQTT(int version = 0);
	~CMQTT();

	bool CreateClient(std::string user, std::string pass, std::string host, std::string port = "1883", std::string id = "");
	bool ConnectClient(std::string id = "");
	bool DisConClient(std::string id = "");
	bool DeleteClient(std::string id = "");
	std::vector<std::string> listID();

	bool CreateTopic(std::string topic, int qos = 0);
	bool DeleteTopic(std::string topic = "");
	std::vector<std::string> listTopic();

	bool SelectTopic(std::string topic);
	bool SelectClient(std::string ClientID);

	bool PubMessage(std::string message, std::string topic = "", std::string id = "");
	bool ClientSubTopic(std::string id = "", std::string topic = "",int qos = -1);
	bool ClientdisTopic(std::string id = "", std::string topic = "");

protected:
	int Version;
	MQTT_Topic* nowTopic = nullptr;
	MQTT_client* nowClient = nullptr;
	std::vector<MQTT_Topic*> Topics;
	std::vector<MQTT_client*> Clients;
protected:
	static MQTT_LostCon _LostCon(void* context, char* cause);							//丢失连接
	static MQTT_DealSub _DealSub(void* context, char* topicName, int topicLen, MQTTAsync_message* mess);	//订阅信息处理	


	static MQTT_ConSuss _ConSuss(void* context, MQTTAsync_successData* data);			//连接成功
	static MQTT_ConFail _ConFail(void* context, MQTTAsync_failureData* data);			//连接失败
	static MQTT_DisaCon _DisaCon(void* context, MQTTAsync_successData* data);			//关闭连接
	static MQTT_PubSuss _PubSuss(void* context, MQTTAsync_successData* data);			//发布成功
	static MQTT_PubFail _PubFail(void* context, MQTTAsync_failureData* data);			//发布失败
	static MQTT_SubSuss _SubSuss(void* context, MQTTAsync_successData* data);			//订阅成功
	static MQTT_SubFail _SubFail(void* context, MQTTAsync_failureData* data);			//订阅失败
	static MQTT_DisaSub _DisaSub(void* context, MQTTAsync_successData* data);			//关闭订阅

	static MQTT_ConSuss5 _ConSuss5(void* context, MQTTAsync_successData5* data);			//连接成功
	static MQTT_ConFail5 _ConFail5(void* context, MQTTAsync_failureData5* data);			//连接失败
	static MQTT_DisaCon5 _DisaCon5(void* context, MQTTAsync_successData5* data);			//关闭连接
	static MQTT_PubSuss5 _PubSuss5(void* context, MQTTAsync_successData5* data);			//发布成功
	static MQTT_PubFail5 _PubFail5(void* context, MQTTAsync_failureData5* data);			//发布失败
	static MQTT_SubSuss5 _SubSuss5(void* context, MQTTAsync_successData5* data);			//订阅成功
	static MQTT_SubFail5 _SubFail5(void* context, MQTTAsync_failureData5* data);			//订阅失败
	static MQTT_DisaSub5 _DisaSub5(void* context, MQTTAsync_successData5* data);			//关闭订阅
};

