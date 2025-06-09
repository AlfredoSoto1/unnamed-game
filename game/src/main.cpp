#include <iostream>

#include "uranium/core/AppEntry.hpp"
#include "uranium/core/Logger.hpp"
#include "uranium/platform/windows/OpenGLApp.hpp"

using namespace uranium::core;
using namespace uranium::platform::windows;

class MyApplication final : public OpenGLApp {
public:
  MyApplication() noexcept : OpenGLApp() {
    std::cout << "MyApplication initialized" << std::endl;
  }

  ~MyApplication() noexcept override {
    std::cout << "MyApplication destroyed" << std::endl;
  }
};

std::unique_ptr<uranium::core::IApp> uranium::core::launchApp(
    std::vector<std::string>& args) {
  return std::make_unique<MyApplication>();
}