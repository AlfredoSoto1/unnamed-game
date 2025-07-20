/*******************************************************************
 * @file   IEvent.hpp
 * @brief
 *
 * @author Alfredo
 * @date   May 2025
 *******************************************************************/
#pragma once

#include "uranium/core/Types.hpp"

namespace uranium::event {

  /**
   * @brief Abstract base class for all events in the system.
   *
   * This class provides a unified event interface and a way to register
   * and identify both engine-defined and client-defined event types
   * using a unique integer ID.
   */
  UR_ABSTRACT_CLASS IEvent {
  public:
    using Type = uint32_t;  // Event type identifier

  public:
    /**
     * @brief Constructs a new event with the given type ID.
     *
     * @param type A unique identifier for the event type.
     */
    IEvent(IEvent::Type type) : type(type) {}

  public:
    IEvent::Type type;

  public:
    /**
     * @brief Generates a new unique event type ID for client-defined events.
     *
     * This function ensures no collision with built-in types by starting
     * at the value of `Builtin::COUNT`.
     *
     * @return A unique event type ID.
     */
    static inline Type create() { return counter++; }

    /**
     * @enum Builtin
     * @brief Enumeration of all built-in engine event types.
     *
     * These events cover core systems like application lifecycle,
     * input, windowing, and networking. The `COUNT` enum value is
     * used to determine the starting ID for custom events.
     */
    enum class Builtin : Type {
      // Application-level events
      APPLICATION_EXIT = 0,
      APPLICATION_START,
      APPLICATION_PAUSE,
      APPLICATION_RESUME,

      // Mouse events
      MOUSE_CLICKED,
      MOUSE_PRESSED,
      MOUSE_RELEASED,
      MOUSE_WHEEL,

      // Cursor events
      CURSOR_MOVED,
      CURSOR_ENTERED,
      CURSOR_EXITED,
      CURSOR_DROPPED,

      // Keyboard events
      KEY_PRESSED,
      KEY_RELEASED,
      KEY_TYPED,

      // Window and system events
      WINDOW_RESIZED,
      WINDOW_MOVED,
      WINDOW_CLOSED,
      WINDOW_MINIMIZED,
      WINDOW_MAXIMIZED,
      WINDOW_FOCUS_GAINED,
      WINDOW_FOCUS_LOST,

      // Network events
      NETWORK_CONNECTED,
      NETWORK_DISCONNECTED,
      NETWORK_DATA_RECEIVED,
      NETWORK_DATA_SENT,

      // Game events
      GAME_EVENT,
      COUNT,
    };

  private:
    friend class EventManager;

    /**
     * @brief Static counter for generating unique custom event type IDs.
     *
     * Initialized to start after all built-in event types. Each call to
     * `create()` will increment and return a new unique ID.
     */
    static inline IEvent::Type counter = static_cast<Type>(Builtin::COUNT);
  };

}  // namespace uranium::event
