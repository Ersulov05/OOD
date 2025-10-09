#pragma once
#include <memory>

uint8_t CryptByte(const uint8_t byte, uint8_t key)
{
	uint8_t byteXOR = byte ^ key;
	uint8_t result = 0;

	result |= (byteXOR << 2) & 0b00011100;
	result |= (byteXOR >> 5) & 0b00000011;
	result |= (byteXOR >> 2) & 0b00100000;
	result |= (byteXOR << 3) & 0b11000000;

	return result;
}

uint8_t DecryptByte(const uint8_t byte, uint8_t key)
{
	uint8_t result = 0;

	result |= (byte >> 2) & 0b00000111;
	result |= (byte << 5) & 0b01100000;
	result |= (byte << 2) & 0b10000000;
	result |= (byte >> 3) & 0b00011000;

	return result ^ key;
}