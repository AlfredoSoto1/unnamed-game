/*******************************************************************
 * @file   Utils.h
 * @brief  Basic macro-function implementation.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/

#pragma once

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
  #define UR_PLATFORM_WINDOWS
#elif defined(__linux__)
  #define UR_PLATFORM_LINUX
#endif

// Compiler detection
#if defined(_MSC_VER)
  #define UR_MSVC_COMPILER
#elif defined(__GNUC__)
  #define UR_GCC_COMPILER
#endif

#if defined(UR_DEBUG)
  /*
   * @brief Defines the debug-breakpoint macro depending on the selected
   *        platform.
   */
  #if defined(UR_PLATFORM_WINDOWS) && defined(UR_MSVC_COMPILER)
    #define UR_DEBUG_BREAK() __debugbreak()
  #elif defined(UR_PLATFORM_LINUX) && defined(UR_GCC_COMPILER)
    #define UR_DEBUG_BREAK() __builtin_debugtrap()
  #else
    #define UR_DEBUG_BREAK()
  #endif

  /**
   * @brief Injects code into source code in compile-time only on debug.
   *
   * UR_IF            - Inserts a conditional check.
   * UR_IF_END        - Ends the if conditional block.
   * UR_ON_DEBUG      - Inserts a statement
   * UR_ON_DEBUG_SWAP - Swaps the statement when debug configuration is no
   *                    longer selected.
   */
  #define UR_IF(condition) if (condition) {
  #define UR_IF_END }
  #define UR_ON_DEBUG(statement) statement
  #define UR_ON_DEBUG_SWAP(debug_statement, default_statement) debug_statement

  /*
   * @brief Does an assert at runtime that triggers the debug
   *        breakpoint and logs an error message.
   *
   * @param condition - establishes if it should do an assert
   */
  #define UR_ASSERT(condition) \
    if (condition) {           \
      UR_DEBUG_BREAK();        \
    }

  /*
   * @brief Does a static assert before running (compilation).
   *
   * @param condition - establishes if it should do an assert
   * @param message   - displays the message of the assertion
   */
  #define UR_STATIC_ASSERT(condition, message) \
    {                                          \
      static_assert(!condition, message);      \
    }
#else
  #define UR_DEBUG_BREAK()

  #define UR_IF(condition)
  #define UR_IF_END
  #define UR_ON_DEBUG(statement)
  #define UR_ON_DEBUG_SWAP(debug_statement, release_statement) release_statement

  #define UR_ASSERT(condition, type, message)
  #define UR_STATIC_ASSERT(condition, message)
#endif

/*
 * @brief Binds a class member function to an `std::function`.
 *        The `std::bind` function is used to bind a member function to an
 *        object and its arguments. This allows the member function to be passed
 *        around as a callable.
 */
#define UR_METHOD(class_function, ...) \
  std::bind(&class_function, this, __VA_ARGS__)

/**
 * @brief Macro to create a bitmask for a given activation bit.
 *        The macro shifts the number 1 to the left by `activation_bit`
 *        positions to generate a single-bit mask at that position. The result
 *        is AND-ed with UINT32_MAX to ensure the value fits within 32 bits.
 *
 * Example:
 * UR_BIT(0) => 0x00000001 (bit 0 is set)
 * UR_BIT(1) => 0x00000002 (bit 1 is set)
 * UR_BIT(31) => 0x80000000 (bit 31 is set)
 *
 * Use Case:
 * Useful for defining bit flags in enums or for managing feature flags.
 */
#define UR_BIT(activation_bit) ((1U << activation_bit) & UINT32_MAX)