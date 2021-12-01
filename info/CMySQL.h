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
    std::vector<std::string> fields;//表中字段
};
struct DataBase_info {
    const bool Connect() { return connect; }
    const std::string DataBaseName() { return database_name; }
    std::vector<Table_info> GetTables() { return tables; }
private:
    friend class CMySQL;
    bool connect = false;//是否链接
    MYSQL* mysql = nullptr;//mysql连接 
    std::string database_name = "";//数据库名
    std::vector<Table_info> tables;//库中表的名字
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
    bool connect = false;//是否链接
    MYSQL* mysql = nullptr;//mysql连接 
    std::vector<DataBase_info*> databases;//此主机中所有数据库
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
    std::string m_code = MYSQL_GBK; //默认编码
private:
    Mysql_info mysql_info;//链接的MySQL信息
    DataBase_info* database_info = nullptr; //此时操作的的数据库信息
    std::string m_errorcode = ""; //最近一次的错误码
    MYSQL_RES* m_res = nullptr;//查询结果集  
};