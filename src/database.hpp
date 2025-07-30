#pragma once

#include <sqlite/sqlite3.h>

#include <node_data.hpp>

#include <map>

class Database {
public:
    Database() = default;

    std::map<unsigned short int, Node_Data> getNodes();

private:
    std::pair<unsigned short int, Node_Data> readNode(sqlite3_stmt* statement);
};
