#include <serial/serial.hpp>
#include "fake.hpp"

using namespace mhaa::serial;
using namespace example;

int main()
{
    Fake link;
    Serial serial(link);
    const Config config{9600, Mode::Asynchronous, 9, Parity::None, StopBits::One};
    return serial.configure(config) == Status::Success &&
                   serial.try_write(0x155) == Status::Success
               ? 0
               : 1;
}
