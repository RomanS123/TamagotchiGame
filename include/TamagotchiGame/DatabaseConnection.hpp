#include <pqxx/pqxx>

class DatabaseConnection {
 public:
  pqxx::connection* conn;
  void SetConnection();

  void Disconnect();

  pqxx::result Query(std::string query);
};
