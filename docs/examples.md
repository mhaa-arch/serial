# Run the Serial Core example

The example configures nine data bits at 9600 baud with no parity and one stop symbol. The facade accepts `0x155` as one frame. The program checks that the fake accepted it. The behavior test also uses a wider synchronous implementation and exercises receive busy, corrupt-frame handling and completion.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
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
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/serial-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
