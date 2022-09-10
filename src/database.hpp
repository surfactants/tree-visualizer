#pragma once

#include <node_data.hpp>
#include <map>

class Database{
public:
    Database();
    ~Database();
    std::map<unsigned short int, Node_Data> getNodes();
};
