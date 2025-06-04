/*********************************************************************
 * @file   Api.hpp
 * @brief  Platform-specific definitions and macros.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/

#pragma once

// Platform definitions
#if defined(_WIN32) || defined(_WIN64)
  #define UR_PLATFORM_WINDOWS
#elif defined(__linux__)
  #define UR_PLATFORM_LINUX
#else
  #error Uranium Engine only supports Windows and Linux platforms.
#endif

// Compiler checks
#if defined(_MSC_VER)
  #define UR_MSVC_COMPILER
#elif defined(__GNUC__) || defined(__clang__)
  #define UR_GCC_COMPILER
#else
  #error Uranium Engine only supports MSVC, GCC, or Clang compilers.
#endif

// Platform and compiler-specific configurations for DLL import/export.
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
 *   applied.
 */
#if defined(UR_BUILD_DLL)
  #define URANIUM_API UR_EXPORT_DLL
#elif defined(UR_USE_DLL)
  #define URANIUM_API UR_IMPORT_DLL
#else
  #define URANIUM_API
#endif