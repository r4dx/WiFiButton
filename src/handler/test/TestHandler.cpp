#include "TestHandler.h"
#include "common/sentinel/storage/eeprom/EEPROM.h"

namespace wifi_button {
    namespace handler {
        void TestHandler::setPath(sentinel::web::Method method, std::shared_ptr<std::string> uri) {   
            this->uri = uri;
            this->method = method;
        }                
                
        bool TestHandler::canHandle() const {
            return uri->compare("/test") == 0 && method == sentinel::web::Method::GET;
        }

		TestHandler::TestHandler(sentinel::log::Logger& logger) :
                logger(logger), 
                sender(nullptr),
                uri(std::shared_ptr<std::string>()),
                method(sentinel::web::Method::DELETE) { }

        void TestHandler::setSender(sentinel::web::IWebSender& sender) {
            this->sender = &sender;
        }

		std::string to_string(int number) {
			char buff[256];
			itoa(number, buff, 10);
			return std::string(buff);
		}

        bool TestHandler::handle() {
            logger.info("Test handler");
			sentinel::storage::EEPROM eeprom(SDA, SCL, 0x50);
			eeprom.move(5000);
			eeprom.write_string("Hello, happy world");
			eeprom.move(5000);
			std::string result = eeprom.read_string();
			sender->send(200, "text/html", "OK: " + result);
            return true;
        }
    }
}