/*********************************************************************
 * @file   OpenGLDisplay.hpp
 * @brief  Interface for Windows platform-specific functionality.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/
#pragma once

#include "uranium/core/IDisplay.hpp"

struct GLFWwindow;

namespace uranium::platform::windows {

  UR_ABSTRACT_CLASS OpenGLDisplay final : UR_EXTENDS core::IDisplay {
  public:
    /**
     * @brief Constructor for OpenGLDisplay.
     * @param properties Configuration properties for the display.
     * @param smonitor A reference to the Monitor for system-specific
     *        operations.
     */
    explicit OpenGLDisplay(const core::IDisplay::Properties& properties,
                           const core::Monitor& smonitor) noexcept;

    /**
     * @brief Closes and cleans up the GLFW window.
     */
    virtual void close() override;

    /**
     * @brief Reloads the display.
     * @param properties New properties for the display.
     */
    virtual void reload(const core::IDisplay::Properties& properties) override;

    /**
     * @brief Updates the display's title.
     * @param title New title for the display.
     */
    virtual void setTitle(const std::string& title) override;

    /**
     * @brief Updates the display's icon.
     * @param icon_path Path to the new icon.
     */
    virtual void setIcon(const std::string& icon_path) override;

    /**
     * @brief Resizes the display to the given dimensions.
     * @param width New width of the display.
     * @param height New height of the display.
     */
    virtual void resize(uint32_t width, uint32_t height) override;

    /**
     * @brief Sets the display mode (e.g., windowed, fullscreen).
     * @param mode New mode for the display.
     */
    virtual void setMode(Mode mode) override;

    /**
     * @brief Sets the display resolution.
     * @param resolution New resolution for the display.
     */
    virtual void setResolution(Resolution resolution) override;

    /**
     * @brief Sets the display resolution.
     * @param width
     * @param height
     */
    virtual void setResolution(uint32_t width, uint32_t height) override;

    /**
     * @brief Sets the opacity level of the display.
     * @param opacity Opacity level (0-255).
     */
    virtual void setOpacity(uint8_t opacity) override;

    /**
     * @brief Sets the visibility of the display.
     * @param visible True to show the display, false to hide it.
     */
    virtual void setVisible(bool visible) override;

    /**
     * @brief Sets the display's position on the screen.
     * @param xpos X-coordinate of the new position.
     * @param ypos Y-coordinate of the new position.
     */
    virtual void setPosition(uint32_t xpos, uint32_t ypos) override;

    /**
     * @brief Sets the anti-aliasing level for rendering.
     * @param antialias_level New anti-aliasing level.
     */
    virtual void setAntialiasLevel(uint32_t antialias_level) override;

    /**
     * @brief Enables or disables V-Sync.
     * @param enable True to enable, false to disable.
     */
    virtual void enableVsync(bool enable) override;

    /**
     * @brief Focuses the display window.
     */
    virtual void focus() override;

    /**
     * @brief Restores the display to its original state (e.g., from minimized).
     */
    virtual void restore() override;

    /**
     * @brief Requests attention (e.g., flashes the display icon).
     */
    virtual void requestAttention() override;

  private:
    GLFWwindow* glfwWindow;
  };

}  // namespace uranium::platform::windows