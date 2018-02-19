#pragma once
#include <string>
#include "IProvider.h"

namespace sentinel {
	namespace wifi {
		class Connection : public IProvider {
		public:
			bool connect() override;
			bool disconnect() override;
			std::string getIp() const override;

			Connection(const std::string& SSID, const std::string& password,
				int attempts, int delayBetweenAttempts);
			~Connection() override;
			// Copy & Move are forbidden
			Connection(const Connection& other) = delete;
			Connection(Connection&& other) noexcept = delete;
			Connection& operator= (const Connection& other) = delete;
			Connection& operator= (Connection&& other) noexcept = delete;

		private:
			bool connected;
			const std::string& SSID;
			const std::string& password;
			int attempts;
			int delayBetweenAttempts;
		};
	}
}
