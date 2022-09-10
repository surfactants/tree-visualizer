#pragma once

#include <string>
#include <vector>

struct Node_Data{
    Node_Data(unsigned short int nid, std::string ntval, std::vector<unsigned short int> nchildren)
    : id{ nid }, tval{ ntval }, children{ nchildren }{}
    unsigned short int id;
    std::string tval;
    std::vector<unsigned short int> children;
};
