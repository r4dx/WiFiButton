#pragma once
#include "common/sentinel/web/IWebHandler.h"
#include "common/sentinel/web/Method.h"
#include "common/sentinel/logger/logger.h"
#include <string>
#include <memory>

namespace wifi_button {
	namespace handler {
		class SetupHandler : public sentinel::web::IWebHandler {
		public:
			bool canHandle() const override;
			void setPath(sentinel::web::Method method,
				std::shared_ptr<std::string> uri) override;

			void setSender(sentinel::web::IWebSender& sender) override;
			bool handle() override;

			SetupHandler(sentinel::log::Logger& logger);
		private:
			bool handleGet();
			bool handlePost();
			std::shared_ptr<std::string> uri;
			sentinel::web::Method method;

			sentinel::web::IWebSender* sender;
			sentinel::log::Logger& logger;

			static const std::string body_pattern;
		};
	}
}
