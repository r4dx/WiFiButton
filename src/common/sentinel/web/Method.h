#pragma once
#include "ESP8266WebServer.h"
#include <string>

namespace sentinel {
    namespace web {
        enum Method : byte {
            GET,
            POST,
            DELETE,
			PUT
        };
        
        HTTPMethod methodToHTTPMethod(Method method);
		Method httpMethodToMethod(HTTPMethod method);
		std::string methodToString(Method method);
    }
}