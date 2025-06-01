#include <iostream>

#include "uranium/core/AppEntry.hpp"
#include "uranium/core/Logger.hpp"

using namespace uranium::core;

class MyApplication : public uranium::core::IApp {
public:
  MyApplication() noexcept {
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