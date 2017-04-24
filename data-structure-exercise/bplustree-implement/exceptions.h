#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include "common.h"

class LeafNotFoundException: public std::exception {
public:
    explicit LeafNotFoundException(KeyType);
    const char* what() const noexcept override;
private:
    KeyType fkey;
};

class NodeNotFoundException: public std::exception {
public:
    explicit NodeNotFoundException(std::string, std::string);
    const char* what() const noexcept override;
private:
    std::string fsearch_node;
    std::string fcontaining_node;
};

class RecordNotFoundException: public std::exception {
public:
    explicit RecordNotFoundException(KeyType);
    const char* what() const noexcept override;
private:
    KeyType fkey;
};

#endif
