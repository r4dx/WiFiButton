#pragma once
#include <string>

namespace sentinel {
	namespace wifi {
		class IProvider {
		public:
			virtual bool connect() = 0;
			virtual bool disconnect() = 0;
			virtual std::string getIp() const = 0;

			virtual ~IProvider() { };
		};
	}
}
