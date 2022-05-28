#include <iostream>
#include <string>

using std::string;

class Configuration {
private:

	static constexpr char config_file[] = "/etc/program_name/default.conf";

	Configuration() {
		// instantiation is not thread-safe
		// maybe parse initial state from a configuration file
		std::cout << "Constructing Configuration" << std::endl;
	}

public:

/* Creation */

	static Configuration& build() {
		if (config == nullptr) {
			config = new Configuration();
		}
		return *Configuration::config;
	}

	static void destroy() {
		delete config;
		config = nullptr;
	}

	void f() const {}
	void g() {} // if there are any non-const functions then the singleton won't be thread-safe depending on the context


private:

	static Configuration* config;
};

Configuration* Configuration::config = nullptr;

void f() {
	auto config = Configuration::build();
	// user updates settings
}

int main() {
	auto config = Configuration::build();

	f();
	// user might have updated settings and we still have access to it
	return 0;
}
