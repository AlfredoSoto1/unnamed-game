#include <chrono>
#include <iostream>
#include <vector>

#include "uranium/core/AppEntry.hpp"
#include "uranium/core/Logger.hpp"
#include "uranium/event/EventDispatcher.hpp"  // FOR TEST
#include "uranium/platform/windows/OpenGLApp.hpp"

using namespace std::chrono;
using namespace uranium::event;

using namespace uranium::core;
using namespace uranium::platform::windows;

void test_EventManager() {
  struct TestEvent : public IEvent {
    TestEvent() : IEvent(9999) {}  // Use a custom event type
  };
}

class MyApplication final : public OpenGLApp {
public:
  MyApplication() noexcept : OpenGLApp() {
    std::cout << "MyApplication initialized" << std::endl;

    test_EventManager();
  }

  ~MyApplication() noexcept override {
    std::cout << "MyApplication destroyed" << std::endl;
  }
};

std::unique_ptr<uranium::core::IApp> uranium::core::launchApp(
    std::vector<std::string>& args) {
  return std::make_unique<MyApplication>();
}