#pragma once

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <vector>
#include <limits>

class MemoryNavigator {
private:
    char* baseAddress;
    size_t memorySize;
    int currentOffset;
    int bytesPerLine;
    int ptrSize;

public:
    MemoryNavigator(size_t size = 1024) : memorySize(size), currentOffset(0), bytesPerLine(16), ptrSize(sizeof(void*)) {
        baseAddress = new char[memorySize];
        std::memset(baseAddress, 0xAB, memorySize); // Fill memory with example data
    }

    ~MemoryNavigator() {
        delete[] baseAddress;
    }

    void displayMemory() {
        std::cout << "Current base address: " << static_cast<void*>(baseAddress + currentOffset) << std::endl;
        for (int i = 0; i < memorySize; i += bytesPerLine) {
            std::cout << std::hex << std::setfill('0');
            std::cout << "0x" << reinterpret_cast<uintptr_t>(baseAddress + currentOffset + i) << ": ";
            for (int j = 0; j < bytesPerLine; j++) {
                std::cout << std::setw(2) << static_cast<unsigned>(static_cast<unsigned char>(baseAddress[currentOffset + i + j])) << " ";
            }
            std::cout << std::dec << "| ";
            for (int j = 0; j < bytesPerLine; j++) {
                char ch = isprint(baseAddress[currentOffset + i + j]) ? baseAddress[currentOffset + i + j] : '.';
                std::cout << ch;
            }
            std::cout << std::endl;
        }
    }

    void handleCommand(const std::string& commandLine) {
        std::istringstream iss(commandLine);
        std::string command;
        iss >> command;

        if (command == "goto") {
            uintptr_t newAddress;
            iss >> std::hex >> newAddress >> std::dec;
            currentOffset = static_cast<int>(newAddress - reinterpret_cast<uintptr_t>(baseAddress));
            displayMemory();
        } else if (command == "move") {
            int offset;
            iss >> offset;
            currentOffset += offset;
            displayMemory();
        } else if (command == "display") {
            int newBytesPerLine;
            iss >> newBytesPerLine;
            bytesPerLine = newBytesPerLine;
            displayMemory();
        } else if (command == "ptr_size") {
            int newSize;
            iss >> newSize;
            ptrSize = newSize;
            std::cout << "Pointer size set to " << ptrSize << " bytes." << std::endl;
        } else if (command == "exit") {
            std::cout << "Exiting..." << std::endl;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    static inline void run()
    {
        MemoryNavigator navigator;
        std::string input;

        // Clear any leftover characters in the input buffer before starting the main loop.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (true) {
            std::cout << "Enter command (commands, exit): ";
            
            if (!std::getline(std::cin, input)) {
                std::cout << "Error reading input, try again.\n";
                std::cin.clear(); // Clear error flags.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next newline.
                continue;
            }

            if (input.empty()) {
                std::cout << "No command entered, please try again.\n";
                continue;
            }

            navigator.handleCommand(input);
        }
    }
};
