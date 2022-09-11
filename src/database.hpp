#pragma once

#include <node_data.hpp>
#include <map>
#include <sqlite/sqlite3.h>

class Database{
public:
    std::map<unsigned short int, Node_Data> getNodes();

private:
    std::pair<unsigned short int, Node_Data> readNode(sqlite3_stmt* statement);
};
