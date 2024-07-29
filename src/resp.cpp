#include "resp.h"

Resp::Resp(std::istream& input) : reader(input) {}

std::string Resp::readLine() {
    std::string line;
    char c;

    while (reader.get(c)) {
        line += c;
        if (line.length() >= 2 && line[line.length() - 2] == '\r') {
            break;
        }
    }
    return line.substr(0, line.length() - 2); // Remove the trailing CRLF
}

int Resp::readInteger() {
    std::string line = readLine();
    try {
        return std::stoi(line);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Invalid integer format");
    }
}

Value Resp::Read() {
    // b"*2\r\n$5\r\nhello\r\n$5\r\nworld\r\n"
    char type;
    if (!reader.get(type)) {
        throw std::runtime_error("Failed to read type");
    }
    switch (type) {
    case ARRAY:
        return readArray();
    case BULK:
        return readBulk();
    default:
        throw std::runtime_error("Unknown type");
    }
}

Value Resp::readArray() {
    Value v;
    v.typ = "array";

    int len = readInteger();
    v.array.resize(len);

    for (int i = 0; i < len; i++) {
        v.array[i] = Read();
    }
    return v;
}

Value Resp::readBulk() {
    Value v;
    v.typ = "bulk";
    std::string bulk="";
    char c;

    int len = readInteger();

    for (int i=0; i<len; i++) {
        reader.get(c);
        bulk += c;
    }
    std::cout<<"Bulk read: "<<bulk<<std::endl;
    v.bulk = bulk;
    readLine(); // Read the trailing CRLF

    return v;
}
