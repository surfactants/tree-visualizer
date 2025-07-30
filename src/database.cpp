#include <database.hpp>

#include <node_data.hpp>

std::map<unsigned short int, Node_Data> Database::getNodes()
{
    sqlite3* db = nullptr;
    sqlite3_open("tree.db", &db);
    sqlite3_stmt* statement;
    std::string sql = "SELECT * FROM 'NODES'";
    std::map<unsigned short int, Node_Data> nodes;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while((rc = sqlite3_step(statement)) == SQLITE_ROW) {
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

    if (child_string.length() > 0) {
        size_t space;
        while((space = child_string.find(' ')) != std::string::npos) {
            int datum = std::stoi(child_string.substr(0, space));
            children.push_back(datum);
            child_string = child_string.substr(space + 1);
        }

        children.push_back(std::stoi(child_string));
    }

    return std::make_pair(id, Node_Data(id, tval, children));
}
