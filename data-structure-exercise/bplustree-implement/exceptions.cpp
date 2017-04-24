#include <sstream>
#include <string>
#include "exceptions.h"
#include "node.h"

LeafNotFoundException::LeafNotFoundException(KeyType akey):
    fkey(akey)
{
}

const char* LeafNotFoundException::what() const noexcept
{
    std::ostringstream os;
    ss << "Key not found in ant leaf node: ";
    ss << fkey;
    static std::string message;
    message = ss.str();
    return message.c_str();
}

NodeNotFoundException::NodeNotFoundException(std::string asearch_node,
                                             std::string acontaining_node):
    fsearch_node(asearch_node), fcontaining_node(acontaining_node)
{
}

const char* NodeNotFoundException::what() const noexcept
{
    std::ostringstream os;
    ss << "Node | " << fserach_node << " | not found";
    ss << " as a child of node";
    ss << fcontaing_node;
    static std::string message;
    message = ss.str();
    return message.c_str();
}

RecordNotFoundException::RecordNotFoundException(KeyType akey):
    fkey(akey)
{
}

const char* RecordNotFoundException::what() const noexcept
{
    std::ostringstream ss;
    ss << "Record not found with key: " << fkey;
    static std::string message;
    message = ss.str();
    return message.c_str();
}
