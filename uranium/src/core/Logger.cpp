#include "uranium/core/Logger.hpp"

#include <cstdint>
#include <print>

using namespace uranium::core;

static enum class TextColor {
  BLACK = 0,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  COUNT
};

#define TO_INT(x) static_cast<uint32_t>(x)

static std::string_view color_codes[TO_INT(TextColor::COUNT)] = {
    "\033[0;30m",  // BLACK
    "\033[0;31m",  // RED
    "\033[0;32m",  // GREEN
    "\033[0;33m",  // YELLOW
    "\033[0;34m",  // BLUE
    "\033[0;35m",  // MAGENTA
    "\033[0;36m",  // CYAN
    "\033[0;37m"   // WHITE
};

inline std::string_view Logger::toString(LogLevel level) noexcept {
  switch (level) {
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::DEBUG:
      return "DEBUG";
    case LogLevel::WARN:
      return "WARN";
    case LogLevel::TRACE:
      return "TRACE";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::FATAL:
      return "FATAL";
    default:
      return "UNKNOWN";
  }
}

inline std::string_view Logger::toString(LogCategory category) noexcept {
  switch (category) {
    case LogCategory::SYSTEM:
      return "[SYSTEM]";
    case LogCategory::APPLICATION:
      return "[APP]";
    case LogCategory::ENGINE:
      return "[ENGINE]";
    case LogCategory::INPUT:
      return "[INPUT]";
    case LogCategory::MEMORY:
      return "[MEMORY]";
    case LogCategory::RESOURCE:
      return "[RESOURCE]";
    case LogCategory::RENDERER:
      return "[RENDERER]";
    case LogCategory::SHADER:
      return "[SHADER]";
    default:
      return "";
  }
}

inline std::string_view Logger::toColorString(LogLevel level) noexcept {
  switch (level) {
    case LogLevel::INFO:
      return color_codes[TO_INT(TextColor::YELLOW)];
    case LogLevel::DEBUG:
      return color_codes[TO_INT(TextColor::BLUE)];
    case LogLevel::WARN:
      return color_codes[TO_INT(TextColor::MAGENTA)];
    case LogLevel::TRACE:
      return color_codes[TO_INT(TextColor::GREEN)];
    case LogLevel::ERROR:
    case LogLevel::FATAL:
      return color_codes[TO_INT(TextColor::RED)];
    default:
      return color_codes[TO_INT(TextColor::WHITE)];
  }
}

void Logger::cout(LogLevel lvl, std::string_view msg) noexcept {
  Logger::cout(lvl, LogCategory::NONE, msg);
}

void Logger::fout(LogLevel lvl, std::string_view msg) noexcept {
  Logger::fout(lvl, LogCategory::NONE, msg);
}

void Logger::cout(LogLevel lvl, LogCategory cat,
                  std::string_view msg) noexcept {
  // Obtain color codes for the log level and category
  std::string_view back_color = color_codes[TO_INT(TextColor::WHITE)];
  std::string_view front_color = toColorString(lvl);

  if (lvl == LogLevel::ERROR || lvl == LogLevel::FATAL) {
    // For ERROR and FATAL, make the entire message red
    std::println("{}[{:<5}] {} {} {}",
                 front_color,    // Start color
                 toString(lvl),  // Log level
                 toString(cat),  // Log category
                 msg,            // Log message
                 back_color      // Ensure colors are reset
    );
  } else {
    // Standard formatting for other log levels
    std::println("{}[{:<5}]{} {} {} {}",
                 front_color,    // Start color
                 toString(lvl),  // Log level
                 back_color,     // End color
                 toString(cat),  // Log category
                 msg,            // Log message
                 back_color      // Ensure colors are reset
    );
  }
}

void Logger::fout(LogLevel lvl, LogCategory cat,
                  std::string_view msg) noexcept {}
