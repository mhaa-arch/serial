#ifndef MHAA_SERIAL_EXAMPLE_FAKE_HPP
#define MHAA_SERIAL_EXAMPLE_FAKE_HPP

#include <serial/peripheral.hpp>

namespace example
{
    using namespace mhaa::serial;

    class Fake final : public Peripheral
    {
    public:
        explicit Fake(uint8_t maximum = 9) : maximum_(maximum) {}
        Status configure(const Config &config) override
        {
            if (config.data_bits > maximum_)
            {
                return Status::Unsupported;
            }
            bits_ = config.data_bits;
            return Status::Success;
        }
        Status try_write(Frame frame) override
        {
            if (available_)
            {
                return Status::Busy;
            }
            if (uint32_t{frame} >> bits_)
            {
                return Status::InvalidArgument;
            }
            frame_ = frame;
            available_ = true;
            return Status::Success;
        }
        Status try_read(Frame &frame) override
        {
            if (!available_)
            {
                return Status::Busy;
            }
            available_ = false;
            if (corrupted)
            {
                return Status::FrameError;
            }
            frame = frame_;
            return Status::Success;
        }
        bool transmission_complete() const override { return !available_; }

        bool corrupted = false;

    private:
        uint8_t maximum_;
        uint8_t bits_ = 8;
        Frame frame_ = 0;
        bool available_ = false;
    };
}

#endif
