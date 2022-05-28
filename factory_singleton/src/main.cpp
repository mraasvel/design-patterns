#include "FactoryService.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class FactoryService;

struct User {
	User(int id = -1, const string& username = "default")
	: id(id), username(username) {}
	User(int id = -1, string&& username = "default")
	: id(id), username(username) {}

	int id;
	string username;
};

struct Database {
	std::unordered_map<int, User> users;
};

class UserService : IService {
public:
	UserService(Database db)
	: db(db) {
		std::cout << "Making User Service" << std::endl;
	}

	~UserService() {}

	IService* clone() {
		return this;
		// return UserService::build();
	}

	static IService* build() {
		return new UserService { Database {} };
	}

	static UserService* get() {
		auto factory = FactoryService::get();
		return static_cast<UserService*>(factory->build(FactoryService::USER_SERVICE));
	}

	User find_user(int id) const {
		auto user = db.users.find(id);
		if (user == db.users.end()) {
			printf("didn't find user\n");
			throw 404;
		}
		return user->second;
	}

	void add_user(User user) {
		db.users.insert(std::make_pair(user.id, std::move(user)));
	}

	void remove_user(int id) {
		db.users.erase(id);
	}

	void print() const {
		for (auto& it : db.users) {
			printf("User {\n\tid: %d\n\tname: %s\n}\n", it.second.id, it.second.username.c_str());
		}
	}

private:
	Database db;
};

FactoryService::FactoryService() {
	std::cout << "Initializing Factory" << std::endl;
	services[USER_SERVICE] = UserService::build();
}

FactoryService::~FactoryService() {
	for (auto& service: services) {
		delete service.second;
	}
}

IService* FactoryService::build(ServiceType type) {
	auto service = services.find(type);
	if (service == services.end()) {
		std::cout << "didn't find service" << std::endl;
		return nullptr;
	}
	return service->second->clone();
}

FactoryService* FactoryService::get() {
	if (factory_service == nullptr) {
		factory_service = new FactoryService {};
	}
	return factory_service;
}

FactoryService* FactoryService::factory_service = nullptr;

void authenticate(int id) {
	auto user_service = UserService::get();
	auto user = user_service->find_user(id);
}

int main() {
	auto user_service = UserService::get();
	if (user_service == nullptr) {
		printf("nullptr");
		return 1;
	}
	user_service->add_user(User { 0, "Maarten" });
	user_service->print();
	// delete user_service;
	authenticate(0);
	return 0;
}
