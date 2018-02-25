#pragma once
#include "IWebHandler.h"
#include <string>

namespace sentinel {
    namespace web {
        
        class IWebHandler;
        
        class IWebServer {
        public:
            virtual ~IWebServer() { };

            virtual bool on(IWebHandler& handler) = 0;
            virtual void start() = 0;
            virtual void process() = 0;
            virtual void stop() = 0;
        };
        
        class IWebSender {
        public:
            virtual ~IWebSender() { };
            
            virtual void send(int code, const std::string& content_type, 
                const std::string& content) = 0;
            
            virtual void sendContent(const std::string& content) = 0;
            
        };

		class IWebArgProvider {
		public:
			virtual ~IWebArgProvider() { };
			virtual std::string arg(const std::string& name) const = 0;
		};
    }
}