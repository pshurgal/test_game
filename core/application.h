#pragma once

#include <memory>

class Application
{
public:
    Application();
    ~Application();

    int exec();

private:
    class impl;
    std::unique_ptr<Application::impl> _impl;
};
