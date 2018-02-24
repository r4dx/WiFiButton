#pragma once
#include <string>

namespace sentinel {
	namespace storage {
		class IStorage {
		public:
			virtual std::string read_string() = 0;
			virtual uint32_t read_uint32() = 0;
			virtual uint8_t read_uint8() = 0;
			virtual void write_string(const std::string& data) = 0;
			virtual void write_uint32(const uint32_t data) = 0;
			virtual void write_uint8(const uint8_t data) = 0;
			virtual void move(const int address) = 0;

			virtual ~IStorage() { }
		};
	}
}
