#pragma once
#include <cstdint>


namespace hal {

    using TimeTicks_t = uint64_t;

    /**
     * Generic timer interface.
    */
    class ITimer {
    public:
        ITimer() = default;
        virtual ~ITimer() = default;
    };
}
