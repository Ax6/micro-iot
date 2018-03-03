//
// Created by Aaron Russo on 24/02/2018.
//

#ifndef ESP8266_MEMORY_H
#define ESP8266_MEMORY_H

#include <c_types.h>
#include <OS.h>

// Max size for single data = 1 Sector size
typedef enum {
    MEM_SMALL = 540,    //30 Sectors of 16 bytes each
    MEM_NORMAL = 1020,  //30 Sectors of 32 bytes each
    MEM_BIG = 2040,     //60 Sectors of 32 bytes each
    MEM_HUGE = 3960     //60 Sectors of 64 bytes each
} memorySize;

typedef unsigned char memAddress;

class FileSystem {
private:
    memorySize MEM_SIZE;
    memAddress fileDescriptorsIndex;
    uint8 sectorSize, kernelBytes, availableSectors;

    memAddress getSectorAddress(fileAddress);

    memAddress getDescriptorAddress(fileAddress);

public:
    void init(memorySize);

    bool write(fileAddress, const char *, uint8 = 0);

    const char *read(fileAddress);

    bool writeKernel(kernelAddress, char);

    char readKernel(kernelAddress);
};

extern FileSystem flash;

#endif //ESP8266_MEMORY_H
