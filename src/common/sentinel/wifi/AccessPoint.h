#pragma once
#include <string>
#include "IProvider.h"

namespace sentinel {
	namespace wifi {
		class AccessPoint : public IProvider {
		public:
			bool connect() override;
			bool disconnect() override;
			std::string getIp() const override;

			AccessPoint(const std::string& SSID);
			~AccessPoint() override;
			// Copy & Move are forbidden
			AccessPoint(const AccessPoint& other) = delete;
			AccessPoint(AccessPoint&& other) noexcept = delete;
			AccessPoint& operator= (const AccessPoint& other) = delete;
			AccessPoint& operator= (AccessPoint&& other) noexcept = delete;

		private:
			bool connected;
			const std::string& SSID;
		};
	}
}
