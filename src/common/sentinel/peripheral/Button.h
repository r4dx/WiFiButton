#pragma once
#include <functional>

namespace sentinel {
	namespace peripheral {
		class Button {
		public:
			Button(int pin, std::function<void()> onDown);
			void process();
		private:
			int pin;
			std::function<void()> onDown;
		};
	}
}