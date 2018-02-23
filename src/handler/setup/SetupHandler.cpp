#include "SetupHandler.h"

namespace wifi_button {
	namespace handler {
		const std::string SetupHandler::body_pattern = "<html><body><form id='setupForm'><table><tr><td colspan='2'><h1>Setup</h1></td></tr><tr><td colspan='2' align='right'>N.B. 64Kb max</td></tr><tr><td colspan='2'><h2>WiFi setup</h2></td></tr><tr><td>SSID</td><td><input type='text' id='ssid' value='%SSID%' /></td></tr><tr><td>Password</td><td><input type='password' id='password' value='%PASSWORD%' /></td></tr><tr><td colspan='2'><h2>Button</h2></td></tr><tr><td>URL</td><td><input type='text' id='url' value='%URL%' /></td></tr><tr><td>Method</td><td><select id='method'><option value='get' %GET_SELECTED%>GET</option><option value='post' %POST_SELECTED%>POST</option><option value='delete' %DELETE_SELECTED%>DELETE</option><option value='put' %PUT_SELECTED%>PUT</option><option value='head' %HEAD_SELECTED%>HEAD</option></select></td></tr><tr><td>Headers</td><td><textarea id='headers' cols='50' rows='10'>%HEADERS%</textarea></td></tr><tr><td>Body</td><td><textarea id='body' cols='50' rows='10'>%BODY%</textarea></td></tr><tr><td>&nbsp;</td><td align='right'>N.B. Save will restart device</td></tr><tr><td>&nbsp;</td><td align='right'><input type='submit' value='Save' /></td></tr></table></form></body></html>";

		bool SetupHandler::canHandle() const {
			return uri->compare("/setup.html") == 0 &&
				(method == sentinel::web::Method::GET || method == sentinel::web::Method::POST);
		}
		void SetupHandler::setPath(sentinel::web::Method method, std::shared_ptr<std::string> uri) {
			this->uri = uri;
			this->method = method;
		}
		void SetupHandler::setSender(sentinel::web::IWebSender& sender) {
			this->sender = &sender;
		}
		bool SetupHandler::handle() {
			if (method == sentinel::web::Method::GET)
				return handleGet();

			return handlePost();
		}
		SetupHandler::SetupHandler(sentinel::log::Logger& logger) : logger(logger) {}

		bool replace(std::string& str, const std::string& from, const std::string& to) {
			size_t start_pos = str.find(from);
			if (start_pos == std::string::npos)
				return false;
			str.replace(start_pos, from.length(), to);
			return true;
		}


		bool SetupHandler::handleGet() {
			std::string content(body_pattern);
			replace(content, "%SSID%", "ssid");
			replace(content, "%PASSWORD%", "pass");
			replace(content, "%URL%", "url");
			replace(content, "%GET_SELECTED%", "");
			replace(content, "%POST_SELECTED%", "selected");
			replace(content, "%DELETE_SELECTED%", "");
			replace(content, "%PUT_SELECTED%", "");
			replace(content, "%HEAD_SELECTED%", "");
			replace(content, "%HEADERS%", "headers");
			replace(content, "%BODY%", "body");
			sender->send(200, "text/html", content);
			return true;
		}
		bool SetupHandler::handlePost() {
			return false;
		}
	}
}

