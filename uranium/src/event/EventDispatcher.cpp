#include "uranium/event/EventDispatcher.hpp"

#include "uranium/core/Utils.hpp"

using namespace uranium::event;

EventDispatcher::EventDispatcher() noexcept : listeners(), event_queue() {}

EventDispatcher::~EventDispatcher() noexcept {
  // Clear all events and listeners
  this->clear();
}

void EventDispatcher::subscribe(IEvent::Type type, uint32_t priority,
                                Listener listener) {
  // Generate a new listener id
  // Store the new listener linked to the generated ID
  listeners[type].push_back(
      {next_listener_id++, priority, std::move(listener)});

  // Sort listeners for this type by descending priority
  std::sort(listeners[type].begin(), listeners[type].end(),
            [](const ListenerEntry& a, const ListenerEntry& b) {
              // Higher priority first
              return a.priority > b.priority;
            });
}

void EventDispatcher::raise(IEvent* event) { event_queue.push_back(event); }

void EventDispatcher::dispatch() {
  while (!event_queue.empty()) {
    // Obtain the first event from queue
    IEvent* event = event_queue.back();
    event_queue.pop_back();

    // Check if there is a listener asociated to the event to handle
    auto it = listeners.find(event->type);
    UR_ASSERT(it == listeners.end());

    // Handle the event linked to the listener
    for (auto& entry : it->second) {
      entry.callback(*event);
    }
  }
}

void EventDispatcher::flush() {
  while (!event_queue.empty()) {
    event_queue.pop_back();
  }
}

void EventDispatcher::clear() {
  // Flush all events left in queue
  // And remove all listeners
  flush();
  listeners.clear();
}
