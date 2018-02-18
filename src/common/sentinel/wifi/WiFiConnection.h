#pragma once
#include <string>

namespace sentinel {
	namespace wifi {
		class WiFiConnection {
		public:
			bool connect();
			bool disconnect();
			std::string getIp() const;

			WiFiConnection(const std::string& SSID, const std::string& password,
				int attempts, int delayBetweenAttempts);
			~WiFiConnection();
			// Copy & Move are forbidden
			WiFiConnection(const WiFiConnection& other) = delete;
			WiFiConnection(WiFiConnection&& other) noexcept = delete;
			WiFiConnection& operator= (const WiFiConnection& other) = delete;
			WiFiConnection& operator= (WiFiConnection&& other) noexcept = delete;

		private:
			bool connected;
			const std::string& SSID;
			const std::string& password;
			int attempts;
			int delayBetweenAttempts;
		};
	}
}
