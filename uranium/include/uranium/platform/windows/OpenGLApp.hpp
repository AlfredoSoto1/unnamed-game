/*********************************************************************
 * @file   OpenGLApp.hpp
 * @brief  Interface for Windows platform-specific functionality.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/
#pragma once

#include "uranium/core/App.hpp"

namespace uranium::platform::windows {

  UR_ABSTRACT_CLASS OpenGLApp : UR_EXTENDS core::IApp {
  public:
    explicit OpenGLApp() noexcept;

    /**
     * @brief Provides the primary monitor.
     *
     * @return const IMonitor*
     */
    const core::IMonitor* primaryMonitor() override;

    /**
     * @brief Changes all settings related to a monitor to the one being
     *        selected.
     *
     * @return const IMonitor*
     */
    const core::IMonitor* selectMonitor(uint32_t selection) override;
  };

}  // namespace uranium::platform::windows