#include "uranium/platform/windows/OpenGLApp.hpp"

#include <GLFW/glfw3.h>

#include <stdexcept>

#include "uranium/core/IMonitor.hpp"
#include "uranium/core/Logger.hpp"

using namespace uranium::core;
using namespace uranium::platform::windows;

OpenGLApp::OpenGLApp() noexcept : IApp() {}

const IMonitor* OpenGLApp::primaryMonitor() {
  // If no monitor is available, create a new reference
  // pointing to the primary monitor.
  if (!monitor) {
    monitor = std::unique_ptr<IMonitor>(new IMonitor(glfwGetPrimaryMonitor()));
  }
  return monitor.get();
}

const IMonitor* OpenGLApp::selectMonitor(uint32_t selection) {
  // Obtain the monitors that the application has scoped
  int count;
  GLFWmonitor** monitor_devices = glfwGetMonitors(&count);

  // Check if the selection doesn't go off
  if (selection > count) {
    Logger::UR_ERROR(LogCategory::APPLICATION,
                     "Monitor selection is out of bounds.");
    return nullptr;
  }

  monitor.reset();

  // Replace the previous monitor reference
  monitor = std::unique_ptr<IMonitor>(new IMonitor(monitor_devices[selection]));

  return monitor.get();
}