#include <serial/serial.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::serial;
using namespace example;

int main()
{
       Fake narrow(9);
       Fake wide(16);
       Serial serial(narrow);
       Serial synchronous(wide);
       const Config bad{0, Mode::Asynchronous, 0, Parity::Even, StopBits::One};
       const Config config{9600, Mode::Synchronous, 16, Parity::None, StopBits::One};
       assert(serial.configure(bad) == Status::InvalidArgument);
       assert(serial.configure(config) == Status::Unsupported);
       assert(synchronous.configure(config) == Status::Success);
       assert(serial.try_write(0x155) == Status::InvalidArgument);
       assert(synchronous.try_write(0x8001) == Status::Success);
       assert(synchronous.try_write(1) == Status::Busy && !synchronous.transmission_complete());
       Frame frame = 3;
       assert(synchronous.try_read(frame) == Status::Success && frame == 0x8001);
       assert(synchronous.try_read(frame) == Status::Busy && frame == 0x8001);
       assert(synchronous.try_write(1) == Status::Success);
       wide.corrupted = true;
       assert(synchronous.try_read(frame) == Status::FrameError && frame == 0x8001);

       assert(serial.configure({9600, Mode::Asynchronous, 8, Parity::None, StopBits::None}) == Status::InvalidArgument);
       assert(synchronous.configure({9600, Mode::Synchronous, 16, Parity::None, StopBits::None}) == Status::Success);
}
