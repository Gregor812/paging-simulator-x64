#pragma once

#include <cstdint>

struct LogicalAddress
{
    union
    {
        uint64_t Raw;

        struct
        {
            uint64_t Offset : 12;
            uint64_t Table : 9;
            uint64_t Dir : 9;
            uint64_t DirPtr : 9;
            uint64_t PML4 : 9;
        };

        // struct
        // {
        //     uint64_t Offset : 21;
        //     uint64_t Dir : 9;
        //     uint64_t DirPtr : 9;
        //     uint64_t PML4 : 9;
        // } Page2MB;

        // struct
        // {
        //     uint64_t Offset : 30;
        //     uint64_t DirPtr : 9;
        //     uint64_t PML4 : 9;
        // } Page1GB;
    };
};
