/*******************************************************************
 * @file   EventManager.hpp
 * @brief  Central dispatcher for managing event flow and listeners
 *
 * @author Alfredo
 * @date   May 2025
 *******************************************************************/
#pragma once

#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "IEvent.hpp"
#include "uranium/core/Types.hpp"

namespace uranium::event {

  /**
   * @class DynamicEventManager
   * @brief Manages the registration of listeners, queuing of events,
   *        and dispatching of those events based on priority.
   *
   *        Events are organized by priority and can be dispatched
   *        selectively or flushed entirely.
   */
  class DynamicEventManager final {
  public:
    /**
     * @enum Priority
     * @brief Defines the importance level of an event queue. Higher
     *        priority queues can be processed first.
     */
    enum class Priority {
      SYSTEM = 0,
      APPLICATION,
      INPUT,
      RENDERER,
      GAMEPLAY,
      COUNT,
    };

  public:
    using ListenerID = uint64_t;
    using Listener = std::function<void(IEvent&)>;

  public:
    /**
     * @brief Constructs a new DynamicEventManager instance.
     */
    explicit DynamicEventManager() noexcept;

    /**
     * @brief Destroys the DynamicEventManager instance, clearing all queued
     *        events and unregistering all listeners.
     */
    ~DynamicEventManager() noexcept;

    /**
     * @brief Registers a new listener for a specific event type.
     *
     * @param type     The event type to listen for.
     * @param listener The callback function to invoke on dispatch.
     * @return ListenerID A unique ID used for listener removal.
     */
    ListenerID add(IEvent::Type type, Listener listener);

    /**
     * @brief Registers a new listener for a specific event type.
     *        This Listener CANNOT be removed once added. The manager
     *        handles its lifetime throught the lifetime of the application.
     *
     * @param type     The event type to listen for.
     * @param listener The callback function to invoke on dispatch.
     */
    void addPermanent(IEvent::Type type, Listener listener);

    /**
     * @brief Unregisters a previously added listener.
     *
     * @param type The event type associated with the listener.
     * @param id   The unique ID of the listener.
     * @return true if the listener was removed successfully.
     * @return false if the listener was not found.
     */
    bool remove(IEvent::Type type, ListenerID id);

    /**
     * @brief Queues a new event under a specified priority.
     *
     * @param priority The priority level of the event.
     * @param event    A pointer to the event object.
     */
    void raise(Priority priority, IEvent* event);

    /**
     * @brief Dispatches and processes all events in a given priority queue.
     *
     * @param priority The priority level to dispatch from.
     */
    void dispatch(Priority priority);

    /**
     * @brief Clears all queued events from every priority level.
     */
    void flush();

    /**
     * @brief Clears all event queues and unregisters all listeners.
     */
    void clear();

  private:
    static inline ListenerID next_listener_id = 0;
    static inline constexpr size_t PCOUNT =
        static_cast<size_t>(Priority::COUNT);

    /**
     * @struct ListenerEntry
     * @brief Associates a listener ID with a callback function.
     */
    struct ListenerEntry {
      ListenerID id;
      Listener callback;
    };

    std::array<std::vector<IEvent*>, PCOUNT> event_buffers;
    std::unordered_map<IEvent::Type, std::vector<ListenerEntry>> listeners;
  };
}  // namespace uranium::event
