#include "sql_odbc.h"
#include <iostream>

using namespace std;

bool SQL_ODBC::initSQL(const QString o_name, const QString d_name, const QString d_pass)
{
   db=QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
   db.setHostName("localhost");             //选择本地主机，127.0.1.1
   db.setDatabaseName(o_name);              //数据源名称
   db.setUserName(d_name);                  //登录用户
   db.setPassword(d_pass);                  //密码

   sqlDebug=0;

   return isOpen=db.open();
}

void SQL_ODBC::freeSQL()
{
    db.close();
}

void SQL_ODBC::changeDebugMode(int _sqlDebug)
{
    sqlDebug=_sqlDebug;
}

bool SQL_ODBC::beginTran()
{
    errorNum=0;
    return db.transaction();
}

bool SQL_ODBC::commitTran()
{
    if(errorNum>0)
    {
        errorNum=0;
        if(!db.rollback())
        {
            //rollback failed
            if(sqlDebug==1)
            {
                cout<<">>Error!Rollback failed!"<<"<<"<<endl;
            }
        }
        return false;
    }
    else
    {
        if(!db.commit())
        {
            //commit failed

            if(sqlDebug==1)
            {
                cout<<">>Error!Commit failed!"<<"<<"<<endl;
            }
            return false;
        }
        return true;
    }
}

bool SQL_ODBC::sql(const std::string &statement,vector<vector<string>> &result)
{
    QSqlQuery qry(db);
    vector<vector<string>> _result;

    if(!qry.exec(QString::fromStdString(statement)))
    {
        //wrong query statement

        if(sqlDebug==1)
        {
            cout<<">>Error T-SQL:"<<statement<<"<<"<<endl;
        }

        ++errorNum;

        return false;
    }

    if(!qry.first())
    {
        //true query but result is empty
        result=_result;
        return true;
    }

    int col_num=qry.record().count();
    int row=0;

    do
    {
        _result.push_back(vector<string>());
        for(int i=0;i<col_num;++i)
        {
            _result[row].push_back(qry.value(i).toString().toStdString());
        }
        ++row;
    }while(qry.next());

    result=_result;
    return true;
}

bool SQL_ODBC::sql(const string &statement)
{
    QSqlQuery qry(db);

    if(!qry.exec(QString::fromStdString(statement)))
    {
        //wrong query statement

        if(sqlDebug==1)
        {
            cout<<">>Error T-SQL:"<<statement<<"<<"<<endl;
        }

        ++errorNum;

        return false;
    }
    return true;
}
