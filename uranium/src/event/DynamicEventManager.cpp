#include "uranium/event/DynamicEventManager.hpp"

#include "uranium/core/Utils.hpp"

using namespace uranium::event;

DynamicEventManager::DynamicEventManager() noexcept
    : listeners(), event_buffers() {}

DynamicEventManager::~DynamicEventManager() noexcept { this->clear(); }

DynamicEventManager::ListenerID DynamicEventManager::add(IEvent::Type type,
                                                         Listener listener) {
  // Generate a new listener id
  ListenerID id = next_listener_id++;

  // Store the new listener linked to the generated ID
  listeners[type].push_back(ListenerEntry{id, std::move(listener)});
  return id;
}

bool DynamicEventManager::remove(IEvent::Type type, ListenerID id) {
  // Look up the listener list for the given type
  auto it = listeners.find(type);
  if (it == listeners.end()) {
    return false;  // No listeners registered for this type
  }

  auto& vec = it->second;
  auto original_size = vec.size();

  // Remove the listener with the matching ID
  vec.erase(std::remove_if(
                vec.begin(), vec.end(),
                [id](const ListenerEntry& entry) { return entry.id == id; }),
            vec.end());

  // If the vector is empty, remove the entry from the map entirely
  if (vec.empty()) {
    listeners.erase(it);
  }

  // Return true if a listener was removed
  return vec.size() < original_size;
}

void DynamicEventManager::raise(Priority priority, IEvent* event) {
  event_buffers[static_cast<size_t>(priority)].push_back(event);
}

void DynamicEventManager::dispatch(Priority priority) {
  auto& queue = event_buffers[static_cast<size_t>(priority)];
  while (!queue.empty()) {
    // Obtain the first event from queue
    IEvent* event = queue.back();
    queue.pop_back();

    // Check if there is a listener asociated to the event to handle
    auto it = listeners.find(event->type);
    UR_ASSERT(it == listeners.end());

    // Handle the event linked to the listener
    for (auto& entry : it->second) {
      entry.callback(*event);
    }
  }
}

void DynamicEventManager::flush() {
  for (auto& queue : event_buffers) {
    while (!queue.empty()) {
      queue.pop_back();
    }
  }
}

void DynamicEventManager::clear() {
  // Flush all events left in queue
  // And remove all listeners
  flush();
  listeners.clear();
}
