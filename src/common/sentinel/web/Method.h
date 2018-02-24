#ifndef METHOD_H
#define METHOD_H

#include "ESP8266WebServer.h"

namespace sentinel {
    namespace web {
        enum Method : byte {
            GET,
            POST,
            DELETE,
			PUT,
			HEAD
        };
        
        HTTPMethod methodToHTTPMethod(Method method);
        Method httpMethodToMethod(HTTPMethod method);           
        
    }
}

#endif