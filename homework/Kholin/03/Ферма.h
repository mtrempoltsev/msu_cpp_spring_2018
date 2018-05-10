
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


#ifndef ФЕРМА_H
#define ФЕРМА_H
#include "Здание.h"

#include <string>

/**
  * class Ферма
  * 
  */

class Ферма : public Здание
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Ферма ();

  /**
   * Empty Destructor
   */
  virtual ~Ферма ();

  // Static Public attributes
  //  

  // Public attributes
  //  

  int Сколько_позволяет_закупить_боевых_единиц;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of Сколько_позволяет_закупить_боевых_единиц
   * @param new_var the new value of Сколько_позволяет_закупить_боевых_единиц
   */
  void setСколько_позволяет_закупить_боевых_единиц (int new_var)   {
      Сколько_позволяет_закупить_боевых_единиц = new_var;
  }

  /**
   * Get the value of Сколько_позволяет_закупить_боевых_единиц
   * @return the value of Сколько_позволяет_закупить_боевых_единиц
   */
  int getСколько_позволяет_закупить_боевых_единиц ()   {
    return Сколько_позволяет_закупить_боевых_единиц;
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

#endif // ФЕРМА_H
