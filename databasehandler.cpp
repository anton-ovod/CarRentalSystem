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

    QString AdminQuery = "INSERT INTO USERS (UserName, Password, Email, PhoneNumber, OrderNumber) "
                         "SELECT :username, :password "
                         "WHERE NOT EXISTS (SELECT 1 FROM USERS WHERE UserName = :username)";

    query.bindValue(":username", "admin");
    query.bindValue(":password", "admin");

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            qDebug() << "Admin succssefully added";
        } else {
            qDebug() << "Error with inserting admin account";
        }
    } else {
        qDebug() << "Something went wrong";
    }

    QString createCarsTabel = "CREATE TABLE IF NOT EXISTS CARS ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "CarName TEXT,"
                               "CarModel TEXT,"
                               "CarCapacity TEXT,"
                               "CarColour TEXT,"
                               "CarOwner TEXT,"
                               "CarPrice TEXT,"
                               "CarHolder TEXT DEFAULT 'Ready for rent'"
                               ")";
    if(!query.exec(createCarsTabel))
    {
        qDebug() << "Error creating <CARS> table:" << query.lastError().text();
    }
    db.close();

    isInitialized = true;
    return true;
}
