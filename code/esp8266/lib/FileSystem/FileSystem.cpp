//
// Created by Aaron Russo on 24/02/2018.
//

#include <Arduino.h>
#include <LogLog.h>
#include <EEPROM.h>
#include "FileSystem.h"

void FileSystem::init(memorySize size) {
    this->MEM_SIZE = size;
    if (this->MEM_SIZE == MEM_SMALL || this->MEM_SIZE == MEM_NORMAL) {
        this->availableSectors = 30;
    } else if (this->MEM_SIZE == MEM_BIG || this->MEM_SIZE == MEM_HUGE) {
        this->availableSectors = 60;
    }
    this->fileDescriptorsIndex = this->kernelBytes = this->availableSectors;
    this->sectorSize = (this->MEM_SIZE - this->availableSectors - this->kernelBytes) / this->availableSectors;
    EEPROM.begin(this->MEM_SIZE);
}

bool FileSystem::write(fileAddress address, const char *data, uint8 size) {
    memAddress pointer;
    uint8 i;
    if (size == 0) size = (uint8) strlen(data);
    if (size > this->sectorSize) size = this->sectorSize;
    EEPROM.write(this->getDescriptorAddress(address), size);
    pointer = this->getSectorAddress(address);
    for (i = 0; i < size; i += 1) {
        EEPROM.write(pointer, (uint8) data[i]);
        pointer += 1;
    }
    return EEPROM.commit();
}

const char *FileSystem::read(fileAddress address) {
    memAddress pointer;
    uint8 size, i;
    char *file;
    size = EEPROM.read(this->getDescriptorAddress(address));
    file = (char *) malloc(size);
    pointer = this->getSectorAddress(address);
    for (i = 0; i < size; i += 1) {
        file[i] = EEPROM.read(pointer);
        pointer += 1;
    }
    return file;
}

bool FileSystem::writeKernel(kernelAddress address, char value) {
    if (address < this->kernelBytes) {
        EEPROM.write(address, (uint8) value);
        return EEPROM.commit();
    } else return false;
}

char FileSystem::readKernel(kernelAddress address) {
    return EEPROM.read(address);
}

memAddress FileSystem::getSectorAddress(fileAddress address) {
    return (this->fileDescriptorsIndex + this->kernelBytes) + (this->sectorSize * address);
}

memAddress FileSystem::getDescriptorAddress(fileAddress address) {
    return this->fileDescriptorsIndex + address;
}

FileSystem flash;