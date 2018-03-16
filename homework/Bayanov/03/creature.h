#ifndef HOMEWORK3_CREATURE_H
#define HOMEWORK3_CREATURE_H

#endif  // HOMEWORK3_CREATURE_H

#include <cstdint>
#include <string>

#include "equipment.h"

namespace game {

    class Creature {
    protected:
        uint8_t satiety_;
        uint8_t health_;
        uint8_t drowsiness_;

    public:
        virtual void eat() = 0;

        virtual void sleep() = 0;
    };

    class Human : Creature {
    protected:
        std::string name_;
        uint8_t age_;

    public:
        void speak(std::string phrase = "Hello, unfamiliar traveler!");

        void eat();

        void sleep();

        virtual void change_state() = 0;
    };

    class Peasant : Human {
        enum Gender { male, fimale };
        Gender gender_;

        enum State { eating, sleeping, digging, nothin_doing };

        State state_;

        Shavel shavel_;

    public:
        void dig();

        void throw_out_shavel();

        void take_shavel();
    };

    class Knight : Human {
        enum State { eating, sleeping, fighting, nothin_doing };

        State state_;

        Sword sword_;

    public:
        void hit();

        void throw_out_sword();

        void take_sword();

        void train_hitting();
    };

    class Archer : Human {
        enum State { eating, sleeping, fighting, nothin_doing };

        State state_;

        Bow bow_;

    public:
        void shot();

        void throw_out_bow();

        void take_bow();

        void train_shotting();
    };

    class Pet : Creature {
    protected:
        std::string owner_;

    public:
        virtual void eat() = 0;

        virtual void sleep() = 0;
    };

    class Pig : Pet {
        enum State { eating, sleeping, lying_in_dirty, grunting, nothing_doing };

        State state_;

    public:
        void grunt();

        void eat();

        void sleep();

        void lie_in_dirty();
    };

    class Dog : Pet {
        enum State { eating, sleeping, guarding, barking, nothing_doing };

        State state_;

    public:
        void bark();

        void eat();

        void sleep();

        void guard();
    };
}