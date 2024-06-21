#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

namespace ui_event_args {
    /**
     * @struct base
     * @brief Base struct for UI event arguments.
     *
     * This struct provides basic properties for UI event arguments.
     */
    struct base {
        int x;
        int y;
    };

    /**
     * @struct base_with_timestamp
     * @brief Base struct for UI event arguments with a timestamp.
     *
     * This struct inherits from base and adds a timestamp.
     */
    struct base_with_timestamp : public base {
        long long timestamp;
    };

    /**
     * @struct mouse_enter
     * @brief Struct for mouse enter event arguments.
     *
     * This struct inherits from base_with_timestamp.
     */
    struct mouse_enter : public base_with_timestamp { };

    /**
     * @struct mouse_move
     * @brief Struct for mouse move event arguments.
     *
     * This struct inherits from base.
     */
    struct mouse_move : public base { };

    /**
     * @struct mouse_leave
     * @brief Struct for mouse leave event arguments.
     *
     * This struct inherits from base_with_timestamp.
     */
    struct mouse_leave : public base_with_timestamp { };

    /**
     * @struct click
     * @brief Struct for click event arguments.
     *
     * This struct inherits from base_with_timestamp.
     */
    struct click : public base_with_timestamp { };
};

class ui_event {
public:
    using event_id = std::size_t;

    enum ui_event_type {
        mouse_enter,
        mouse_move,
        mouse_leave,
        left_click,
        right_click,
    };

    /**
     * @typedef event_callback
     * @brief A type representing a callback function for an event.
     */
    using event_callback = std::function<void(const ui_event_args::base&)>;

    /**
     * @brief Get the event count of a specific type.
     * @param type The type of event.
     * @return The event count of the specified type.
     */
    int get_event_count(ui_event_type type) {
        return static_cast<int>(handlers[type].size());
    }

    /**
     * @brief Get the total count of all types of events.
     * @return The total event count.
     */
    int get_event_count() {
        int count = 0;

        for (const auto& pair : handlers)
            count += static_cast<int>(pair.second.size());
        
        return count;
    }

    /**
     * @brief Check if a specific type of event exists.
     * @param type The type of event.
     */
    bool event_exists(ui_event_type type) {
        return !handlers[type].empty();
    }

    /**
     * @brief Register a callback for a specific type of event.
     * @param type The type of event.
     * @param callback The callback function to be registered.
     * @return The ID of the registered event.
     */
    event_id on(ui_event_type type, event_callback callback) {
        event_id id = next_id++;
        handlers[type].push_back({ id, callback });
        return id;
    }

    /**
     * @brief Trigger a specific type of event.
     * @tparam EventArgs The type of event arguments.
     * @param type The type of event.
     * @param args The event arguments.
     */
    template<typename EventArgs>
    void trigger(ui_event_type type, const EventArgs& args) {
        for (auto& pair : handlers[type]) {
            pair.second(args);
        }
    }

    /**
     * @brief Remove a specific event by its ID.
     * @param id The ID of the event to be removed.
     * @return bool indicating whether the event was successfully removed.
     */
    bool remove_event(event_id id) {
        bool removed = false;

        for (auto& pair : handlers) {
            auto& callbacks = pair.second;

            auto it = std::remove_if(
                callbacks.begin(),
                callbacks.end(),
                [id](const auto& pair) {
                    return pair.first == id;
                }
            );

            if (it != callbacks.end()) {
                callbacks.erase(it, callbacks.end());
                removed = true;
            }
        }

        return removed;
    }

    /**
     * @brief Remove all events.
     */
    void remove_events() {
        handlers.clear();
    }

private:
    event_id next_id = 0;
    std::unordered_map<ui_event_type, std::vector<std::pair<event_id, event_callback>>> handlers;
};