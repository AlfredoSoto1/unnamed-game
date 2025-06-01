/*********************************************************************
 * @file   Platform.h
 * @brief  Platform-specific definitions and macros.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/

#pragma once

#include <string>

#include "Types.hpp"

// Platform definitions
#if defined(_WIN32) || defined(_WIN64)
  #define UR_PLATFORM_WINDOWS  // Define for Windows platform
#elif defined(__linux__)
  #define UR_PLATFORM_LINUX  // Define for Linux platform
#else
  #error Uranium Engine only supports Windows and Linux platforms.
#endif

// Compiler checks
#if defined(_MSC_VER)
  #define UR_MSVC_COMPILER  // Define for MSVC compiler
#elif defined(__GNUC__) || defined(__clang__)
  #define UR_GCC_COMPILER  // Define for GCC/Clang compiler
#else
  #error Uranium Engine only supports MSVC, GCC, or Clang compilers.
#endif

/*
 * Platform and compiler-specific configurations for DLL import/export.
 * - On Windows, only MSVC is supported with `__declspec(dllexport)` and
 * `__declspec(dllimport)`.
 * - On Linux, only GCC/Clang is supported with `__attribute__` for visibility
 * control.
 */
#if defined(UR_PLATFORM_WINDOWS)
  #if defined(UR_MSVC_COMPILER)
    // MSVC-specific definitions for DLL export/import
    #define UR_EXPORT_DLL __declspec(dllexport)
    #define UR_IMPORT_DLL __declspec(dllimport)
  #else
    #error Uranium Engine requires MSVC on Windows.
  #endif
#elif defined(UR_PLATFORM_LINUX)
  #if defined(UR_GCC_COMPILER)
  // GCC/Clang-specific definitions for DLL export/import
    #define UR_EXPORT_DLL __attribute__((visibility("default")))
    #define UR_IMPORT_DLL __attribute__((visibility("hidden")))
  #else
    #error Uranium Engine requires GCC or Clang on Linux.
  #endif
#endif

/*
 * API linking macros.
 * These macros define how the Uranium Engine API is linked:
 * - `UR_BUILD_DLL`: When building the Uranium Engine DLL, export the symbols.
 * - `UR_USE_DLL`: When using the Uranium Engine DLL, import the symbols.
 * - If neither is defined, the API is treated as static and no import/export is
 * applied.
 */
#if defined(UR_BUILD_DLL)
  #define URANIUM_API UR_EXPORT_DLL
#elif defined(UR_USE_DLL)
  #define URANIUM_API UR_IMPORT_DLL
#else
  #define URANIUM_API
#endif

namespace uranium::platform {

  class Monitor;

  /**
   * @class Display
   *
   * @brief Represents a system's display or window, encapsulating properties
   *        such as resolution, mode, and visual configurations.
   */
  UR_ABSTRACT_CLASS Display {
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
      uint32_t opacity = 100;
      Mode mode = Mode::WINDOWED;
      Resolution resolution = Resolution::R_800x600;

      uint32_t xposition = 0;
      uint32_t yposition = 0;
      uint32_t antialiasingLevel = 1;

      bool vsync = true;
      bool resizable = true;
      bool transparent = false;
    };

    /**
     * @brief Default properties for the display.
     *        This can be used to initialize a display with standard settings.
     */
    static const Properties DEFAULT;

    /**
     * @brief Constructor for Display.
     * @param properties Configuration properties for the display.
     * @param smonitor A reference to the Monitor for system-specific
     * operations.
     */
    explicit Display(const Properties& properties,
                     const Monitor& smonitor) noexcept;
    virtual ~Display() = default;

    /**
     * @brief Initializes the display.
     *        This must be implemented by derived classes.
     */
    virtual void init() = 0;

    /**
     * @brief Closes and cleans up the display.
     *        This must be implemented by derived classes.
     */
    virtual void close() = 0;

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
     * @param mode New mode for the display.
     */
    virtual void setMode(Mode mode) = 0;

    /**
     * @brief Sets the display resolution.
     * @param resolution New resolution for the display.
     */
    virtual void setResolution(Resolution resolution) = 0;

    /**
     * @brief Sets the opacity level of the display.
     * @param opacity Opacity level (0-100).
     */
    virtual void setOpacity(uint32_t opacity) = 0;

    /**
     * @brief Sets the display's position on the screen.
     * @param xpos X-coordinate of the new position.
     * @param ypos Y-coordinate of the new position.
     */
    virtual void setPosition(uint32_t xpos, uint32_t ypos) = 0;

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
     * @brief Enables or disables resizing of the display.
     * @param enable True to enable, false to disable.
     */
    virtual void enableResize(bool enable) = 0;

    /**
     * @brief Enables or disables transparency of the display.
     * @param enable True to enable, false to disable.
     */
    virtual void enableTransparency(bool enable) = 0;

    /**
     * @brief Focuses the display window.
     */
    virtual void focus() = 0;

    /**
     * @brief Restores the display to its original state (e.g., from minimized).
     */
    virtual void restore() = 0;

    /**
     * @brief Temporarily "loses" attention from the display.
     */
    virtual void loseAttention() = 0;

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
     * @brief Gets the current position of the display on the screen.
     * @param xpos Pointer to store the X-coordinate.
     * @param ypos Pointer to store the Y-coordinate.
     */
    void getPosition(uint32_t* xpos, uint32_t* ypos) const;

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
    Properties properties;
    bool initialized;
  };
}  // namespace uranium::platform