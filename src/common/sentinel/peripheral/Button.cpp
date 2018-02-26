#include "Button.h"
#include <Arduino.h>

namespace sentinel {
	namespace peripheral {
		Button::Button(int pin, std::function<void()> onDown, int delayBetweenEvents) : 
			pin(pin),
			onDown(onDown),
			delayBetweenEvents(delayBetweenEvents) {
			pinMode(pin, INPUT);
		}

		void Button::process() {
			if (digitalRead(pin) == HIGH) {
				onDown();
				delay(delayBetweenEvents);
			}
		}

	}
}
