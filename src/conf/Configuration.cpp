#include "Configuration.h"

namespace wifi_button {
	namespace configuration {
		SaveResponse Configuration::save() {
			if (ssid.size() > 32)
				return SaveResponse::SSID_TOO_LONG;
			if (password.size() > 128)
				return SaveResponse::PASSWORD_TOO_LONG;
			if (url.size() > 2083)
				return SaveResponse::URL_TOO_LONG;
			if (headers.size() + body.size() + url.size() + password.size() + ssid.size() + sha1Fingerprint.size() + 5 >= 8000)
				return SaveResponse::OVERALL_SIZE_TOO_BIG;

			storage.write_uint32(magic);
			storage.write_string(ssid);
			storage.write_string(password);
			storage.write_string(url);
			storage.write_uint8((uint8_t)method);
			storage.write_string(headers);
			storage.write_string(body);
			storage.write_string(sha1Fingerprint);
			return SaveResponse::OK;

		}

		std::shared_ptr<Configuration> Configuration::load(sentinel::storage::IStorage& storage) {
			if (storage.read_uint32() != magic)
				return nullptr;

			std::shared_ptr<Configuration> result = std::make_shared<Configuration>(storage);

			result->ssid = storage.read_string();
			result->password = storage.read_string();
			result->url = storage.read_string();
			result->method = (sentinel::web::Method)storage.read_uint8();
			result->headers = storage.read_string();
			result->body = storage.read_string();
			result->sha1Fingerprint = storage.read_string();

			return result;
		}

		Configuration::Configuration(sentinel::storage::IStorage& storage) : storage(storage) { }
	}
}
