#ifndef MHAA_SERIAL_HPP
#define MHAA_SERIAL_HPP

#include <serial/peripheral.hpp>
#include <serial/types.hpp>

namespace mhaa
{
    namespace serial
    {
        /** @brief Configures and polls one borrowed framed serial peripheral. */
        class Serial
        {
        public:
            explicit Serial(Peripheral &peripheral) : peripheral_(peripheral) {}

            Status configure(const Config &config)
            {
                if (config.baud_rate == 0 || config.data_bits == 0 || config.data_bits > 16 ||
                    (config.mode == Mode::Asynchronous && config.stop_bits == StopBits::None))
                {
                    return Status::InvalidArgument;
                }
                return peripheral_.configure(config);
            }

            Status try_write(Frame frame) { return peripheral_.try_write(frame); }
            Status try_read(Frame &frame) { return peripheral_.try_read(frame); }
            bool transmission_complete() const { return peripheral_.transmission_complete(); }

        private:
            Peripheral &peripheral_;
        };
    }
}

#endif
