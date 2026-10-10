#ifndef SHADER_COMPILER_ERROR__
#define SHADER_COMPILER_ERROR__

#include <exception>
#include <string>

class shader_compile_error: public std::exception{
    std::string log;
public:
    explicit shader_compile_error(const char * errorLog): log(errorLog){
        
    }
    
    virtual const char* what() const noexcept override{
        return log.c_str();
    }
};

#endif