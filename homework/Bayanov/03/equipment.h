#include <cstdint>

#ifndef HOMEWORK3_EQUIPMENT_H
#define HOMEWORK3_EQUIPMENT_H

#endif  // HOMEWORK3_EQUIPMENT_H

namespace game {

    class Equipment {
        bool presense;

    public:
        void change_presense();
    };

    class Shavel : Equipment {
        uint8_t digging_level_;

    public:
        void change_diggin_level();
    };

    class Armor : Equipment {
    protected:
        uint8_t protection_level_;

    public:
        virtual void change_protection_level() = 0;
    };

    class Lats : Armor {
    public:
        void change_protection_level();
    };

    class Hauberk : Armor {
    public:
        void change_protection_level();
    };

    class Weapon : Equipment {
    protected:
        uint8_t damage_lats_level_;
        uint8_t damage_hauberk_;

    public:
        virtual void change_damage_lats_level() = 0;

        virtual void change_damage_hauberk_level() = 0;
    };

    class Bow : Weapon {
        uint8_t fire_range_;
        uint8_t shot_frequency_;

    public:
        void change_fire_range();

        void change_shot_frequency();

        void change_damage_lats_level();

        void change_damage_hauberk_level();
    };

    class Sword : Weapon {
        uint8_t hit_frequency_;

    public:
        void change_hit_freauency();

        void change_damage_lats_level();

        void change_damage_hauberk_level();
    };
}