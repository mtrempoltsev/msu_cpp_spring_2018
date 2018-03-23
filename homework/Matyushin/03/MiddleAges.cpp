class Machine : public Environment {
    private:
        double fuel;
    public:
        double getFuelLevel(void);
    protected:
};

class Entity : public DynamicEnvironment {
    private:
        int age;
    public:
        int getAge(void);
        void drop(void);
    protected:
};

class Man : public Entity {
    private:
        bool gender;
        const Man** parents;
        const Horse** horses; 
    public:
        bool getGender(void);
        const Man** getParents(void);
        void die(void);
    protected:
};

class Environment {
    private:
        bool visible;
    public:
        bool setVisibility(bool vis);
    protected:
        Point pos;
};

class StaticEnvironment : public Environment {
    private:
    public:
    protected:
};

class DynamicEnvironment : public Environment {
    private:
        double mass;
        Vector speed;
    public:
        void move(Point newpos);
        void moveDelta(Vector deltapos);
        double getMass(void);
        Vector getSpeed(void);
        void setSpeed(Vector speed);
        void setSpeedDelta(Vector deltaspeed);
    protected:
};

class Bag : public DynamicEnvironment {
    private:
        const Item** content;
        const Man** owner;
    public:
        const Item* getContent(void);
        void dropItem(int id);
        void drop(void);
        const Man* getOwner(void);
        void setOwner(const Man* man);
    protected:
};

class Point {
    private:
    public:
        double x;
        double y;
        double z;
    protected:
};

class Vector : public Point {
    private:
    public:
        void normalize(void);
    protected:
};

class ColorRGB : public Point {
    private:
    public:
    protected:
};

class Eyes : public DynamicEnvironment {
    private:
        Vector sightDirection;
        bool closed;
    public:
        void setSightDirection(Vector direction);
        Vector getSightDirection(void);
        void blink(void);
        void wink(void);
        void close(void);
        void open(void);
    protected:
};

class Horse : public Machine, public DynamicEnvironment {
    private:
        ColorRGB maneColor;
        ColorRGB tailColor;
        int lear;
        double height;
        int size;
        const Man* owner;
    public:
        ColorRGB getManeColor(void);
        ColorRGB getTailColor(void);
        int getLear(void);
        double getHeight(void);
        int getSize(void);
        void setOwner(const Man* man);
        void setFree(void);
        void getCaught(void);
    protected:
};

class Tree : public StaticEnvironment {
    private:
        int height;
        int kind;
        int greeness;
        int structure;
    public:
        int getHeight(void);
        void dropLeaf(void);
        void dropBranch(void);
    protected:
};

class FruitfulTree : public Tree {
    private:
    public:
        void dropFruit(void);
    protected:
};

class Item : public DynamicEnvironment {
    private:
        const Man* owner;
        int durability;
        bool broken;
    public:
        const Man* getOwner(void);
        void setOwner(const Man*);
        void spoil(int value);
    protected:
};

class Armor : public Item {
    private:
        int armor; 
    public:
        int getArmor(void);
    protected:
};

class Hauberk : public Armor {
    private:
    public:
    protected:
};

class Lats : public Armor {
    private: 
    public:
    protected:
};

class Tool : public Item {
    private:
        int strength; 
    public:
        int getStrength(void);
    protected:
};

class Weapon : public Item {
    private:
        int damage; 
    public:
        int getDamage(void);
    protected:
};

class Shovel : public Tool {
    private:
    public:
    protected:
};

class Bow : public Weapon {
    private:
    public:
    protected:
};

class Sword : public Weapon {
    private:
    public:
    protected:
};

class SkilledMan : public Man {
    private:
        const Item* tool;
        const Item* dress;
    public:
        void putOn(const Item* cloth);
        void putOff(void);
        void takeTool(const Item* t);
        void dropTool(void);
    protected:
};

class Archer : public SkilledMan {
    public:
    public:
        void shoot(Vector direction);
    protected:
};

class Peasant : public SkilledMan {
    private:
    public:
        void plowHere(void);
    protected:
};

class Knight : public SkilledMan {
    private:
    public:
        void attack(Vector direction);
    protected:
};

class _emptyItem : public Item {
    private:    
    public:
        const bool voidness = true; 
    protected:
};
