#include "uranium/platform/windows/OpenGLDisplay.hpp"

#include <GLFW/glfw3.h>

#include "uranium/core/IMonitor.hpp"
#include "uranium/core/Logger.hpp"

using namespace uranium::core;
using namespace uranium::platform::windows;

OpenGLDisplay::OpenGLDisplay(const core::IDisplay::Properties& properties,
                             const core::IMonitor& smonitor) noexcept
    : core::IDisplay(properties, smonitor) {
  if (!glfwInit()) {
    Logger::UR_FATAL(LogCategory::ENGINE,
                     "Failed to initialize GLFW for OpenGL.");
    std::terminate();
  }

  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  glfwWindowHint(GLFW_VISIBLE, properties.visible ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, properties.resizable ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_DECORATED,
                 properties.mode != Mode::BORDERLESS ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,
                 properties.opacity < 255 ? GL_TRUE : GL_FALSE);

  // glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

  glfwWindow = glfwCreateWindow(properties.width, properties.height,
                                properties.title.c_str(), nullptr, nullptr);

  if (!glfwWindow) {
    Logger::UR_FATAL(LogCategory::ENGINE, "Failed to create GLFW window.");
    glfwTerminate();
    std::terminate();
  }

  glfwMakeContextCurrent(glfwWindow);
  if (properties.vsync) {
    glfwSwapInterval(1);
  }
}

void OpenGLDisplay::close() {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot close OpenGL without a valid GLFW window.");
    return;
  }
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}

void OpenGLDisplay::reload(const Properties& properties) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot reload without a valid GLFW window.");
    return;
  }
}

void OpenGLDisplay::setTitle(const std::string& title) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot set title without a valid GLFW window.");
    return;
  }
  properties.title = title;
  glfwSetWindowTitle(glfwWindow, title.c_str());
}

void OpenGLDisplay::setIcon(const std::string& icon_path) {}

void OpenGLDisplay::resize(uint32_t width, uint32_t height) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot resize without a valid GLFW window.");
    return;
  }
  if (width == 0 || height == 0) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Invalid dimensions for resizing: {}x{}.", width, height);
    return;
  }
  properties.width = width;
  properties.height = height;
  glfwSetWindowSize(glfwWindow, width, height);
}

void OpenGLDisplay::setMode(IMonitor* monitor, Mode mode) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot set mode without a valid GLFW window.");
    return;
  }

  // If the current mode is FULLSCREEN, we need to restore the window
  // position and size before changing the mode.
  if (properties.mode == Mode::FULLSCREEN && mode != properties.mode) {
    glfwSetWindowMonitor(glfwWindow,
                         0,  // Use primary monitor if no monitor is specified
                         properties.xposition,  // Use current position
                         properties.yposition,  // Use current position
                         properties.width,      // Use current width
                         properties.height,     // Use current height
                         0);                    // No refresh rate specified
  }

  properties.mode = mode;

  switch (mode) {
    case Mode::WINDOWED:
      glfwSetWindowAttrib(glfwWindow, GLFW_DECORATED, GLFW_TRUE);
      glfwSetWindowAttrib(glfwWindow, GLFW_RESIZABLE,
                          properties.resizable ? GLFW_TRUE : GLFW_FALSE);
      glfwRestoreWindow(glfwWindow);
      break;
    case Mode::MINIMIZED:
      glfwIconifyWindow(glfwWindow);
      break;
    case Mode::MAXIMIZED:
      glfwMaximizeWindow(glfwWindow);
      break;
    case Mode::BORDERLESS:
      glfwSetWindowAttrib(glfwWindow, GLFW_DECORATED, GLFW_FALSE);
      glfwSetWindowAttrib(glfwWindow, GLFW_RESIZABLE, GLFW_FALSE);
      break;
    case Mode::FULLSCREEN:
      if (!monitor) {
        Logger::UR_ERROR(
            LogCategory::ENGINE,
            "Cannot set fullscreen without a monitor (must provide).");
        return;
      }

      glfwGetWindowPos(glfwWindow,              // glfw ptr
                       &properties.xposition,   // xpos
                       &properties.yposition);  // ypos

      glfwSetWindowMonitor(glfwWindow,         // glfw ptr
                           *monitor,           // GLFWmonitor
                           0, 0,               // position; zero default
                           properties.width,   // width
                           properties.height,  // height
                           0);
      break;
  }
}

void OpenGLDisplay::setResolution(Resolution resolution) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot set resolution without a valid GLFW window.");
    return;
  }

  switch (resolution) {
    case Resolution::R_800x600:
      properties.width = 800;
      properties.height = 600;
      break;
    case Resolution::R_1024x768:
      properties.width = 1024;
      properties.height = 768;
      break;
    case Resolution::R_1280x720:
      properties.width = 1280;
      properties.height = 720;
      break;
    case Resolution::R_1920x1080:
      properties.width = 1920;
      properties.height = 1080;
      break;
    case Resolution::R_2560x1440:
      properties.width = 2560;
      properties.height = 1440;
      break;
    case Resolution::R_3840x2160:
      properties.width = 3840;
      properties.height = 2160;
      break;
    default:
      Logger::UR_ERROR(LogCategory::ENGINE, "Invalid resolution specified: {}.",
                       "R_CUSTOM");
      return;
  }

  properties.resolution = resolution;
  glfwSetWindowSize(glfwWindow, properties.width, properties.height);
}

void OpenGLDisplay::setResolution(uint32_t width, uint32_t height) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot set resolution without a valid GLFW window.");
    return;
  }
  if (width == 0 || height == 0) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Invalid resolution dimensions: {}x{}.", width, height);
    return;
  }
  properties.width = width;
  properties.height = height;
  properties.resolution = Resolution::R_CUSTOM;
  glfwSetWindowSize(glfwWindow, width, height);
}

constexpr uint8_t clamp(uint8_t value, uint8_t min, uint8_t max) {
  return static_cast<uint8_t>((value < min)   ? min
                              : (value > max) ? max
                                              : value);
}

void OpenGLDisplay::setOpacity(uint8_t opacity) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE, "Invalid opacity value: {}.",
                     opacity);
    return;
  }
  opacity = clamp(opacity, 0u, 255u);
  properties.opacity = opacity;

  bool transparent = opacity < 255;

  glfwSetWindowAttrib(glfwWindow, GLFW_TRANSPARENT_FRAMEBUFFER,
                      transparent ? GLFW_TRUE : GLFW_FALSE);
  glfwSetWindowOpacity(glfwWindow, static_cast<float>(opacity) / 255.0f);
}

void OpenGLDisplay::setVisible(bool visible) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot set visibility without a valid GLFW window.");
    return;
  }
  properties.visible = visible;
  glfwSetWindowAttrib(glfwWindow, GLFW_VISIBLE,
                      visible ? GLFW_TRUE : GLFW_FALSE);
}

void OpenGLDisplay::setPosition(int32_t xpos, int32_t ypos) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot set position without a valid GLFW window.");
    return;
  }
  properties.xposition = xpos;
  properties.yposition = ypos;
  glfwSetWindowPos(glfwWindow, xpos, ypos);
}

void OpenGLDisplay::center(const IMonitor& monitor) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Cannot center display without a valid GLFW window.");
    return;
  }

  // Check if the display is capable of being centered
  if (properties.mode != Mode::BORDERLESS ||
      properties.mode != Mode::WINDOWED) {
    Logger::UR_WARN(LogCategory::ENGINE,
                    "Cannot center a non borderless/windowed display.");
    return;
  }

  // Get the monitor resolution, and calulate the center position
  uint32_t width, height;
  monitor.getResolution(&width, &height);
  setPosition((width - properties.width) / 2, (height - properties.height) / 2);
}

void OpenGLDisplay::setAntialiasLevel(uint32_t antialias_level) {}

void OpenGLDisplay::enableVsync(bool enable) {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "V-Sync cannot be enabled without a valid window.");
    return;
  }
  glfwSwapInterval(enable ? 1 : 0);
}

void OpenGLDisplay::focus() {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Focus cannot be set without a valid window.");
    return;
  }
  glfwFocusWindow(glfwWindow);
}

void OpenGLDisplay::restore() {
  if (!glfwWindow) {
    Logger::UR_ERROR(LogCategory::ENGINE,
                     "Restore cannot be performed without a valid window.");
    return;
  }
  glfwRestoreWindow(glfwWindow);
}

void OpenGLDisplay::requestAttention() {
  if (!glfwWindow) {
    Logger::UR_ERROR(
        LogCategory::ENGINE,
        "Request attention cannot be performed without a valid window.");
    return;
  }
  glfwRequestWindowAttention(glfwWindow);
}