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

class StaticEnvironment : public Environment {
    private:
        bool visible; 
    public:
        bool setVisibility(bool vis);
    protected:
};

class DynamicEnvironment : public Environment {
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

class Bag : public DynamicEnvironment {
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

class Eyes : public DynamicEnvironment {
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

class Horse : public Machine, public DynamicEnvironment {
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
        const &Man owner;
        int durability;
        bool broken;
    public:
        const &Man getOwner(void);
        void setOwner(const &Man);
        void spoil(int value);
    protected:
};

class Hauberk : public Item {
    private:
        int armor; 
    public:
        int getArmor(void);
    protected:
};

class Lats : public Item {
    private:
        int armor; 
    public:
        int getArmor(void);
    protected:
};

class Shovel : public Item {
    private:
        int damage; 
    public:
        int getDamage(void);
    protected:
};

class Bow : public Item {
    private:
        int strength; 
    public:
        int getStrength(void);
    protected:
};

class Sword : public Item {
    private:
        int damage; 
    public:
        int getDamage(void);
    protected:
};

class Archer : public Man {
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

class Peasant : public Man {
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

class Knight : public Man {
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

class _emptyItem : public Item {
    private:    
    public:
        const bool voidness = true; 
    protected:
};
