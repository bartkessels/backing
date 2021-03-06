#include "domain/Listener.hpp"

using namespace backing::domain;

void Listener::registerMethod(const std::string& name, const std::shared_ptr<Response>& response)
{
    methods.insert_or_assign(name, response);
}

void Listener::unregisterMethod(const std::string& name)
{
    const auto& it = methods.find(name);

    if (it != methods.end()) {
        methods.erase(it);
    }
}

void Listener::setLogger(const std::shared_ptr<Logger>& logger)
{
    this->logger = logger;
}

void Listener::start(const std::string& uri)
{
    if (!validateUri(uri)) throw exception::InvalidUriException(uri);
    if (listenerStarted) throw exception::ListenerAlreadyStartedException(uri);

    listenerStarted = startListener(uri);
}

void Listener::stop()
{
    if (!listenerStarted) throw exception::ListenerNotStartedException();

    stopListener();
    listenerStarted = false;
}

std::shared_ptr<Response> Listener::getResponse(const std::string& method)
{
    const auto& it = methods.find(method);

    if (it == methods.end()) {
        throw exception::MethodNotRegisteredException(method);
    }

    return it->second;
}

void Listener::log(const std::string& message)
{
    if (logger != nullptr) {
        logger->log(message);
    }
}

bool Listener::validateUri(const std::string& uri)
{
    return std::regex_match(uri, std::regex("^(?:http://)?([^/]+)(?:/?.*/?)/(.*)$"));
}