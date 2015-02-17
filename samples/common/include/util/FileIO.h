#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace coment
{
    std::string readFile(const char* filename)
    {
        std::ostringstream buf;
        std::ifstream in(filename);

        if (!in)
            throw std::runtime_error("Failed to open file");

        buf << in.rdbuf();

        return buf.str();
    }
}