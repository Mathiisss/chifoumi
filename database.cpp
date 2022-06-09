#include "database.h"

database::database()
{
    this->mybd=QSqlDatabase::addDatabase(CONNECT_TYPE);
    this->mybd.setDatabaseName(DATABASE_NAME);
}
database::~database()
{

}
bool database::openDataBase()
{
    if(mybd.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*bool database::restoreDataBase()
{
    if(!openDataBase())
    {
        return false;
    }
    if(!CreateVille())
    {
        return false;
    }
    if(!InsertVilles())
    {
        return false;
    }
    return true;
}*/
void database::closeDataBase()
{
    this->mybd.close();
}
/*bool database::CreateVille()
{
    QSqlQuery query;
    if(!query.exec("create table Ville (codepostal varchar(5) primary key, nomVille varchar(30),nbHabitants int(10))"))
        {
            return false;
        }
    return true;
}
bool database::InsertVilles()
{



}*/
