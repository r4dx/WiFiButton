#ifndef GETLOGHANDLER_H
#define GETLOGHANDLER_H

#include "common/sentinel/web/IWebHandler.h"
#include "common/sentinel/logger/logger.h"
#include <string>
#include <memory>

namespace wifi_button {
    namespace handler {
        class HealthcheckHandler : public sentinel::web::IWebHandler {
        public:
            bool canHandle() const override;
            void setPath(sentinel::web::Method method, 
                std::shared_ptr<std::string> uri) override;
                
            void setSender(sentinel::web::IWebSender& sender) override;
            bool handle() override;

            HealthcheckHandler(sentinel::log::Logger& logger);
        private:
            std::shared_ptr<std::string> uri;
            sentinel::web::Method method;                
                
			sentinel::web::IWebSender* sender;
            sentinel::log::Logger& logger;
        };
    }
}
#endif /* GETLOGHANDLER_H */

