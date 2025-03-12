#ifndef ASCII85_H
#define ASCII85_H

#include <iostream>
#include <cstddef>

void encode(const char* input, size_t len, std::ostream& out);
bool decode(std::istream& in, std::ostream& out);

#endif // ASCII85_H