#pragma once
#include "common.h"

namespace engine::utils
{
    class UUIDGenerator {
    public:
        UUIDGenerator();
        uint32_t generate();
    private:
        std::atomic<uint32_t > counter;
        std::unordered_set<uint32_t > set;
    };

}

