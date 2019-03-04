#pragma once

#include <cstdint>

struct TableRow
{
    union
    {
        uint64_t Raw;
        
        struct
        {
            uint64_t IsLinked: 1;
            uint64_t CanBeWritten: 1;
            uint64_t HasAccessFromUserspace: 1;
            uint64_t Reserved1: 4;
            uint64_t IsPhysicalPage: 1;
            uint64_t Reserved2: 4;
            uint64_t PhysicalAddress: 40;
            uint64_t Reserved3: 11;
            uint64_t CannotBeExecuted: 1;
        };
    };
};