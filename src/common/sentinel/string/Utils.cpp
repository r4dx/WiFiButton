#include "Utils.h"

namespace sentinel {
	namespace string {
		bool replace(std::string& str, const std::string& from, const std::string& to) {
			size_t start_pos = str.find(from);
			if (start_pos == std::string::npos)
				return false;
			str.replace(start_pos, from.length(), to);
			return true;
		}

		void replaceAll(std::string& str, const std::string& from, const std::string& to) {
			size_t start_pos = 0;
			while (true) {
				start_pos = str.find(from, start_pos);
				if (start_pos == std::string::npos)
					break;
				str.replace(start_pos, from.length(), to);
			}
		}

		std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
			size_t previous = 0;
			size_t start_pos = 0;
			std::vector<std::string> result;
			while (true) {
				start_pos = str.find(delimiter, previous);
				if (start_pos == std::string::npos)
					break;
				result.push_back(str.substr(previous, start_pos - previous));
				previous = start_pos + delimiter.size();
			}
			result.push_back(str.substr(previous));
			return result;
		}


	}
}