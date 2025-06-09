#include "uranium/core/IMonitor.hpp"

#include <GLFW/glfw3.h>

using namespace uranium::core;

void uranium::core::callback(GLFWmonitor* monitor, int event) {
  IMonitor* imonitor = (IMonitor*)glfwGetMonitorUserPointer(monitor);
  imonitor->is_connected = event == GLFW_CONNECTED;
}

IMonitor::IMonitor(GLFWmonitor* monitor) noexcept
    : monitor(monitor), is_connected(true) {
  glfwSetMonitorCallback(callback);
  glfwSetMonitorUserPointer(monitor, this);
}

bool IMonitor::isConnected() const { return is_connected; }

uint32_t IMonitor::getRefreshrate() const {
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  return mode->refreshRate;
}

void IMonitor::getResolution(uint32_t* width, uint32_t* height) const {
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  if (width) *width = mode->width;
  if (height) *height = mode->height;
}

IMonitor::operator GLFWmonitor*() const { return monitor; }