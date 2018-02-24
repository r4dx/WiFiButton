#pragma once
#include <string>
#include <stdint.h>
#include "../IStorage.h"

namespace sentinel {
	namespace storage {
		class EEPROM : public IStorage {
		public:
			std::string read_string() override;
			uint32_t read_uint32() override;
			uint8_t read_uint8() override;
			void write_string(const std::string& data) override;
			void write_uint32(const uint32_t data) override;
			void write_uint8(const uint8_t data) override;

			void move(const int address) override;

			EEPROM(const int sda, const int scl, const int i2c_device_address);


		private:
			int address;
			int i2c_device_address;
		};
	}
}