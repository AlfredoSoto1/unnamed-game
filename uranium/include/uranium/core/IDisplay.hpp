/*********************************************************************
 * @file   IDisplay.hpp
 * @brief  Interface for display/window management.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/

#pragma once

#include <string>

#include "Types.hpp"

namespace uranium::core {

  class IMonitor;

  /**
   * @class Display
   *
   * @brief Represents a system's display or window, encapsulating properties
   *        such as resolution, mode, and visual configurations.
   */
  UR_ABSTRACT_CLASS IDisplay {
  public:
    /**
     * @enum Resolution
     *
     * @brief Predefined resolutions for display configurations.
     */
    enum class Resolution {
      R_800x600,
      R_1024x768,
      R_1280x720,
      R_1920x1080,
      R_2560x1440,
      R_3840x2160,
      R_CUSTOM,
    };

    /**
     * @enum Mode
     *
     * @brief Available display modes for the window or screen.
     */
    enum class Mode {
      WINDOWED,
      MINIMIZED,
      MAXIMIZED,
      BORDERLESS,
      FULLSCREEN,
    };

    /**
     * @struct Properties
     *
     * @brief A structure to store display properties and configurations.
     */
    struct Properties final {
      std::string title;
      std::string icon_path;

      uint32_t width = 800;
      uint32_t height = 600;
      uint8_t opacity = 255;
      Mode mode = Mode::WINDOWED;
      Resolution resolution = Resolution::R_800x600;

      int32_t xposition = 0;
      int32_t yposition = 0;
      uint32_t antialiasingLevel = 1;

      bool vsync = true;
      bool visible = true;
      bool resizable = true;
    };

  public:
    /**
     * @brief Default properties for the display.
     *        This can be used to initialize a display with standard settings.
     */
    static const Properties DEFAULT;

    /**
     * @brief Constructor for IDisplay.
     * @param properties Configuration properties for the display.
     * @param smonitor A reference to the Monitor for system-specific
     *        operations.
     */
    explicit IDisplay(const Properties& properties,
                      const IMonitor& smonitor) noexcept;
    virtual ~IDisplay() = default;

    /**
     * @brief Closes and cleans up the display.
     *        This must be implemented by derived classes.
     */
    virtual void close() = 0;

    /**
     * @brief Reloads the display.
     * @param properties New properties for the display.
     */
    virtual void reload(const Properties& properties) = 0;

    /**
     * @brief Updates the display's title.
     * @param title New title for the display.
     */
    virtual void setTitle(const std::string& title) = 0;

    /**
     * @brief Updates the display's icon.
     * @param icon_path Path to the new icon.
     */
    virtual void setIcon(const std::string& icon_path) = 0;

    /**
     * @brief Resizes the display to the given dimensions.
     * @param width New width of the display.
     * @param height New height of the display.
     */
    virtual void resize(uint32_t width, uint32_t height) = 0;

    /**
     * @brief Sets the display mode (e.g., windowed, fullscreen).
     * @param monitor
     * @param mode New mode for the display.
     */
    virtual void setMode(IMonitor * monitor, Mode mode) = 0;

    /**
     * @brief Sets the display resolution.
     * @param resolution New resolution for the display.
     */
    virtual void setResolution(Resolution resolution) = 0;

    /**
     * @brief Sets the display resolution.
     * @param width
     * @param height
     */
    virtual void setResolution(uint32_t width, uint32_t height) = 0;

    /**
     * @brief Sets the opacity level of the display.
     * @param opacity Opacity level (0-255).
     */
    virtual void setOpacity(uint8_t opacity) = 0;

    /**
     * @brief Sets the visibility of the display.
     * @param visible True to show the display, false to hide it.
     */
    virtual void setVisible(bool visible) = 0;

    /**
     * @brief Sets the display's position on the screen.
     * @param xpos X-coordinate of the new position.
     * @param ypos Y-coordinate of the new position.
     */
    virtual void setPosition(int32_t xpos, int32_t ypos) = 0;

    /**
     * @brief Centers the window onto a given monitor.
     *
     * @param monitor
     */
    virtual void center(const IMonitor& monitor) = 0;

    /**
     * @brief Sets the anti-aliasing level for rendering.
     * @param antialias_level New anti-aliasing level.
     */
    virtual void setAntialiasLevel(uint32_t antialias_level) = 0;

    /**
     * @brief Enables or disables V-Sync.
     * @param enable True to enable, false to disable.
     */
    virtual void enableVsync(bool enable) = 0;

    /**
     * @brief Focuses the display window.
     */
    virtual void focus() = 0;

    /**
     * @brief Restores the display to its original state (e.g., from minimized).
     */
    virtual void restore() = 0;

    /**
     * @brief Requests attention (e.g., flashes the display icon).
     */
    virtual void requestAttention() = 0;

    /**
     * @brief Gets the current width of the display.
     * @return The width of the display in pixels.
     */
    uint32_t getWidth() const;

    /**
     * @brief Gets the current height of the display.
     * @return The height of the display in pixels.
     */
    uint32_t getHeight() const;

    /**
     * @brief Get the Aspect Ratio of the display.
     *
     * @return uint32_t
     */
    float getAspectRatio() const;

    /**
     * @brief Gets the current position of the display on the screen.
     * @param xpos Pointer to store the X-coordinate.
     * @param ypos Pointer to store the Y-coordinate.
     */
    void getPosition(int32_t* xpos, int32_t* ypos) const;

    /**
     * @brief Gets the current mode of the display.
     * @return The current display mode.
     */
    Mode getMode() const;

    /**
     * @brief Gets the current resolution of the display.
     * @return The current display resolution.
     */
    Resolution getResolution() const;

    /**
     * @brief Checks if the display has been successfully initialized.
     * @return True if initialized, false otherwise.
     */
    bool hasInitialized() const;

  protected:
    bool initialized;
    Properties properties;
  };
}  // namespace uranium::core