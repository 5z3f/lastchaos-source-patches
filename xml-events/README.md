### Simple javascript-style event system for xml elements (cpp17)

Available events: `mouse_enter`, `mouse_move`, `mouse_leave`, `left_click`, and `right_click`.

#### Example Usage

First, let's initialize ui element:

```cpp
auto* btn_ok = (CUIButton*)findUI("btn_ok");
```

Now we can assign event handlers to it:

**Handling left click event**

```cpp
btn_ok->on(ui_event::left_click, [](const ui_event_args::base& args) {
    auto& click_args = static_cast<const ui_event_args::click&>(args);
    std::cout << "Left clicked: (" << click_args.x << ", " << click_args.y << ", " << click_args.timestamp << ")" << std::endl;
});
```

**Handling right click event**

```cpp
btn_ok->on(ui_event::right_click, [](const ui_event_args::base& args) {
    auto& click_args = static_cast<const ui_event_args::click&>(args);
    std::cout << "Right clicked: (" << click_args.x << ", " << click_args.y << ", " << click_args.timestamp << ")" << std::endl;
});
```

**Handling mouse move event**

```cpp
btn_ok->on(ui_event::mouse_move, [](const ui_event_args::base& args) {
    auto& move_args = static_cast<const ui_event_args::mouse_move&>(args);
    std::cout << "Move: (" << move_args.x << ", " << move_args.y << ")" << std::endl;
});
```

**Handling mouse enter event**

```cpp
btn_ok->on(ui_event::mouse_enter, [](const ui_event_args::base& args) {
    auto& enter_args = static_cast<const ui_event_args::mouse_enter&>(args);
    std::cout << "Enter: (" << enter_args.x << ", " << enter_args.y << ", " << enter_args.timestamp << ")" << std::endl;
});
```

**Handling mouse leave event**

```cpp
ui_event::event_id mouse_leave_event = btn_ok->on(ui_event::mouse_leave, [](const ui_event_args::base& args) {
    auto& leave_args = static_cast<const ui_event_args::mouse_leave&>(args);
    std::cout << "Leave: (" << leave_args.x << ", " << leave_args.y << ", " << leave_args.timestamp << ")" << std::endl;
});
```

#### Managing Events

**Remove event by `ui_event::event_id`** id

```cpp
bool success = btn_ok->remove_event(mouse_leave_event);
```

**You can also trigger events programmatically and remove all events if needed:**

```cpp
// Triggering an event manually
ui_event_args::click click_args{100, 200, 1234567890};
btn_ok->trigger(ui_event::left_click, click_args);

// Removing all events
btn_ok->remove_events();
```

#### Additional Functions

**Checking if an event exists**

```cpp
if (btn_ok->event_exists(ui_event::left_click)) {
    std::cout << "Left click event exists for btn_ok." << std::endl;
}
```

**Getting event callback count of an event**

```cpp
int left_click_count = btn_ok->get_event_count(ui_event::left_click);
std::cout << "btn_ok event count [left_click]: " << left_click_count << std::endl;
```

**Getting total event callback count**

```cpp
int total_events = btn_ok->get_event_count();
std::cout << "Total events registered: " << total_events << std::endl;
```

#### Files
[events-initial-branch.patch](./events-initial-branch.patch) ([You can view patch file here](https://diffy.org/diff/927245528534)) \
[ui_event.h](./ui_event.h) - for manual implementation