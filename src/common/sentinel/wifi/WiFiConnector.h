#pragma once
#include <string>

namespace sentinel {
	namespace wifi {
		class WiFiConnector {
		public:
			WiFiConnector(const std::string& SSID, const std::string& password, 
				int attempts, int delayBetweenAttempts);
			bool connect();
			bool disconnect();
			std::string getIp() const;

		private:
			const std::string& SSID;
			const std::string& password;
			int attempts;
			int delayBetweenAttempts;
		};
	}
}
