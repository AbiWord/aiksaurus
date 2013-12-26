#include "MeaningStream.h"

const int MeaningStream::EOL = 0xFFFF;

MeaningStream::MeaningStream(std::istream& in)
: d_in(in)
{

}

MeaningStream::~MeaningStream()
{

}

bool MeaningStream::operator>>(int& id)
{
    unsigned char x1, x2;

    if (!d_in.get(x1))
        return false;

    if (!d_in.get(x2))
        return false;

    id = (static_cast<int>(x1) << 8) | x2;

    return true;
}
