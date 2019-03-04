#include <iostream>
#include <map>

#include "TableRow.h"
#include "LogicalAddress.h"

uint64_t TranslateLogicalToPhysicalAddress(LogicalAddress logical);

uint64_t CR3;

std::map<uint64_t, TableRow> PhysicalMemory;

int main(int argc, char **argv)
{
    uint64_t m, q, paddr, value, logicalAddress;
    std::cin >> m >> q >> CR3;

    while(m--)
    {
        std::cin >> paddr >> value;
        TableRow temp;
        temp.Raw = value;
        PhysicalMemory[paddr] = temp;
    }

    while(q--)
    {
        LogicalAddress logicalAddress;
        std::cin >> logicalAddress.Raw;
        // std::cout << "Read logical address: " << logicalAddress.Raw << std::endl;

        uint64_t physicalAddress = TranslateLogicalToPhysicalAddress(logicalAddress);
        if(!physicalAddress)
        {
            std::cout << "fault" << std::endl;
        }
        else
        {
            std::cout << physicalAddress << std::endl;
        }

        // std::cout << std::endl;
    }

    return 0;
}

uint64_t TranslateLogicalToPhysicalAddress(LogicalAddress logical)
{
    // std::cout << "Address translating..." << std::endl;
    // std::cout << "PML4 = " << logical.PML4 << std::endl;
    // std::cout << "PML4 * 8 = " << logical.PML4 * sizeof(TableRow) << std::endl;
    uint64_t pml4eAddr = CR3 + logical.PML4 * sizeof(TableRow);
    // std::cout << "pml4eAddr = CM3 + PML4 * 8 = " << pml4eAddr << std::endl;
    TableRow pml4e = PhysicalMemory[pml4eAddr];
    // std::cout << "pml4e = mem[pml4eAddr] = " << pml4e.Raw << std::endl;

    if (!pml4e.IsLinked)
        return 0L;

    uint64_t pdpteBase = pml4e.PhysicalAddress << 12;
    // std::cout << "pdpteBase = pml4e.PhysicalAddress << 12 = " << pdpteBase << std::endl;
    uint64_t pdpteAddr = pdpteBase + logical.DirPtr * sizeof(TableRow);
    // std::cout << "DirPtr = " << logical.DirPtr << std::endl;
    // std::cout << "pdpteAddr = pdpteBase + DirPtr * 8 = " << pdpteAddr << std::endl;
    TableRow pdpte = PhysicalMemory[pdpteAddr];
    // std::cout << "pdpte = mem[pdpteAddr] = " << pdpte.Raw << std::endl;

    if (!pdpte.IsLinked)
        return 0L;

    uint64_t pdeBase = pdpte.PhysicalAddress << 12;
    // std::cout << "pdeBase = pdpte.PhysicalAddress << 12 = " << pdeBase << std::endl;
    uint64_t pdeAddr = pdeBase + logical.Dir * sizeof(TableRow);
    // std::cout << "Dir = " << logical.Dir << std::endl;
    // std::cout << "pdeAddr = pdeBase + Dir * 8 = " << pdeAddr << std::endl;
    TableRow pde = PhysicalMemory[pdeAddr];
    // std::cout << "pde = mem[pdeAddr] = " << pde.Raw << std::endl;

    if (!pde.IsLinked)
        return 0L;

    

    uint64_t pteBase = pde.PhysicalAddress << 12;
    // std::cout << "pteBase = pde.PhysicalAddress << 12 = " << pteBase << std::endl;
    uint64_t pteAddr = pteBase + logical.Table * sizeof(TableRow);
    // std::cout << "Table = " << logical.Table << std::endl;
    // std::cout << "pteAddr = pteBase + Table * 8 = " << pteAddr << std::endl;
    TableRow pte = PhysicalMemory[pteAddr];
    // std::cout << "pte = mem[pteAddr] = " << pte.Raw << std::endl;

    if (!pte.IsLinked)
        return 0L;

    uint64_t base = pte.PhysicalAddress << 12;
    // std::cout << "base = pte.PhysicalAddress << 12 = " << base << std::endl;
    uint64_t addr = base + logical.Offset;
    // std::cout << "Offset = " << logical.Offset << std::endl;
    // std::cout << "addr = base + Offset = " << addr << std::endl;
    return addr;
}
