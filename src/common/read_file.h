#ifndef READ_FILE
#define READ_FILE

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

//[[nodiscard]]
std::string readShaderFile(const char* filePath) 
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    if (file) {
        buffer << file.rdbuf();
        file.close();
    } else {
        std::cerr << "Failed to load shader: " << filePath << std::endl;
    }
    return buffer.str();
}



#endif