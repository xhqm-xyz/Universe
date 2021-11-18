#pragma once
#include <ctime>
#include <string>
#include <vector>
#include <thread>
#include <windows.h>
#pragma warning(disable : 4996)

#include "./mqtt/include/MQTTAsync.h"
#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3a-static.lib")	//���ʹ��release��
#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3as-static.lib")	//���ʹ��release��

//#include "./mqtt/include/MQTTClient.h"
//#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3c-static.lib")	//���ʹ��release��
//#pragma comment(lib,"./info/mqtt/lib/paho-mqtt3cs-static.lib")//���ʹ��release��

typedef void (*MQTT_LostCon)(void*, char*);								//��ʧ����
typedef void (*MQTT_DealSub)(void*, char*, int, MQTTAsync_message*);	//������Ϣ����
//typedef void (*MQTT_DealSub5)(void*, char*, int, MQTTAsync_message*);	//������Ϣ����

typedef void (*MQTT_ConSuss)(void*, MQTTAsync_successData*);			//���ӳɹ�
typedef void (*MQTT_ConFail)(void*, MQTTAsync_failureData*);			//����ʧ��
typedef void (*MQTT_DisaCon)(void*, MQTTAsync_successData*);			//�ر�����
typedef void (*MQTT_PubSuss)(void*, MQTTAsync_successData*);			//�����ɹ�
typedef void (*MQTT_PubFail)(void*, MQTTAsync_failureData*);			//����ʧ��
typedef void (*MQTT_SubSuss)(void*, MQTTAsync_successData*);			//���ĳɹ�
typedef void (*MQTT_SubFail)(void*, MQTTAsync_failureData*);			//����ʧ��
typedef void (*MQTT_DisaSub)(void*, MQTTAsync_successData*);			//�رն���

typedef void (*MQTT_ConSuss5)(void*, MQTTAsync_successData5*);			//���ӳɹ�
typedef void (*MQTT_ConFail5)(void*, MQTTAsync_failureData5*);			//����ʧ��
typedef void (*MQTT_DisaCon5)(void*, MQTTAsync_successData5*);			//�ر�����
typedef void (*MQTT_PubSuss5)(void*, MQTTAsync_successData5*);			//�����ɹ�
typedef void (*MQTT_PubFail5)(void*, MQTTAsync_failureData5*);			//����ʧ��
typedef void (*MQTT_SubSuss5)(void*, MQTTAsync_successData5*);			//���ĳɹ�
typedef void (*MQTT_SubFail5)(void*, MQTTAsync_failureData5*);			//����ʧ��
typedef void (*MQTT_DisaSub5)(void*, MQTTAsync_successData5*);			//�رն���


struct MQTT_Topic
{
	int qos = 0;
	std::string topic = "";
	MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;			//����
	MQTTAsync_responseOptions sub_opts = MQTTAsync_responseOptions_initializer;			//��������
	MQTTAsync_responseOptions dis_opts = MQTTAsync_responseOptions_initializer;			//�رն���
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
	MQTTAsync_createOptions crea_opts = MQTTAsync_createOptions_initializer;			//����
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;			//��������
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;	//�ر�����
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
	static MQTT_LostCon _LostCon(void* context, char* cause);							//��ʧ����
	static MQTT_DealSub _DealSub(void* context, char* topicName, int topicLen, MQTTAsync_message* mess);	//������Ϣ����	


	static MQTT_ConSuss _ConSuss(void* context, MQTTAsync_successData* data);			//���ӳɹ�
	static MQTT_ConFail _ConFail(void* context, MQTTAsync_failureData* data);			//����ʧ��
	static MQTT_DisaCon _DisaCon(void* context, MQTTAsync_successData* data);			//�ر�����
	static MQTT_PubSuss _PubSuss(void* context, MQTTAsync_successData* data);			//�����ɹ�
	static MQTT_PubFail _PubFail(void* context, MQTTAsync_failureData* data);			//����ʧ��
	static MQTT_SubSuss _SubSuss(void* context, MQTTAsync_successData* data);			//���ĳɹ�
	static MQTT_SubFail _SubFail(void* context, MQTTAsync_failureData* data);			//����ʧ��
	static MQTT_DisaSub _DisaSub(void* context, MQTTAsync_successData* data);			//�رն���

	static MQTT_ConSuss5 _ConSuss5(void* context, MQTTAsync_successData5* data);			//���ӳɹ�
	static MQTT_ConFail5 _ConFail5(void* context, MQTTAsync_failureData5* data);			//����ʧ��
	static MQTT_DisaCon5 _DisaCon5(void* context, MQTTAsync_successData5* data);			//�ر�����
	static MQTT_PubSuss5 _PubSuss5(void* context, MQTTAsync_successData5* data);			//�����ɹ�
	static MQTT_PubFail5 _PubFail5(void* context, MQTTAsync_failureData5* data);			//����ʧ��
	static MQTT_SubSuss5 _SubSuss5(void* context, MQTTAsync_successData5* data);			//���ĳɹ�
	static MQTT_SubFail5 _SubFail5(void* context, MQTTAsync_failureData5* data);			//����ʧ��
	static MQTT_DisaSub5 _DisaSub5(void* context, MQTTAsync_successData5* data);			//�رն���
};

