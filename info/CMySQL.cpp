#include "CMySQL.h"

CMySQL::CMySQL()
{
    m_code = MYSQL_GBK;
    mysql_info.mysql = new MYSQL();
    mysql_init(mysql_info.mysql);  //初始化mysql
}

CMySQL::CMySQL(Mysql_info info)
{
    m_code = MYSQL_GBK;
    mysql_info.mysql = new MYSQL();
    mysql_init(mysql_info.mysql);  //初始化mysql
    UpMySQLInfo(info.ip, info.username, info.password, info.port);
}

CMySQL::CMySQL(const std::string ip, const std::string username, const std::string password, int port)
{
    m_code = MYSQL_GBK;
    mysql_info.mysql = new MYSQL();
    mysql_init(mysql_info.mysql);  //初始化mysql
    UpMySQLInfo(ip, username, password, port);
}

CMySQL::~CMySQL()
{
    if (database_info) {
        mysql_free_result(m_res);
        mysql_close(database_info->mysql);
        database_info->connect = false;
        database_info = nullptr;
    }
    if (mysql_info.connect) {
        mysql_close(mysql_info.mysql);
        _close_mysql();
    }
}

void CMySQL::UpMySQLInfo()
{
    UpMySQLInfo(mysql_info);
}

void CMySQL::UpMySQLInfo(const Mysql_info info)
{
    UpMySQLInfo(info.ip, info.username, info.password, info.port);
}

void CMySQL::UpMySQLInfo(const std::string ip, const std::string username, const std::string password, int port)
{
    mysql_info.ip = ip;
    mysql_info.username = username;
    mysql_info.password = password;
    mysql_info.port = port;
    if (mysql_info.connect) {
        mysql_close(mysql_info.mysql);
        _close_mysql();
    }
    if ((mysql_real_connect(mysql_info.mysql, ip.c_str(), username.c_str(), password.c_str(), NULL, port, NULL, 0))) {
        mysql_info.connect = true;//中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
        _open_mysql();
    }else
        m_errorcode = std::string(mysql_error(mysql_info.mysql));
}

void CMySQL::ShowDataBase(std::string dbname, std::string tabbname)
{
    if (!mysql_info.connect)
        return;
    if (dbname == "") {
        auto DBinfo = mysql_info.databases;
        for (auto db : DBinfo)
            printf("库名：%s\n", db->database_name.c_str());
        printf("\n\n");
        return;
    }
    if (tabbname == "") {
        auto DBinfo = mysql_info.databases;
        for (auto db : DBinfo)
            if (db->database_name == dbname) {
                printf("库名：%s\n", dbname.c_str());
                auto TABinfo = db->tables;
                for (auto tab : TABinfo)
                    printf("\t%s\n", tab.table_name.c_str());
            }printf("\n\n");
            return;
    }
    auto DBinfo = mysql_info.databases;
    for (auto db : DBinfo)
        if (db->database_name == dbname) {
            printf("库名：%s\n", dbname.c_str());
            auto TABinfo = db->tables;
            for (auto tab : TABinfo)
                if (tab.table_name == tabbname) {
                    printf("%s\n", tabbname.c_str());
                    auto FIELDino = tab.fields;
                    for (auto field : FIELDino)
                        printf("%s\t", field.c_str());
                }printf("\n\n");
        }
}

bool CMySQL::SelectDataBase(std::string DatabaseName)
{
    if (!mysql_info.connect)
        return false;
    CloseDataBase();
    if (DatabaseName == "")
        return true;
    std::vector<DataBase_info*>::iterator dbit;
    for (dbit = mysql_info.databases.begin(); dbit != mysql_info.databases.end(); dbit++)
        if ((*dbit)->database_name == DatabaseName)
            database_info = (*dbit);
    if (!database_info)
        return false;
    if ((mysql_real_connect(database_info->mysql, //返回false则连接失败，返回true则连接成功
        mysql_info.ip.c_str(),
        mysql_info.username.c_str(),
        mysql_info.password.c_str(),
        database_info->database_name.c_str(), mysql_info.port, NULL, 0)))
        return database_info->connect = true;
    else
        m_errorcode = std::string(mysql_error(database_info->mysql));
    return database_info = nullptr;
}

void CMySQL::CloseDataBase()
{
    if (database_info) {
        mysql_free_result(m_res);
        mysql_close(database_info->mysql);
        database_info->connect = false;
        database_info = nullptr;
    }
}

void CMySQL::_dblist(){
    if (!mysql_info.connect)
        return;
    mysql_info.databases.clear();
    std::string command = "show databases";
    mysql_query(mysql_info.mysql, m_code.c_str());//设置编码
    if (mysql_query(mysql_info.mysql, command.c_str())) {    //执行SQL语句
        m_errorcode = std::string(mysql_error(mysql_info.mysql));
        return;
    }MYSQL_RES* res;//获取结果集  
    if (!(res = mysql_store_result(mysql_info.mysql)))  {
        m_errorcode = std::string(mysql_error(mysql_info.mysql));
        return;
    }long long db_num = mysql_affected_rows(mysql_info.mysql);
    for (long long i = 0; i < db_num; i++) {
        DataBase_info* dbinfo = new DataBase_info;
        dbinfo->database_name = std::string(*mysql_fetch_row(res));
        mysql_info.databases.push_back(dbinfo);
    }
}

void CMySQL::_tablist(){
    if (!mysql_info.connect)
        return;
    for (auto dbit = mysql_info.databases.begin(); dbit != mysql_info.databases.end(); dbit++) {
        (*dbit)->mysql = new MYSQL();
        std::string command = "show tables";
        if (!(mysql_real_connect((*dbit)->mysql, //返回false则连接失败，返回true则连接成功
            mysql_info.ip.c_str(),
            mysql_info.username.c_str(),
            mysql_info.password.c_str(),
            (*dbit)->database_name.c_str(), mysql_info.port, NULL, 0)))
            return;
        mysql_query((*dbit)->mysql, m_code.c_str());//设置编码
        if (mysql_query((*dbit)->mysql, command.c_str())) {    //执行SQL语句
            m_errorcode = std::string(mysql_error((*dbit)->mysql));
            mysql_close((*dbit)->mysql);
            return;
        }MYSQL_RES* res;//获取结果集  
        if (!(res = mysql_store_result((*dbit)->mysql))) {
            m_errorcode = std::string(mysql_error((*dbit)->mysql));
            mysql_close((*dbit)->mysql);
            return;
        }long long tab_num = mysql_affected_rows((*dbit)->mysql);
        for (long long i = 0; i < tab_num; i++) {
            Table_info tabinfo;
            tabinfo.table_name = std::string(*mysql_fetch_row(res));
            if (!_fieldlist((*dbit)->mysql, &tabinfo)) {
                mysql_close((*dbit)->mysql);
                return;
            }(*dbit)->tables.push_back(tabinfo);
        }mysql_close((*dbit)->mysql);
    }
}

bool CMySQL::_fieldlist(MYSQL* mysql, Table_info* tabname){
    if (!mysql||!tabname)
        return false;
    std::string command = "desc " + tabname->table_name;
    if (mysql_query(mysql, command.c_str())) {    //执行SQL语句
        m_errorcode = std::string(mysql_error(mysql));
        return false;
    }MYSQL_RES* res;//获取结果集  
    if (!(res = mysql_store_result(mysql))) {
        m_errorcode = std::string(mysql_error(mysql));
        return false;
    }long long field_num = mysql_affected_rows(mysql);
    for (long long i = 0; i < field_num; i++) {
        std::string fieldname = std::string(*mysql_fetch_row(res));
        tabname->fields.push_back(fieldname);
    }return true;
}

void CMySQL::_open_mysql(){
    _dblist();
    _tablist();
}

void CMySQL::_close_mysql()
{
    std::vector<DataBase_info*>::iterator dbit;
    std::vector<Table_info>::iterator tabit;
    for (dbit = mysql_info.databases.begin(); dbit != mysql_info.databases.end(); dbit++) {
        for (tabit = (*dbit)->tables.begin(); tabit != (*dbit)->tables.end(); tabit++)
            tabit->fields.clear();
        (*dbit)->tables.clear();
        if((*dbit)->connect)
            mysql_close((*dbit)->mysql);
        delete (*dbit)->mysql;
        (*dbit)->mysql = nullptr;
    }mysql_info.databases.clear();
}

bool CMySQL::MySQLCommand(std::string command)
{
    if(!database_info || database_info->connect == false)
        return false;
    mysql_query(database_info->mysql, m_code.c_str());
    if (mysql_query(database_info->mysql, command.c_str())) {//执行SQL语句
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    if (!(m_res = mysql_store_result(database_info->mysql))) {//获得sql语句结束后返回的结果集  
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    return true;
}

bool CMySQL::Insert(std::string tabname, std::string data)
{
    std::string command = "insert into " + tabname + " values " + data + ";";
    if (!database_info || database_info->connect == false)
        return false;
    mysql_query(database_info->mysql, m_code.c_str());
    if (mysql_query(database_info->mysql, command.c_str())) {//执行SQL语句
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    if (!(m_res = mysql_store_result(database_info->mysql))) {//获得sql语句结束后返回的结果集  
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    return true;
}

bool CMySQL::Delete(std::string tabname, std::string conditions)
{
    std::string command = "delete from " + tabname + " " + conditions + ";";
    if (!database_info || database_info->connect == false)
        return false;
    mysql_query(database_info->mysql, m_code.c_str());
    if (mysql_query(database_info->mysql, command.c_str())) {//执行SQL语句
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    if (!(m_res = mysql_store_result(database_info->mysql))) {//获得sql语句结束后返回的结果集  
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    return true;
}

bool CMySQL::Updata(std::string tabname, std::string key, std::string val, std::string conditions)
{
    std::string command = "update " + tabname + " set " + key + " = " + val + " " + conditions + ";";
    if (!database_info || database_info->connect == false)
        return false;
    mysql_query(database_info->mysql, m_code.c_str());
    if (mysql_query(database_info->mysql, command.c_str())) {//执行SQL语句
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    if (!(m_res = mysql_store_result(database_info->mysql))) {//获得sql语句结束后返回的结果集  
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    return true;
}

bool CMySQL::Select(std::string tabname, std::string key, std::vector<std::map<std::string, std::string>>*res, std::string conditions)
{
    std::string command = "select " + key + " from " + tabname + " " + conditions + ";";
    if (!res || !database_info || database_info->connect == false)
        return false;
    mysql_query(database_info->mysql, m_code.c_str());
    if (mysql_query(database_info->mysql, command.c_str())) {//执行SQL语句
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    if (!(m_res = mysql_store_result(database_info->mysql))) {//获得sql语句结束后返回的结果集  
        m_errorcode = std::string(mysql_error(database_info->mysql));
        return false;
    }
    res->clear();
    long long name_num = 1;
    for (int i = 0; i < key.length(); i++)
        if (key[i] == ',')
            name_num++;

    long long data_num = mysql_affected_rows(database_info->mysql);
    auto dataname = mysql_fetch_field(m_res);
    auto tabit = database_info->tables.begin();
    for (long long i = 0; i < data_num; i++) {
        auto datastr = mysql_fetch_row(m_res);
        std::map<std::string, std::string> key_val;
        for (int j = 0; j < name_num; j++)
            key_val[dataname[j].name] = std::string(datastr[j]);
        res->push_back(key_val);
    }return true;
}