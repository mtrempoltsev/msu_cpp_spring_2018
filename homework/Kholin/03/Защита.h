
#ifndef БАШНЯ_H
#define БАШНЯ_H
#include "Здание.h"

#include <string>

/**
  * class Башня
  * 
  */

class Башня : public Здание
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Башня ();

  /**
   * Empty Destructor
   */
  virtual ~Башня ();

  // Static Public attributes
  //  

  // Public attributes
  //  

  int Наносимый_урон;
  int Скорость_наносимого_урона;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of Наносимый_урон
   * @param new_var the new value of Наносимый_урон
   */
  void setНаносимый_урон (int new_var)   {
      Наносимый_урон = new_var;
  }

  /**
   * Get the value of Наносимый_урон
   * @return the value of Наносимый_урон
   */
  int getНаносимый_урон ()   {
    return Наносимый_урон;
  }

  /**
   * Set the value of Скорость_наносимого_урона
   * @param new_var the new value of Скорость_наносимого_урона
   */
  void setСкорость_наносимого_урона (int new_var)   {
      Скорость_наносимого_урона = new_var;
  }

  /**
   * Get the value of Скорость_наносимого_урона
   * @return the value of Скорость_наносимого_урона
   */
  int getСкорость_наносимого_урона ()   {
    return Скорость_наносимого_урона;
  }


  /**
   * @param  Объект
   */
  void Отаковать_объект (Объект Объект)
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:


  void initAttributes () ;

};

#endif // БАШНЯ_H


#ifndef ЗАЩИТА_H
#define ЗАЩИТА_H
#include "Снаряжение.h"

#include <string>

/**
  * class Защита
  * 
  */

class Защита : public Снаряжение
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Защита ();

  /**
   * Empty Destructor
   */
  virtual ~Защита ();

  // Static Public attributes
  //  

  // Public attributes
  //  

  int На_сколько_улучшает_защиту;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of На_сколько_улучшает_защиту
   * @param new_var the new value of На_сколько_улучшает_защиту
   */
  void setНа_сколько_улучшает_защиту (int new_var)   {
      На_сколько_улучшает_защиту = new_var;
  }

  /**
   * Get the value of На_сколько_улучшает_защиту
   * @return the value of На_сколько_улучшает_защиту
   */
  int getНа_сколько_улучшает_защиту ()   {
    return На_сколько_улучшает_защиту;
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:


  void initAttributes () ;

};

#endif // ЗАЩИТА_H
