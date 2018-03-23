#include <cstdint>

#ifndef HOMEWORK3_EQUIPMENT_H
#define HOMEWORK3_EQUIPMENT_H

#endif  // HOMEWORK3_EQUIPMENT_H

namespace game {

    class Equipment {
    protected:
        bool presense_;

    public:
        void changePresense();
    };


    class Armor : Equipment {
    protected:
        uint8_t protection_level_;

    public:
        virtual void changeProtectionLevel() = 0;
    };

    class Lats : Armor {
    public:
        void changeProtectionLevel();
    };

    class Hauberk : Armor {
    public:
        void changeProtectionLevel();
    };

    class Weapon : Equipment {
    protected:
        uint8_t action_level_;
        uint8_t action_speed_;
        uint8_t action_radius_;

    public:
        virtual void changeActionLevel() = 0;

        virtual void changeActionSpeed() = 0;

        virtual void changeActionRadius() = 0;

        uint8_t getActionLevel();

        uint8_t getActionSpeed();

        uint8_t getActionRadius();
    };

    class Shavel : Weapon {
    public:
        void changeActionLevel();

        void changeActionSpeed();

        void changeActionRadius();
    };

    class Bow : Weapon {
    public:
        void changeActionLevel();

        void changeActionSpeed();

        void changeActionRadius();
    };

    class Sword : Weapon {
    public:
        void changeActionLevel();

        void changeActionSpeed();

        void changeActionRadius();
    };
}