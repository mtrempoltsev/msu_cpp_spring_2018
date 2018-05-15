
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


#ifndef ОБЪЕКТ_H
#define ОБЪЕКТ_H

#include <string>

/**
  * class Объект
  * 
  */

class Объект
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Объект ();

  /**
   * Empty Destructor
   */
  virtual ~Объект ();

  // Static Public attributes
  //  

  // Public attributes
  //  

  double Координата_X;
  double Координата_Y;
  double Координата_Z;
  int Здоровье;

  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


  /**
   * Set the value of Координата_X
   * @param new_var the new value of Координата_X
   */
  void setКоордината_X (double new_var)   {
      Координата_X = new_var;
  }

  /**
   * Get the value of Координата_X
   * @return the value of Координата_X
   */
  double getКоордината_X ()   {
    return Координата_X;
  }

  /**
   * Set the value of Координата_Y
   * @param new_var the new value of Координата_Y
   */
  void setКоордината_Y (double new_var)   {
      Координата_Y = new_var;
  }

  /**
   * Get the value of Координата_Y
   * @return the value of Координата_Y
   */
  double getКоордината_Y ()   {
    return Координата_Y;
  }

  /**
   * Set the value of Координата_Z
   * @param new_var the new value of Координата_Z
   */
  void setКоордината_Z (double new_var)   {
      Координата_Z = new_var;
  }

  /**
   * Get the value of Координата_Z
   * @return the value of Координата_Z
   */
  double getКоордината_Z ()   {
    return Координата_Z;
  }

  /**
   * Set the value of Здоровье
   * @param new_var the new value of Здоровье
   */
  void setЗдоровье (int new_var)   {
      Здоровье = new_var;
  }

  /**
   * Get the value of Здоровье
   * @return the value of Здоровье
   */
  int getЗдоровье ()   {
    return Здоровье;
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

#endif // ОБЪЕКТ_H
