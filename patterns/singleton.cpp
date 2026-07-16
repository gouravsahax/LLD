#include <bits/stdc++.h>

using namespace std;

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    static mutex mtx;

    DatabaseConnection() {
        cout << "Database Connection Created..." << endl;
    }

    ~DatabaseConnection() {
        cout << "Database Connection Destroyed..." << endl;
    }

public:
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    static DatabaseConnection* getInstance() {
        lock_guard<mutex> lock(mtx);   // Thread-safe

        if (!instance) {
            instance = new DatabaseConnection();
        }
        return instance;
    }

    static void destroyInstance() {   // Free memory
        delete instance;
        instance = nullptr;
    }

    void query(const string& sql) {
        cout << "Executing: " << sql << endl;
    }
};

DatabaseConnection* DatabaseConnection::instance = nullptr;
mutex DatabaseConnection::mtx;

int main() {
    DatabaseConnection* db1 = DatabaseConnection::getInstance();
    DatabaseConnection* db2 = DatabaseConnection::getInstance();

    db1->query("SELECT * FROM users");

    cout << (db1 == db2) << endl; // 1

    DatabaseConnection::destroyInstance(); // Prevent memory leak

    return 0;
}