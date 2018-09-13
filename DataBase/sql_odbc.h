#ifndef SQL_ODBC_H
#define SQL_ODBC_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <string>
#include <vector>

class SQL_ODBC
{
private:
    QSqlDatabase db;

    bool isOpen;

    int sqlDebug;

    int errorNum;
public:

    bool initSQL(const QString o_name, const QString d_name, const QString d_pass);

    void freeSQL();

    void changeDebugMode(int _sqlDebug);

    bool beginTran(void);

    bool commitTran(void);

    bool sql(const std::string &statement,std::vector<std::vector<std::string>> &result);

    bool sql(const std::string &statement);
};

#endif // SQL_ODBC_H
