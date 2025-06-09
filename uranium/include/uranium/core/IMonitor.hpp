/*******************************************************************
 * @file   IMonitor.hpp
 * @brief  Interface for monitor-related functionality.
 *
 * @author Alfredo
 * @date   May 2025
 *******************************************************************/
#pragma once

#include "Types.hpp"

struct GLFWmonitor;

namespace uranium::platform::windows {
  UR_DECLARE OpenGLApp;
}

namespace uranium::core {

  UR_ABSTRACT_CLASS IMonitor final {
  public:
    IMonitor(const IMonitor&) = delete;
    IMonitor& operator=(const IMonitor&) = delete;

  public:
    /**
     * @brief Checks if the monitor is connected.
     *
     * @return true if the monitor is connected, false otherwise.
     */
    bool isConnected() const;

    /**
     * @brief Get the Refreshrate object
     *
     * @return uint32_t
     */
    uint32_t getRefreshrate() const;

    /**
     * @brief Get the Resolution object
     *
     * @param width
     * @param height
     */
    void getResolution(uint32_t* width, uint32_t* height) const;

    /**
     * @brief Overload for the cast operator
     *
     * @return GLFWmonitor*
     */
    operator GLFWmonitor*() const;

  private:
    explicit IMonitor(GLFWmonitor * monitor) noexcept;

  private:
    friend platform::windows::OpenGLApp;
    friend void callback(GLFWmonitor * monitor, int event);

  private:
    bool is_connected;
    GLFWmonitor* monitor;
  };

}  // namespace uranium::core