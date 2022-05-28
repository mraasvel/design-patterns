#include <unordered_map>

using std::unordered_map;

class IService {
public:
	virtual IService* clone() = 0;
	virtual ~IService() {};
};

class FactoryService {
public:
	enum ServiceType {
		USER_SERVICE,
	};

private:

	FactoryService();

public:
	~FactoryService();

	IService* build(ServiceType type);

	static FactoryService* get();

private:
	unordered_map<ServiceType, IService*> services;
	static FactoryService* factory_service;
};
