#include "cfgreader.h"

cfgReader::cfgReader(const std::string &path)
{
    std::ifstream inp(path);
    std::string line;
    while(inp >> line)
    {
        int ind = line.find(":");
    std::string name = line.substr(0, ind);
    std::string val = line.substr(ind + 1,
                                  line.size() - ind - 1);
    fields[name] = val;
    }
}

const std::string & cfgReader::getVal(const std::string &name)
{
    return fields[name];
}