#include <vector>
#include <string>
#include <functional>

class Event;

class Trigger {
public:
    void Enable();
    void Disable();
    void AddAction(std::function<void()> function);
    void RemoveAction(std::function<void()> function);
    void AddEvent(Event& event);
    void RemoveEvent(Event& event);
private:
    bool enabled;
    std::vector<std::function<void(Event&)>> actions;
};

class Event {
public:
    void AddTrigger();
private:
    std::vector<Trigger*> triggers;
};

class MouseEvent : public Event {
public:
    std::pair<double, double> GetMouseXY();
    std::pair<double, double> GetMouseDirection();
    int GetMouseButtonClicked();
private:
    struct MouseState {
        double x;
        double y;
        std::vector<int> keys_pressed;
        std::vector<int> keys_released;
    };
    std::vector<MouseState> states;
};

class KeyBoardEvent : public Event {
public:
    std::vector<int> GetKeysPressed();
    std::vector<int> GetKeysReleased();
private:
    struct KeyBoardState {
        std::vector<int> keys_pressed;
        std::vector<int> keys_released;
    };
    std::vector<KeyBoardState> states;
};

class TimerEvent {
public:
    bool IsPeriodic();
    bool GetRemaining();
    bool GetElapsed();
    void Start();
    void Pause();
private:
    class Timer {
        // ...
    };
    Timer timer;
};

class Unit;

class UnitEvent: public Event {
public:
    Unit* GetUnit();
private:
    Unit* unit;
};

class UnitState;

class UnitStateEvent: Event {
public:
    std::string GetState();
private:
    std::string state_name;
};

class Item;

class ItemEvent: public Event {
public:
    Item* GetItem();
private:
    Item* item;
};

class ItemState;

class ItemStateEvent: public Event {
public:
    std::string GetState();
private:
    std::string state_name;
};

class Widget;

class OrderEvent: public Event {
    Widget* GetTarget();
    Widget* GetSource();
private:
    Widget* source;
    Widget* target;
};

class MoveEvent: public OrderEvent {
public:
    std::pair<double, double> GetDirection();
private:
    std::pair<double, double> direction;
};

class AttackEvent: OrderEvent {};

class CancelEvent: OrderEvent {};

class Widget {
public:
    // Getters
private:
    std::string model_file;
    bool is_destroyable;
    bool is_attackable;
    double move_speed;
    double turn_speed;
    std::pair<double, double> position;
    double health_points;
};

class Inventory {
public:
    void AddItem(Item* item);
    void RemoveItem(Item* item);
    Item* GetItemInSlot(int slot);
private:
    std::vector<Item*> items;
};

class Unit: public Widget {
public:
    // Getters
    bool IsDead();
    bool IsInCombat();
    // ...
private:
    struct UnitState {
        double energy_points;
        Inventory inventory;
        double attack_damage;
        double attack_range;
        double attack_speed;
        double armor;
    };
    std::vector<UnitState> states;
};

class Item: public Widget {
public:
    // Getters
    bool IsBroken();
    Unit* CarriedBy();
    // ...
private:
    struct ItemState {
        double attack_damage_bonus;
        double attack_speed_bonus;
        double armor_bonus;
        double move_speed_bonus;
    };
    enum ItemType {
        SWORD,
        AXE,
        BOW,
        SHIELD,
        HELM,
        GLOVES,
        BOOTS,
        BELT
        // ...
    };
    ItemState itemState;
    Unit* owner;
    ItemType itemType;
};

class Decoration : Widget {
public:
    bool IsVisible();
private:
    bool is_visible;
};