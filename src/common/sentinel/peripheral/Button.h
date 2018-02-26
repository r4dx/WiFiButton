#pragma once
#include <functional>

namespace sentinel {
	namespace peripheral {
		class Button {
		public:
			Button(int pin, std::function<void()> onDown, int delayBetweenEvents);
			void process();
		private:
			int pin;
			int delayBetweenEvents;
			std::function<void()> onDown;
		};
	}
}