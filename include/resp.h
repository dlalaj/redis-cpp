#ifndef RESP_H
#define RESP_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

const char STRING  = '+';
const char ERROR   = '-';
const char INTEGER = ':';
const char BULK    = '$';
const char ARRAY   = '*';

class Value {
public:
    std::string typ;
    std::string str;
    int num;
    std::string bulk;
    std::vector<Value> array;

    Value() : num(0) {}
    std::string translateToResp();

private:
    std::string valueString();
    std::string valueBulk();
    std::string valueArray();
    std::string valuError();
    std::string valueNull();
};

class Resp {
public:
    Resp(std::istream& input);
    Value Read();

private:
    std::istream& reader;

    std::string readLine();
    int readInteger();
    Value readArray();
    Value readBulk();
};

#endif // RESP_H
