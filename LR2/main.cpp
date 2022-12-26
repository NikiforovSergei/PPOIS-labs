#include <iostream>
#include "field/field.h"
#include "crow.h"
using json = nlohmann::json;
#define PORT 8080

template<class... Args>
void log(Args... args) {
  std::cout << "[ws] ";
  (std::cout << ... << args) << std::endl;
}

int main() {
  crow::SimpleApp app;
  CROW_ROUTE(app, "/")
	.websocket(&app)
	.onopen([&](crow::websocket::connection &conn) {
	  log("Connection has been opened");
	  auto field = new Field();
	  conn.userdata(field);
	})
	.onclose([&](crow::websocket::connection &conn, const std::string &reason) {
	  log("Connection has been closed");
	  auto field = (Field *)conn.userdata();
	  delete field;
	})
	.onmessage([&](crow::websocket::connection &conn, const std::string &data, bool is_binary) {
	  try {
		auto field = (Field *)conn.userdata();
		auto message = json::parse(data);
		auto action = message["action"].get<std::string>();
		auto payload = message["payload"];
		log("New message `", action, "`");
		if (message["action"] == "init") {
		  field->Init(
			  payload["rows"].get<unsigned long>(),
			  payload["columns"].get<unsigned long>()
		  );
		} else if (message["action"] == "play") {
		  field->Play();
		} else return;
		json update = {
			{"mutation", "update"},
			{"payload", field->ToJSON()}
		};
	  	conn.send_text(update.dump());
	  } catch (const std::exception &e) {
		json error = {
		  {"mutation", "error"},
		  {"payload", e.what()}
		};
		conn.send_text(error.dump());
		log("Error: ", e.what());
	  }
	});

  app.port(PORT).multithreaded().run();
  std::cout << "App is running on port " << PORT << std::endl;

  return 0;
}
