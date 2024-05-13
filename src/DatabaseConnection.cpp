#include <pqxx/pqxx>
#include <TamagotchiGame/DatabaseConnection.hpp>

void DatabaseConnection::SetConnection() {
	conn=new pqxx::connection(
            "username=postgres"
            "host=127.0.0.1"
            "password=abc"
            "dbname=tamagotchi_db"
			"port=5432"
			);
}


void DatabaseConnection::Disconnect() {
	conn->close();
}

pqxx::result DatabaseConnection::Query(std::string strSQL){
        //SetConnection();
        pqxx::work trans(*conn,"trans");

        pqxx::result res=trans.exec(strSQL);

        trans.commit();
        return res;
}
