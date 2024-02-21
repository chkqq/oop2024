#include <iostream>

int countSetBits(int byte) 
{
    int count = 0;
    while (byte)
    {
        count += byte & 1;
        byte >>= 1;
    }
    return count;
}

void PrintBitsInByte(int byte, int setBitsCount)
{
    std::cout << "Number of set bits in byte " << byte << " is: " << setBitsCount << std::endl;
}

int main() 
{
    int byte;
    std::cout << "Enter a byte (0-255): ";
    std::cin >> byte;

    if (byte < 0 || byte > 255) 
    {
        std::cerr << "Invalid input. Byte must be an integer between 0 and 255." << std::endl;
        return 1;
    }

    int setBitsCount = countSetBits(byte);
    PrintBitsInByte(byte, setBitsCount);
    return 0;
}
