#pragma once
#include <string>
#include "common/sentinel/web/Method.h"
#include "common/sentinel/storage/IStorage.h"
#include <memory>
#include <stdint.h>

namespace wifi_button {
    namespace configuration {
		enum SaveResponse {
			OK,
			SSID_TOO_LONG,
			URL_TOO_LONG,
			PASSWORD_TOO_LONG,
			OVERALL_SIZE_TOO_BIG
		};

        class Configuration {
		public:
			std::string ssid;
			std::string password;
			std::string url;
			sentinel::web::Method method;
			std::string headers;
			std::string body;
			std::string sha1Fingerprint;

			SaveResponse save();
			static std::shared_ptr<Configuration> load(sentinel::storage::IStorage& storage);
			Configuration(sentinel::storage::IStorage& storage);
		private:
			sentinel::storage::IStorage& storage;

			static const uint32_t magic = 0x0ddfee1;
        };
	}
}