#include <database.hpp>
#include <node_data.hpp>

std::map<unsigned short int, Node_Data> Database::getNodes(){
    sqlite3* db = nullptr;
    sqlite3_open("tree.db", &db);

    std::map<unsigned short int, Node_Data> nodes;

    sqlite3_stmt* statement;

    std::string sql = "SELECT * FROM 'NODES'";

    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while((rc = sqlite3_step(statement)) == SQLITE_ROW){
        nodes.insert(readNode(statement));
    }

    sqlite3_finalize(statement);

    sqlite3_close(db);

    return nodes;
}

std::pair<unsigned short int, Node_Data> Database::readNode(sqlite3_stmt* statement)
{
    int column = 0;

    //id
    //data
    //children

    unsigned short int id = sqlite3_column_int(statement, column++);
    std::string tval = reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
    std::string child_string = reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
    std::vector<unsigned short int> children;

    if(child_string.length() > 0){
        while(child_string.find(' ') != std::string::npos){
            children.push_back(std::stoi(child_string.substr(0, child_string.find(' '))));
            child_string = child_string.substr(child_string.find(' ') + 1);
        }

        children.push_back(std::stoi(child_string));
    }

    return std::make_pair(id, Node_Data(id, tval, children));
}
