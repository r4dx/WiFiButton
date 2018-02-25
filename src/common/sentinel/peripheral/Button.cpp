#include "Button.h"
#include <Arduino.h>

namespace sentinel {
	namespace peripheral {
		Button::Button(int pin, std::function<void()> onDown) : 
			pin(pin),
			onDown(onDown) { 
			pinMode(pin, INPUT);
		}

		void Button::process() {
			if (digitalRead(pin) == HIGH)
				onDown();
		}

	}
}
