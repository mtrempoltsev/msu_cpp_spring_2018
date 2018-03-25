#ifndef HOMEWORK3_CREATURE_H
#define HOMEWORK3_CREATURE_H

#endif  // HOMEWORK3_CREATURE_H

#include <cstdint>
#include <string>

#include "equipment.h"

namespace game {

    class Creature {
    protected:
        enum Gender { male, fimale };
        Gender gender_;

        uint8_t satiety_;
        uint8_t health_;
        uint8_t drowsiness_;

    public:
        virtual void eat() = 0;

        virtual void sleep() = 0;
    };

    class Pet;

    class Human : Creature {
    protected:
        enum State { eating, sleeping, acting, training, nothin_doing };
        State state_;

        std::string name_;
        uint8_t age_;

        Weapon* weapon_;
        Armor* armor_;

        Pet* pet_;
    public:
        void speak(std::string phrase = "Hello, unfamiliar traveler!");

        void eat();

        void sleep();

        virtual void takeWeapon() = 0;

        virtual void throwOutWeapon() = 0;

        virtual void act() = 0;

        virtual void trainAction() = 0;
    };

    class Peasant : Human {
    public:
        void takeWeapon();

        void throwOutWeapon();

        void act();

        void trainAction();
    };

    class Knight : Human {
    public:
        void takeWeapon();

        void throwOutWeapon();

        void act();

        void trainAction();
    };

    class Archer : Human {
    public:
        void takeWeapon();

        void throwOutWeapon();

        void act();

        void trainAction();
    };

    class Pet : Creature {
    protected:
        enum State { eating, sleeping, acting, sounding, nothing_doing };
        State state_;

        std::string owner_;
        std::string moniker_;

    public:
        virtual void eat() = 0;

        virtual void sleep() = 0;

        virtual void act() = 0;

        virtual void sound() = 0;
    };

    class Pig : Pet {
    public:
        void eat();

        void sleep();

        void act();

        void sound();
    };

    class Dog : Pet {
    public:
        void eat();

        void sleep();

        void act();

        void sound();
    };
}