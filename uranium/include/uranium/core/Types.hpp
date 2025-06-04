/*********************************************************************
 * @file   Types.hpp
 * @brief  Contains type definitions and macros used throughout the Uranium
 *         engine.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/
#pragma once

#include <cstdint>
#include <string_view>

// Object-oriented macros for defining classes and templates
#define UR_DECLARE class
#define UR_GENERIC(...) template <__VA_ARGS__>

#define UR_INTERFACE class         // Interface definition
#define UR_MARKER_INTERFACE class  // Marker interface definition
#define UR_ABSTRACT_CLASS class    // Abstract class definition
#define UR_SINGLETON_CLASS class   // Singleton class definition
#define UR_EXTENDS public          // Inheritance specifier
#define UR_IMPLEMENTS public       // Interface implementation specifier

using byte = int8_t;
