#include <pqxx/pqxx>
#include <TamagotchiGame/DatabaseConnection.hpp>
#include <string>
#include <iostream>

void DatabaseConnection::SetConnection() {
	std::string db_host = "postgres";
	std::string db_user = "admin";
	std::string db_password = "abc";
	std::string db_name = "tamagotchi_db";
	std::string port = "5432";

	/*std::string host = "localhost";
        int port = 5432;
        std::string database = "postgres";
        std::string user = "postgres";
        std::string password = "abc";
	*/
        conn = new pqxx::connection("dbname=" + db_name + " user=" + db_user +
                              " password=" + db_password + " port="+ port +" host=" + db_host);
}


void DatabaseConnection::Disconnect() {
	//conn->close();
}

pqxx::result DatabaseConnection::Query(std::string strSQL){
        //SetConnection();
        pqxx::work trans(*conn,"trans");

        pqxx::result res=trans.exec(strSQL);

        trans.commit();
        return res;
}
