#pragma once
#include <string>
#include <vector>

namespace sentinel {
	namespace string {
		bool replace(std::string& str, const std::string& from, const std::string& to);
		void replaceAll(std::string& str, const std::string& from, const std::string& to);
		std::vector<std::string> split(const std::string& str, const std::string& delimiter);
	}
}
