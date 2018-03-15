class Machine : Environment {
    private:
        double fuel;
    public:
        double getFuelLevel(void);
    protected:
};

class Entity:DynamicEnvironment {
    private:
        int age;
    public:
        int getAge(void);
        void drop(void);
    protected:
};

class Man:Entity {
    private:
        bool gender;
        (const &Man)[2] parents;
        (const &Horse[]) horses; 
    public:
        bool getGender(void);
        bool getParents(void);
        void die(void);
    protected:
};

class Environment {
    private:
    public: 
    protected:
        int xPos;
        int yPos;
        int zPos;
};

class StaticEnvironment:Environment {
    private:
        bool visible; 
    public:
        bool setVisibility(bool vis);
    protected:
};

class DynamicEnvironment : Environment {
    private:
        bool visible;
        double mass;
        double speed[3];
    public:
        bool setVisibility(bool vis);
        void move(int x, int y, int z);
        void moveDelta(int delta_x, int delta_y, int delta_z);
        double getMass(void);
        double[3] getSpeed(void);
        void setSpeed(double[3] speed);
        void setSpeedDelta(double[3] speed);
    protected:
};

class Bag : DynamicEnvironment {
    private:
        (const &Item[]) content;
        const &Man owner;
    public:
        const &Item[] getContent(void);
        void dropItem(int id);
        void drop(void);
        const &Man getOwner(void);
        void setOwner(const &Man);
    protected:
};

class Eyes : DynamicEnvironment {
    private:
        double[3] sightDirection;
        bool closed;
    public:
        void setSightDirection(double[3] direction);
        double[3] getSightDirection(void);
        void blink(void);
        void wink(void);
        void close(void);
        void open(void);
    protected:
};

class Horse : Machine, DynamicEnvironment {
    private:
        int[3] maneColor;
        int[3] tailColor;
        int lear;
        double height;
        int size;
        const &Man owner;
    public:
        int[3] getManeColor(void);
        int[3] getTailColor(void);
        int getLear(void);
        double getHeight(void);
        int getSize(void);
        void setOwner(const &Man man);
        void setFree(void);
        void getCaught(void);
    protected:
};

class Tree : StaticEnvironment {
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

class FruitfulTree : Tree {
    private:
    public:
        void dropFruit(void);
    protected:
};

class Item : DynamicEnvironment {
    private:
        const &Man owner;
        int durability;
        bool broken;
    public:
        const &Man getOwner(void);
        void setOwner(const &Man);
        void spoil(int value);
    protected:
};

class Hauberk : Item {
    private:
        int armor; 
    public:
        int getArmor(void);
    protected:
};

class Lats : Item {
    private:
        int armor; 
    public:
        int getArmor(void);
    protected:
};

class Shovel : Item {
    private:
        int damage; 
    public:
        int getDamage(void);
    protected:
};

class Bow : Item {
    private:
        int strength; 
    public:
        int getStrength(void);
    protected:
};

class Sword : Item {
    private:
        int damage; 
    public:
        int getDamage(void);
    protected:
};

class Archer : Man {
    private:
        const &Item tool;
        const &Item dress; 
    public:
        void shoot(int[3] direction);
        void putOn(const &Item);
        void putOff(void);
        void takeTool(const &Item);
        void dropTool(void);
    protected:
};

class Peasant : Man {
    private:
        const &Item tool;
        const &Item dress; 
    public:
        void plowHere(void);
        void putOn(const &Item);
        void putOff(void);
        void takeTool(const &Item);
        void dropTool(void);
    protected:
};

class Knight : Man {
    private:
        const &Item tool;
        const &Item dress; 
    public:
        void attack(int[3] direction);
        void putOn(const &Item);
        void putOff(void);
        void takeTool(const &Item);
        void dropTool(void);
    protected:
};

class _emptyItem : Item {
    private:    
    public:
        const bool voidness = true; 
    protected:
};
