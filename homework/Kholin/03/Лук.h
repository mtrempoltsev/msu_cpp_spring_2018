
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


#ifndef ЛУК_H
#define ЛУК_H
#include "Оружие.h"

#include <string>

/**
  * class Лук
  * 
  */

class Лук : public Оружие
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Лук ();

  /**
   * Empty Destructor
   */
  virtual ~Лук ();

  // Static Public attributes
  //  

  // Public attributes
  //  

  int Улучшение_дальности_стрельбы;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of Улучшение_дальности_стрельбы
   * @param new_var the new value of Улучшение_дальности_стрельбы
   */
  void setУлучшение_дальности_стрельбы (int new_var)   {
      Улучшение_дальности_стрельбы = new_var;
  }

  /**
   * Get the value of Улучшение_дальности_стрельбы
   * @return the value of Улучшение_дальности_стрельбы
   */
  int getУлучшение_дальности_стрельбы ()   {
    return Улучшение_дальности_стрельбы;
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

#endif // ЛУК_H
