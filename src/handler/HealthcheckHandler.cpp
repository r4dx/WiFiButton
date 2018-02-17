#include "HealthcheckHandler.h"

namespace wifi_button {
    namespace handler {
        void HealthcheckHandler::setPath(sentinel::web::Method method, std::shared_ptr<std::string> uri) {   
            this->uri = uri;
            this->method = method;
        }                
                
        bool HealthcheckHandler::canHandle() const {
            return uri->compare("/healthcheck") == 0 && method == sentinel::web::Method::GET;
        }

		HealthcheckHandler::HealthcheckHandler(sentinel::log::Logger& logger) :
                logger(logger), 
                sender(nullptr),
                uri(std::shared_ptr<std::string>()),
                method(sentinel::web::Method::DELETE) { }

        void HealthcheckHandler::setSender(sentinel::web::IWebSender& sender) {
            this->sender = &sender;
        }

        bool HealthcheckHandler::handle() {
            logger.info("Healthcheck handler");   
			sender->send(200, "text/html", "OK");
            return true;
        }
    }
}