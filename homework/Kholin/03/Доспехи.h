
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


#ifndef ДОСПЕХИ_H
#define ДОСПЕХИ_H
#include "Защита.h"

#include <string>

/**
  * class Доспехи
  * 
  */

class Доспехи : public Защита
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Доспехи ();

  /**
   * Empty Destructor
   */
  virtual ~Доспехи ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


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



};

#endif // ДОСПЕХИ_H
