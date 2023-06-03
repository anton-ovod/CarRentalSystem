#include "databasehandler.h"


DatabaseHandler& DatabaseHandler::getInstance()
{
    static DatabaseHandler instance;
    return instance;
}

QSqlDatabase& DatabaseHandler::getDatabase()
{
    return db;
}

DatabaseHandler::~DatabaseHandler()
{
    if (db.isOpen()) {
        db.close();
    }
}

DatabaseHandler::DatabaseHandler()
{
    isInitialized = false;
}

bool DatabaseHandler::initializeDatabase()
{
    if (isInitialized)
        return true;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("CarRentalSystem.db");

    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createUsersTabel = "CREATE TABLE IF NOT EXISTS USERS ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "UserName TEXT,"
                               "Password TEXT,"
                               "Email TEXT,"
                               "PhoneNumber TEXT,"
                               "OrderNumber TEXT DEFAULT 'No Orders'"
                               ")";
    if(!query.exec(createUsersTabel))
    {
        qDebug() << "Error creating <Users> table : "<< query.lastError().text();
    }
    db.close();

    isInitialized = true;
    return true;
}
