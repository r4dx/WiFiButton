#include "EEPROM.h"
#include <Wire.h>
#include <Arduino.h>

namespace sentinel {
	namespace storage {
		EEPROM::EEPROM(const int sda, const int scl, const int i2c_device_address) :
			address(0),
			i2c_device_address(i2c_device_address) {
			Wire.begin(sda, scl);
		}

		uint8_t EEPROM::read_uint8() {
			Wire.beginTransmission(i2c_device_address);
			Wire.write(address >> 8); // MSB
			Wire.write(address & 0xFF); // LSB
			Wire.endTransmission();
			Wire.requestFrom(i2c_device_address, 1);
			address++;

			return Wire.read();
		}

		void EEPROM::write_uint8(const uint8_t data) {
			Wire.beginTransmission(i2c_device_address);
			Wire.write(address >> 8); // MSB
			Wire.write(address & 0xFF); // LSB
			Wire.write(data);
			Wire.endTransmission();

			address++;
			delay(5);
		}

		void EEPROM::move(const int address) {
			this->address = address;
		}

		void EEPROM::write_uint32(const uint32_t data) {
			write_uint8((data & 0xFF000000) >> 24);
			write_uint8((data & 0x00FF0000) >> 16);
			write_uint8((data & 0x0000FF00) >> 8);
			write_uint8(data & 0x000000FF);
		}

		uint32_t EEPROM::read_uint32() {
			uint32_t result = 0;
			result = read_uint8() << 24;
			result |= read_uint8() << 16;
			result |= read_uint8() << 8;
			result |= read_uint8();

			return result;
		}

		std::string EEPROM::read_string() {
			std::string result;
			uint8_t cur = read_uint8();
			while (cur != 0) {
				result += (char)cur;
				cur = read_uint8();
			}
			return result;
		}

		void EEPROM::write_string(const std::string& data) {
			for (int i = 0; i < data.size(); i++)
				write_uint8((char)data[i]);

			write_uint8(0);
		}

	}
}