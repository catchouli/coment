#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <initializer_list>

namespace coment
{
    inline std::unique_ptr<char[]> readFile(const char* filename)
    {
        std::ostringstream buf;
        std::ifstream in(filename);

        if (!in)
            throw std::runtime_error("Failed to open file");

        buf << in.rdbuf();

        // Output buffer
        std::unique_ptr<char[]> out_buf;
        out_buf.reset(new char[buf.str().length() + 10]); // Allocate length + extra space for \n and NULL
        memcpy(out_buf.get(), buf.str().c_str(), buf.str().length());
        out_buf.get()[buf.str().length()] = '\n';
        out_buf.get()[buf.str().length()+1] = 0;

        return out_buf;
    }

    inline std::vector<std::unique_ptr<char[]>> readFiles(std::initializer_list<const char*> files)
    {
        std::vector<std::unique_ptr<char[]>> fileContents;

        for (const auto& filename : files)
        {
            fileContents.push_back(readFile(filename));
        }

        return fileContents;
    }

    inline std::unique_ptr<char*[]> glStrings(std::vector<std::unique_ptr<char[]>>& strings)
    {
        std::unique_ptr<char*[]> ptrs;

        ptrs.reset(new char*[strings.size()]);

        int i = 0;
        for (auto& str : strings)
        {
            ptrs.get()[i] = str.get();
            i++;
        }

        return ptrs;
    }
}