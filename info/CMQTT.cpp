#include "CMQTT.h"


CMQTT::CMQTT(int version)
{
	Version = version;
}

CMQTT::~CMQTT()
{
	DeleteClient();
}

bool CMQTT::CreateClient(std::string user, std::string pass, std::string host, std::string port, std::string id)
{
	for (auto& Client : Clients)
		if (Client->id == id)
			return false;
	MQTT_client* client = new MQTT_client();
	Clients.push_back(client);
	client->username = user;
	client->password = pass;
	client->ress = "tcp://" + host + ":" + port;
	client->id = (id == "" ? std::to_string(time(NULL)) : id);
	client->crea_opts.sendWhileDisconnected = 0;
	client->crea_opts.maxBufferedMessages = 10;

	client->conn_opts.MQTTVersion = Version;
	client->conn_opts.cleansession = 1;
	client->conn_opts.connectTimeout = 3;
	client->conn_opts.keepAliveInterval = 60;
	client->conn_opts.automaticReconnect = 1;
	client->conn_opts.context = client;
	client->conn_opts.username = user.c_str();
	client->conn_opts.password = pass.c_str();
	client->disc_opts.context = client;
	if (Version < 5) {
		client->conn_opts.onSuccess = (MQTTAsync_onSuccess*)_ConSuss;
		client->conn_opts.onFailure = (MQTTAsync_onFailure*)_ConFail;
		client->disc_opts.onSuccess = (MQTTAsync_onSuccess*)_DisaCon;
	}else {
		client->conn_opts.onSuccess5 = (MQTTAsync_onSuccess5*)_ConSuss5;
		client->conn_opts.onFailure5 = (MQTTAsync_onFailure5*)_ConFail5;
		client->disc_opts.onSuccess5 = (MQTTAsync_onSuccess5*)_DisaCon5;
	}
	if (MQTTASYNC_SUCCESS == MQTTAsync_createWithOptions(&client->client, client->ress.c_str(), client->id.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL, &client->crea_opts)) {
		MQTTAsync_setCallbacks(client->client, client, (MQTTAsync_connectionLost*)_LostCon, (MQTTAsync_messageArrived*)_DealSub, NULL);
		//MQTTAsync_setConnectionLostCallback(client->client, client, (MQTTAsync_connectionLost*)_LostCon);
		return client->create = true;
	}return false;
}

bool CMQTT::ConnectClient(std::string id)
{
	if (id == "") {
		//if()
		for (auto &client : Clients) {
			if (client->create && !client->connect) {
				if (MQTTAsync_connect(client->client, &client->conn_opts) != MQTTASYNC_SUCCESS)
					return client->connect;
				while (!client->connect)
					Sleep(1);
			}
		}return true;
	}
	for (auto &client : Clients)
		if(client->id == id)
			if (client->create && !client->connect)
				if (MQTTAsync_connect(client->client, &client->conn_opts) == MQTTASYNC_SUCCESS) {
					while (!client->connect)
						Sleep(1);
					return true;
				}
	return false;
}

bool CMQTT::DisConClient(std::string id)
{
	if (id == "") {
		for (auto& client : Clients) {
			if (client->connect) {
				if (MQTTAsync_disconnect(client->client, &client->disc_opts) != MQTTASYNC_SUCCESS)
					return false;
				while (client->connect)
					Sleep(1);
			}
		}return true;
	}
	for (auto& client : Clients)
		if (client->id == id) {
			if (client->connect) {
				if (MQTTAsync_disconnect(client->client, &client->disc_opts) != MQTTASYNC_SUCCESS)
					return false;
				while (client->connect)
					Sleep(1);
			}break;
		}
	return true;
}

bool CMQTT::DeleteClient(std::string id)
{
	if (id == "") {
		for (auto &client : Clients) {
			if (client->connect) {
				if (MQTTAsync_disconnect(client->client, &client->disc_opts) != MQTTASYNC_SUCCESS)
					return false;
				while (client->connect)
					Sleep(1);
			}
			if(client->create)
				MQTTAsync_destroy(&client->client);
			delete client;
		}Clients.clear();
		return true;
	}
	for (auto clientIt = Clients.begin(); clientIt != Clients.end(); clientIt++) {
		if ((*clientIt)->id == id) {
			if ((*clientIt)->connect) {
				if (MQTTAsync_disconnect((*clientIt)->client, &(*clientIt)->disc_opts) != MQTTASYNC_SUCCESS)
					return false;
				while ((*clientIt)->connect)
					Sleep(1);
			}
			if ((*clientIt)->create)
				MQTTAsync_destroy(&(*clientIt)->client);
			delete (*clientIt);
			Clients.erase(clientIt);
			break;
		}
	}return true;
}

std::vector<std::string> CMQTT::listID()
{
	std::vector<std::string> list;
	for (auto &client : Clients) {
		printf("id:%s\thost:%s\tisConnect:%d\n", client->id.c_str(), client->ress.c_str(), client->connect);
		list.push_back(client->id);
	}return list;
}

bool CMQTT::CreateTopic(std::string topic, int qos)
{
	for (auto &Topic : Topics)
		if (Topic->topic == topic)
			return false;
	MQTT_Topic* Topic = new MQTT_Topic();
	Topic->qos = qos;
	Topic->topic = topic;
	if (Version < 5) {
		Topic->pub_opts.onSuccess = (MQTTAsync_onSuccess*)_PubSuss;
		Topic->pub_opts.onFailure = (MQTTAsync_onFailure*)_PubFail;
		Topic->sub_opts.onSuccess = (MQTTAsync_onSuccess*)_SubSuss;
		Topic->sub_opts.onFailure = (MQTTAsync_onFailure*)_SubFail;
		Topic->dis_opts.onSuccess = (MQTTAsync_onSuccess*)_DisaSub;
	}else {
		Topic->pub_opts.onSuccess5 = (MQTTAsync_onSuccess5*)_PubSuss5;
		Topic->pub_opts.onFailure5 = (MQTTAsync_onFailure5*)_PubFail5;
		Topic->sub_opts.onSuccess5 = (MQTTAsync_onSuccess5*)_SubSuss5;
		Topic->sub_opts.onFailure5 = (MQTTAsync_onFailure5*)_SubFail5;
		Topic->dis_opts.onSuccess5 = (MQTTAsync_onSuccess5*)_DisaSub5;
	}Topics.push_back(Topic);
	return true;
}

bool CMQTT::DeleteTopic(std::string topic)
{
	if (topic == "") {
		for (auto Topic = Topics.begin(); Topic != Topics.end(); Topic++){
			delete (*Topic);
			Topics.erase(Topic);
		}return true;
	}
	for (auto Topic = Topics.begin(); Topic != Topics.end(); Topic++)
		if ((*Topic)->topic == topic) {
			delete (*Topic);
			Topics.erase(Topic);
			return true;
		}
	return false;
}

std::vector<std::string> CMQTT::listTopic()
{
	std::vector<std::string> list;
	for (auto &Topic : Topics) {
		printf("Topic:%s\tqos:%d\n", Topic->topic.c_str(), Topic->qos);
		list.push_back(Topic->topic);
	}return list;
}

bool CMQTT::SelectTopic(std::string topic)
{
	for (auto &Topic : Topics) {
		if (Topic->topic == topic) {
			nowTopic = Topic;
			return true;
		}
	}return false;
}

bool CMQTT::SelectClient(std::string ClientID)
{
	for (auto &Client : Clients) {
		if (Client->id == ClientID) {
			nowClient = Client;
			return true;
		}
	}return false;
}

bool CMQTT::PubMessage(std::string message, std::string topic, std::string id)
{
	MQTT_Topic* Topic = nullptr;
	MQTT_client* Client = nullptr;
	if (topic != "")
		for (auto& Top : Topics)
			if (Top->topic == topic)
				Topic = Top;
	if(topic == "" || Topic == nullptr)
		Topic = nowTopic;

	if (id != "")
		for (auto& Cli : Clients)
			if (Cli->id == id)
				Client = Cli;
	if (id == "" || Client == nullptr)
		Client = nowClient;

	if(!Topic || !Client)
		return false;

	Topic->pub_opts.context = Client;
	int rc = 0;
	if ((rc = MQTTAsync_send(Client->client, Topic->topic.c_str(), message.length(), message.c_str(), Topic->qos, 0, &Topic->pub_opts)) != MQTTASYNC_SUCCESS)
		return false;
	return true;
}

bool CMQTT::ClientSubTopic(std::string id, std::string topic, int qos)
{
	MQTT_Topic* Topic = nullptr;
	MQTT_client* Client = nullptr;
	if (topic != "")
		for (auto& Top : Topics)
			if (Top->topic == topic)
				Topic = Top;
	if (topic == "" || Topic == nullptr)
		Topic = nowTopic;

	if (id != "")
		for (auto& Cli : Clients)
			if (Cli->id == id)
				Client = Cli;
	if (id == "" || Client == nullptr)
		Client = nowClient;

	if (!Topic || !Client)
		return false;
	if (qos == -1)
		qos = Topic->qos;

	Topic->dis_opts.context = Client;
	Topic->sub_opts.context = Client;

	if (Client->subtopic)
		if (MQTTAsync_unsubscribe(Client->client, Topic->topic.c_str(), &Topic->dis_opts) != MQTTASYNC_SUCCESS)
			return false;
	while (Client->subtopic)
		Sleep(1);

	if (MQTTAsync_subscribe(Client->client, Topic->topic.c_str(), qos, &Topic->sub_opts) != MQTTASYNC_SUCCESS)
		return false;

	while (!Client->subtopic)
		Sleep(1);
	return true;
}

bool CMQTT::ClientdisTopic(std::string id, std::string topic)
{
	MQTT_Topic* Topic = nullptr;
	MQTT_client* Client = nullptr;
	if (topic != "")
		for (auto& Top : Topics)
			if (Top->topic == topic)
				Topic = Top;
	if (topic == "" || Topic == nullptr)
		Topic = nowTopic;

	if (id != "")
		for (auto& Cli : Clients)
			if (Cli->id == id)
				Client = Cli;
	if (id == "" || Client == nullptr)
		Client = nowClient;

	if (!Topic || !Client)
		return false;

	Topic->dis_opts.context = Client;
	Topic->sub_opts.context = Client;

	if (Client->subtopic)
		if (MQTTAsync_unsubscribe(Client->client, Topic->topic.c_str(), &Topic->dis_opts) != MQTTASYNC_SUCCESS)
			return false;
	while (Client->subtopic)
		Sleep(1);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

MQTT_LostCon CMQTT::_LostCon(void* context, char* cause)
{
	auto con = ((MQTT_client*)context);
	con->connect = false;
	printf("Client %s Connect Lost\n", con->id.c_str());
	return MQTT_LostCon();
}

MQTT_DealSub CMQTT::_DealSub(void* context, char* topicName, int topicLen, MQTTAsync_message* mess)
{
	auto con = ((MQTT_client*)context);
	printf("Client %s Sub Message: \"%s\" Sucessful from: \"%s\"\n", con->id.c_str(), (char*)mess->payload, topicName);
	MQTTAsync_freeMessage(&mess);
	MQTTAsync_free(topicName);
	return MQTT_DealSub();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MQTT_ConSuss CMQTT::_ConSuss(void* context, MQTTAsync_successData* data)
{
	auto con = ((MQTT_client*)context);
	con->connect = true;
	printf("Client %s Connect Sucessful, Host: %s, Version: %d\n", con->id.c_str(), data->alt.connect.serverURI, data->alt.connect.MQTTVersion);
	return MQTT_ConSuss();
}

MQTT_ConFail CMQTT::_ConFail(void* context, MQTTAsync_failureData* data)
{
	auto con = ((MQTT_client*)context);
	con->connect = false;
	printf("Client %s Connect Failed, error code: %d\n", con->id.c_str(), data->code);
	return MQTT_ConFail();
}

MQTT_DisaCon CMQTT::_DisaCon(void* context, MQTTAsync_successData* data)
{
	auto con = ((MQTT_client*)context);
	con->connect = false;
	printf("Client %s Connect Disable\n",con->id.c_str());
	return MQTT_DisaCon();
}

MQTT_PubSuss CMQTT::_PubSuss(void* context, MQTTAsync_successData* data)
{
	auto con = ((MQTT_client*)context);
	printf("Client %s Pub Message: \"%s\" Sucessful\n", con->id.c_str(), (char*)data->alt.pub.message.payload);
	return MQTT_PubSuss();
}

MQTT_PubFail CMQTT::_PubFail(void* context, MQTTAsync_failureData* data)
{
	auto con = ((MQTT_client*)context);
	printf("Client %s Pub Failed\n", con->id.c_str());
	return MQTT_PubFail();
}

MQTT_SubSuss CMQTT::_SubSuss(void* context, MQTTAsync_successData* data)
{
	auto con = ((MQTT_client*)context);
	con->subtopic = true;
	printf("Client %s Sub Sucessful\n", con->id.c_str());
	return MQTT_SubSuss();
}

MQTT_SubFail CMQTT::_SubFail(void* context, MQTTAsync_failureData* data)
{
	auto con = ((MQTT_client*)context);
	con->subtopic = false;
	printf("Client %s Sub Failed\n", con->id.c_str());
	return MQTT_SubFail();
}

MQTT_DisaSub CMQTT::_DisaSub(void* context, MQTTAsync_successData* data)
{
	auto con = ((MQTT_client*)context);
	con->subtopic = false;
	printf("Client %s Disable Sub Sucessful\n", con->id.c_str());
	return MQTT_DisaSub();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

MQTT_ConSuss5 CMQTT::_ConSuss5(void* context, MQTTAsync_successData5* data)
{
	auto con = ((MQTT_client*)context);
	con->connect = true;
	printf("Client %s Connect Sucessful, Host: %s, Version: %d\n", con->id.c_str(), data->alt.connect.serverURI, data->alt.connect.MQTTVersion);
	return MQTT_ConSuss5();
}

MQTT_ConFail5 CMQTT::_ConFail5(void* context, MQTTAsync_failureData5* data)
{
	auto con = ((MQTT_client*)context);
	con->connect = false;
	printf("Client %s Connect Failed, error code: %d\n", con->id.c_str(), data->code);
	return MQTT_ConFail5();
}

MQTT_DisaCon5 CMQTT::_DisaCon5(void* context, MQTTAsync_successData5* data)
{
	auto con = ((MQTT_client*)context);
	con->connect = false;
	printf("Client %s Connect Disable\n", con->id.c_str());
	return MQTT_DisaCon5();
}

MQTT_PubSuss5 CMQTT::_PubSuss5(void* context, MQTTAsync_successData5* data)
{
	auto con = ((MQTT_client*)context);
	printf("Client %s Pub Message: \"%s\" Sucessful\n", con->id.c_str(), (char*)data->alt.pub.message.payload);
	return MQTT_PubSuss5();
}

MQTT_PubFail5 CMQTT::_PubFail5(void* context, MQTTAsync_failureData5* data)
{
	auto con = ((MQTT_client*)context);
	printf("Client %s Pub Failed\n", con->id.c_str());
	return MQTT_PubFail5();
}

MQTT_SubSuss5 CMQTT::_SubSuss5(void* context, MQTTAsync_successData5* data)
{
	auto con = ((MQTT_client*)context);
	con->subtopic = true;
	printf("Client %s Sub Sucessful\n", con->id.c_str());
	return MQTT_SubSuss5();
}

MQTT_SubFail5 CMQTT::_SubFail5(void* context, MQTTAsync_failureData5* data)
{
	auto con = ((MQTT_client*)context);
	con->subtopic = false;
	printf("Client %s Sub Failed\n", con->id.c_str());
	return MQTT_SubFail5();
}

MQTT_DisaSub5 CMQTT::_DisaSub5(void* context, MQTTAsync_successData5* data)
{
	auto con = ((MQTT_client*)context);
	con->subtopic = false;
	printf("Client %s Disable Sub Sucessful\n", con->id.c_str());
	return MQTT_DisaSub5();
}