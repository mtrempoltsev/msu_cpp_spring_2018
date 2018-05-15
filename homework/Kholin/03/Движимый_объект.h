
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


#ifndef ДВИЖИМЫЙ_ОБЪЕКТ_H
#define ДВИЖИМЫЙ_ОБЪЕКТ_H
#include "Объект.h"

#include <string>

/**
  * class Движимый_объект
  * 
  */

class Движимый_объект : public Объект
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Движимый_объект ();

  /**
   * Empty Destructor
   */
  virtual ~Движимый_объект ();

  // Static Public attributes
  //  

  // Public attributes
  //  

  int Наносимый_урон;
  int Скорость_атаки;
  int Скорость_перемещения;
  int Сколько_стоит_боевых_единиц;

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
   * Set the value of Скорость_атаки
   * @param new_var the new value of Скорость_атаки
   */
  void setСкорость_атаки (int new_var)   {
      Скорость_атаки = new_var;
  }

  /**
   * Get the value of Скорость_атаки
   * @return the value of Скорость_атаки
   */
  int getСкорость_атаки ()   {
    return Скорость_атаки;
  }

  /**
   * Set the value of Скорость_перемещения
   * @param new_var the new value of Скорость_перемещения
   */
  void setСкорость_перемещения (int new_var)   {
      Скорость_перемещения = new_var;
  }

  /**
   * Get the value of Скорость_перемещения
   * @return the value of Скорость_перемещения
   */
  int getСкорость_перемещения ()   {
    return Скорость_перемещения;
  }

  /**
   * Set the value of Сколько_стоит_боевых_единиц
   * @param new_var the new value of Сколько_стоит_боевых_единиц
   */
  void setСколько_стоит_боевых_единиц (int new_var)   {
      Сколько_стоит_боевых_единиц = new_var;
  }

  /**
   * Get the value of Сколько_стоит_боевых_единиц
   * @return the value of Сколько_стоит_боевых_единиц
   */
  int getСколько_стоит_боевых_единиц ()   {
    return Сколько_стоит_боевых_единиц;
  }


  /**
   * @param  Объект
   */
  void Отаковать_объект (Объект Объект)
  {
  }


  /**
   * @param  Снаряжение
   */
  void Одеть_снаряжение (Снаряжение Снаряжение)
  {
  }


  /**
   * @param  D_X
   * @param  D_Y
   * @param  D_Z
   */
  void Переместиться (double D_X, double D_Y, double D_Z)
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

#endif // ДВИЖИМЫЙ_ОБЪЕКТ_H
