/*******************************************************************
 * @file   Logger.hpp
 * @brief  Logger class for handling log messages.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/
#pragma once

#include <format>

#include "Types.hpp"

namespace uranium::core {

  enum class LogLevel {
    INFO = 0,  // Informational messages, general progress or state updates
    DEBUG,     // Debugging messages, used for development and troubleshooting
    WARN,   // Warning messages, indicating potential issues that are not errors
    TRACE,  // Trace-level messages, useful for detailed flow tracking
    ERROR,  // Error messages, issues that could lead to incorrect behavior
    FATAL,  // Fatal messages, critical errors that cause application to crash
    COUNT
  };

  enum class LogCategory {
    NONE = 0,     // No specific category, used for unclassified logs
    SYSTEM,       // Logs for system-level operations
    ENGINE,       // Core engine-level logs
    APPLICATION,  // General application-level logs
    INPUT,        // Logs for input handling
    MEMORY,       // Logs for memory management
    RESOURCE,     // Logs related to resource loading and management
    RENDERER,     // Logs related to rendering and graphics
    SHADER,       // Logs related to shader compilation or usage
    UNKNOWN,      // Fallback for unclassified logs
    COUNT
  };

  class Logger final {
  public:
    /**
     * @brief Logs a message to the console with color formatting.
     *
     * @param lvl - Log level (e.g., INFO, DEBUG, ERROR).
     * @param msg - Message to log, can be a format string.
     */
    static void cout(LogLevel lvl, std::string_view msg) noexcept;

    /**
     * @brief Logs a message to a file.
     *
     * @param lvl - Log level (e.g., INFO, DEBUG, ERROR).
     * @param fmt - Message to log, can be a format string.
     */
    static void fout(LogLevel lvl, std::string_view msg) noexcept;

    /**
     * @brief Logs a message to the console with color formatting.
     *
     * @param lvl - Log level (e.g., INFO, DEBUG, ERROR).
     * @param cat - Log category (e.g., SYSTEM, ENGINE).
     * @param msg - Message to log, can be a format string.
     */
    static void cout(LogLevel lvl, LogCategory cat,
                     std::string_view msg) noexcept;

    /**
     * @brief Logs a message to a file.
     *
     * @param lvl - Log level (e.g., INFO, DEBUG, ERROR).
     * @param cat - Log category (e.g., SYSTEM, ENGINE).
     * @param fmt - Message to log, can be a format string.
     */
    static void fout(LogLevel lvl, LogCategory cat,
                     std::string_view msg) noexcept;

  private:
    static std::string_view toString(LogLevel level) noexcept;
    static std::string_view toString(LogCategory category) noexcept;
    static std::string_view toColorString(LogLevel level) noexcept;
  };

/*
 * Evaluate these macros in debug configuration ONLY
 */
#if defined(UR_DEBUG)
  /*
   * @brief Debugging message, used for development and troubleshooting.
   *
   */
  #define UR_DEB(cat, msg, ...) \
    cout(LogLevel::DEBUG, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief An error occurred. The program may need to handle this.
   *
   */
  #define UR_ERROR(cat, msg, ...) \
    cout(LogLevel::ERROR, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief Application cannot continue, must close program entirely.
   *
   */
  #define UR_FATAL(cat, msg, ...) \
    cout(LogLevel::FATAL, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief Provides information to the client through the console.
   *
   */
  #define UR_INFO(cat, msg, ...) \
    cout(LogLevel::INFO, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief Provides detailed trace information.
   *
   */
  #define UR_TRACE(cat, msg, ...) \
    cout(LogLevel::TRACE, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief A warning occurred, but the program can continue.
   *
   */
  #define UR_WARN(cat, msg, ...) \
    cout(LogLevel::WARN, cat, std::format(msg, __VA_ARGS__))

#elif defined(UR_RELEASE)
  /*
   * @brief An error occurred. The program may need to handle this.
   *        Writes to a log file the error.
   *
   */
  #define UR_ERROR(cat, msg, ...) \
    fout(LogLevel::ERROR, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief Application cannot continue, must close program entirely
   *        Writes to a log file the fatal error.
   */
  #define UR_FATAL(cat, msg, ...) \
    fout(LogLevel::FATAL, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief Provides information to the client.
   *
   */
  #define UR_INFO(cat, msg, ...) \
    fout(LogLevel::INFO, cat, std::format(msg, __VA_ARGS__))

  #define UR_TRACE(cat, msg, ...) /*Nothing*/
  #define UR_WARN(cat, msg, ...)  /*Nothing*/

#elif defined(UR_DIST)
  /*
   * @brief An error occurred. The program may need to handle this.
   *        Error gets written into a log file.
   *
   */
  #define UR_ERROR(cat, msg, ...) \
    fout(LogLevel::ERROR, cat, std::format(msg, __VA_ARGS__))

  /*
   * @brief Application cannot continue, must close program entirely.
   *        Fatal error gets written into a log file.
   *
   */
  #define UR_FATAL(cat, msg, ...) \
    fout(LogLevel::FATAL, cat, std::format(msg, __VA_ARGS__))

  #define UR_INFO(cat, msg, ...)  /*Nothing*/
  #define UR_TRACE(cat, msg, ...) /*Nothing*/
  #define UR_WARN(cat, msg, ...)  /*Nothing*/

  #define UR_ASSERT(condition, cat, msg)   /*Nothing*/
  #define UR_STATIC_ASSERT(condition, msg) /*Nothing*/

#endif
}  // namespace uranium::core
