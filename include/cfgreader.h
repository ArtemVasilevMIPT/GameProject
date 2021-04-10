#pragma once
#include <fstream>
#include <unordered_map>

class cfgReader
{
private:
    std::unordered_map<std::string, std::string> fields;
public:
    explicit cfgReader(const std::string& path);
    const std::string& getVal(const std::string& name);
};