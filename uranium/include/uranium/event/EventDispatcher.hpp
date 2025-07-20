/*******************************************************************
 * @file   EventDispatcher.hpp
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
   * @class EventDispatcher
   * @brief Manages the registration of listeners, queuing of events,
   *        and dispatching of those events based on priority.
   *
   *        Events are organized by priority and can be dispatched
   *        selectively or flushed entirely.
   */
  class EventDispatcher final {
  public:
    using ListenerID = uint64_t;
    using Listener = std::function<void(IEvent&)>;

  public:
    /**
     * @brief Constructs a new EventDispatcher instance.
     */
    explicit EventDispatcher() noexcept;

    /**
     * @brief Destroys the EventDispatcher instance, clearing all queued
     *        events and unregistering all listeners.
     */
    ~EventDispatcher() noexcept;

    /**
     * @brief Registers a new listener for a specific event type.
     *
     * @param type     The event type to listen for.
     * @param priority Priority of the listener corresponding to the event.
     * @param listener The callback function to invoke on dispatch.
     */
    void subscribe(IEvent::Type type, uint32_t priority, Listener listener);

    /**
     * @brief Queues a new event under a specified priority.
     *
     * @param event A pointer to the event object.
     */
    void raise(IEvent* event);

    /**
     * @brief Dispatches and processes all events in a given priority queue.
     *
     */
    void dispatch();

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

    /**
     * @struct ListenerEntry
     * @brief Associates a listener ID with a callback function.
     */
    struct ListenerEntry {
      ListenerID id;
      uint32_t priority;
      Listener callback;
    };

    struct Queue {
      uint32_t head;
      uint32_t tail;
      std::array<IEvent*, 512> buffer;
    };

    // TODO: Make the event queue have a max limit
    // Add another queue that keeps track of the overflowed events.
    // Handle the in-bound events using a cyclical queue.
    // It can handle by default from [0, 512] events in one buffer.
    // Mixing different kind of event types into one dispatcher can be
    // performance costly, so better optimize it or just leave it like that.
    std::vector<IEvent*> event_queue;
    std::unordered_map<IEvent::Type, std::vector<ListenerEntry>> listeners;
  };
}  // namespace uranium::event
