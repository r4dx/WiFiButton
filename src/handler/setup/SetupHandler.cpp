#include "SetupHandler.h"
#include <common/sentinel/string/Utils.h>

namespace wifi_button {
	namespace handler {
		const std::string SetupHandler::body_pattern = "<html><body><form id='setupForm' method='POST'><table><tr><td colspan='2'><h1>Setup</h1></td></tr><tr><td colspan='2' align='right'>N.B. 8Kb max</td></tr><tr><td colspan='2'><h2>WiFi setup</h2></td></tr><tr><td>SSID</td><td><input type='text' name='ssid' value='%SSID%' /></td></tr><tr><td>Password</td><td><input type='password' name='password' value='%PASSWORD%' /></td></tr><tr><td colspan='2'><h2>Button</h2></td></tr><tr><td>URL</td><td><input type='text' name='url' value='%URL%' /></td></tr>            <tr>                <td>SHA1 Fingerprint (for HTTPS)</td>                <td><input type='text' name='sha1Fingerprint' value='%SHA1FINGERPRINT%' /></td>            </tr><tr><td>Method</td><td><select name='method'><option value='get' %GET_SELECTED%>GET</option><option value='post' %POST_SELECTED%>POST</option><option value='delete' %DELETE_SELECTED%>DELETE</option><option value='put' %PUT_SELECTED%>PUT</option></select></td></tr><tr><td>Headers</td><td><textarea name='headers' cols='50' rows='10'>%HEADERS%</textarea></td></tr><tr><td>Body</td><td><textarea name='body' cols='50' rows='10'>%BODY%</textarea></td></tr><tr><td>&nbsp;</td><td align='right'>N.B. Save will restart device</td></tr><tr><td>&nbsp;</td><td align='right'><input type='submit' value='Save' /></td></tr></table></form></body></html>";

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
		void SetupHandler::setArgProvider(const sentinel::web::IWebArgProvider& argProvider) {
			this->argProvider = &argProvider;
		}
		bool SetupHandler::handle() {
			bool result = true;
			if (method == sentinel::web::Method::POST)
				 result = handlePost();

			render();
			return result;
		}
		SetupHandler::SetupHandler(sentinel::log::Logger& logger, 
			std::shared_ptr<wifi_button::configuration::Configuration> configuration) :
				logger(logger), 
				configuration(configuration) { }


		void SetupHandler::render() {
			std::string content(body_pattern);
			sentinel::string::replace(content, "%SSID%", configuration->ssid);
			sentinel::string::replace(content, "%PASSWORD%", configuration->password);
			sentinel::string::replace(content, "%URL%", configuration->url);
			sentinel::string::replace(content, "%SHA1FINGERPRINT%", configuration->sha1Fingerprint);
			sentinel::string::replace(content, "%GET_SELECTED%", configuration->method == sentinel::web::Method::GET ? "selected" : "");
			sentinel::string::replace(content, "%POST_SELECTED%", configuration->method == sentinel::web::Method::POST ? "selected" : "");
			sentinel::string::replace(content, "%DELETE_SELECTED%", configuration->method == sentinel::web::Method::DELETE ? "selected" : "");
			sentinel::string::replace(content, "%PUT_SELECTED%", configuration->method == sentinel::web::Method::PUT ? "selected" : "");
			sentinel::string::replace(content, "%HEADERS%", configuration->headers);
			sentinel::string::replace(content, "%BODY%", configuration->body);
			sender->send(200, "text/html", content);
		}
		bool SetupHandler::handlePost() {
			logger.info("Starting to handle post...");
			configuration->ssid = argProvider->arg("ssid");
			configuration->password = argProvider->arg("password");

			if (argProvider->arg("method") == "get")
				configuration->method = sentinel::web::Method::GET;
			else if (argProvider->arg("method") == "post")
				configuration->method = sentinel::web::Method::POST;
			else if (argProvider->arg("method") == "delete")
				configuration->method = sentinel::web::Method::DELETE;
			else if (argProvider->arg("method") == "put")
				configuration->method = sentinel::web::Method::PUT;
			else
				return false;

			logger.info("Passed method");

			configuration->url = argProvider->arg("url");
			configuration->sha1Fingerprint = argProvider->arg("sha1Fingerprint");
			configuration->headers = argProvider->arg("headers");
			configuration->body = argProvider->arg("body");

			logger.info("Saving...");
			wifi_button::configuration::SaveResponse response = configuration->save();
			logger.info("Save response - %u", response);

			if (response == wifi_button::configuration::SaveResponse::OK) {
				logger.info("Restarting to apply new settings...");
				ESP.restart();
			}

			return false;
		}
	}
}

