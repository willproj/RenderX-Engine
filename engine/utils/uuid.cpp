#include "uuid.h"

namespace engine::utils
{
    UUIDGenerator::UUIDGenerator()
        :counter(0)
    {

    }

    uint32_t  UUIDGenerator::generate() {
        auto now = std::chrono::high_resolution_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        uint32_t  counter_value = counter++;
        uint32_t  uuid = (timestamp << 16) | (counter_value & 0xFFFFULL);
        if (set.find(uuid) != set.end())
        {
            return generate();
        }
        return uuid;
    }
}