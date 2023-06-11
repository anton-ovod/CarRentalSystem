#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

class DatabaseHandler {
public:
    static DatabaseHandler& getInstance();

    bool initializeDatabase();

    QSqlDatabase& getDatabase();

private:
    QSqlDatabase db;
    bool isInitialized;

    DatabaseHandler();

    ~DatabaseHandler();


    DatabaseHandler(const DatabaseHandler&) = delete;
    DatabaseHandler& operator=(const DatabaseHandler&) = delete;
};
#endif // DATABASEHANDLER_H
