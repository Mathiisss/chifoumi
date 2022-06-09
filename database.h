#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>

#define DATABASE_NAME "Max_bd"
#define CONNECT_TYPE "QODBC"

class database
{
public:
    database();
    ~database();
    bool openDataBase();
    //bool restoreDataBase();
    void closeDataBase();
private:
    QSqlDatabase mybd;
    //bool CreateVille();
    //bool InsertVilles();

};

#endif // DATABASE_H
