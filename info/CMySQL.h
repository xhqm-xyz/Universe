#pragma once
#include <map>
#include <vector>
#include <string>
#include "./mysql/include/mysql.h"
#pragma comment(lib,"./info/mysql/lib/libmysql.lib")
#define MYSQL_LAT "set names lat"
#define MYSQL_GBK "set names gbk"
#define MYSQL_UTF "set names utf8"

class CMySQL;

struct Table_info {
    const std::string TableName() { return table_name; }
    const std::vector<std::string> GetFields() { return fields; }
private:
    friend class CMySQL;
    std::string table_name = "";
    std::vector<std::string> fields;//�����ֶ�
};
struct DataBase_info {
    const bool Connect() { return connect; }
    const std::string DataBaseName() { return database_name; }
    std::vector<Table_info> GetTables() { return tables; }
private:
    friend class CMySQL;
    bool connect = false;//�Ƿ�����
    MYSQL* mysql = nullptr;//mysql���� 
    std::string database_name = "";//���ݿ���
    std::vector<Table_info> tables;//���б������
};
struct Mysql_info {
    int port = 3306;
    std::string ip = "127.0.0.1";
    std::string username = "admin";
    std::string password = "admin";
    const bool Connect() { return connect; }
    std::vector<DataBase_info*> GetDataBases() { return databases; }
private:
    friend class CMySQL;
    bool connect = false;//�Ƿ�����
    MYSQL* mysql = nullptr;//mysql���� 
    std::vector<DataBase_info*> databases;//���������������ݿ�
};

class CMySQL{
public:
	CMySQL();
    CMySQL(Mysql_info info);
    CMySQL(const std::string ip, const std::string username, const std::string password, int port = 3306);
    ~CMySQL();

    void UpMySQLInfo();
    void UpMySQLInfo(const Mysql_info info);
    void UpMySQLInfo(const std::string ip, const std::string username, const std::string password, int port = 3306);
    void ShowDataBase(std::string dbname = "", std::string tabbname = "");
    Mysql_info GetMySQLInfo() { return mysql_info; };
    DataBase_info* GetNowDataBase() { return database_info; };
    std::string MySQLCommandError() { return m_errorcode; }
    MYSQL_RES* MySQLCommandRes() { return m_res; };
    bool MySQLCommand(std::string command);

    bool Insert(std::string tabname, std::string data);
    bool Delete(std::string tabname, std::string conditions = "");
    bool Updata(std::string tabname, std::string key, std::string val, std::string conditions = "");
    bool Select(std::string tabname, std::string key = "*", std::vector<std::map<std::string, std::string>>*res = NULL, std::string conditions = "");
    bool SelectDataBase(std::string DatabaseName = "");
private:
    void CloseDataBase();
    void _close_mysql();
    void _open_mysql();
    bool _fieldlist(MYSQL* mysql, Table_info* tabname);
    void _tablist();
    void _dblist();
public:
    std::string m_code = MYSQL_GBK; //Ĭ�ϱ���
private:
    Mysql_info mysql_info;//���ӵ�MySQL��Ϣ
    DataBase_info* database_info = nullptr; //��ʱ�����ĵ����ݿ���Ϣ
    std::string m_errorcode = ""; //���һ�εĴ�����
    MYSQL_RES* m_res = nullptr;//��ѯ�����  
};