#pragma once
#include "stdint.h"
#include "cstdlib"

enum CommandType: uint8_t {
	ON = 0x12,
	OFF = 0x13,
	COLOR = 0x20,
};

typedef struct lanternCommand lanternCommand;
struct lanternCommand {
	CommandType type;
	uint16_t length;
    uint8_t *value;
    explicit lanternCommand(CommandType type, uint16_t len) {
		this->type = type;
		this->length = len;
		if (len) {
			this->value = new uint8_t[length];
		}
	}
	~lanternCommand() {
		if (length)
			std::free(this->value);
	}
};
