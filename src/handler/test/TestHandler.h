#pragma once

#include "common/sentinel/web/IWebHandler.h"
#include "common/sentinel/logger/logger.h"
#include <string>
#include <memory>

namespace wifi_button {
    namespace handler {
        class TestHandler : public sentinel::web::IWebHandler {
        public:
            bool canHandle() const override;
            void setPath(sentinel::web::Method method, 
                std::shared_ptr<std::string> uri) override;
                
            void setSender(sentinel::web::IWebSender& sender) override;
            bool handle() override;

			TestHandler(sentinel::log::Logger& logger);
        private:
            std::shared_ptr<std::string> uri;
            sentinel::web::Method method;                
                
			sentinel::web::IWebSender* sender;
            sentinel::log::Logger& logger;
        };
    }
}

