#include <iostream>
#include "bigint.h"

void BigInt::CopyOnly(const BigInt &other)
{
        ListItem *t;
        SetZero();
        isNegative = other.isNegative;
        length = other.length;
        t = other.first;

        for (GoToFirst(); t != NULL; t = t->next)
        {
                AddAfter(t->digit);
                if (first != last) GoToNext();
        }
}

void BigInt::Clean()
{
        cur = first;
        while (first)
        {
                cur = first->next;
                delete first;
                first = cur;
        }
        SetZero();
}

void BigInt::AddAfter(char dig)
{
        ListItem *i = new ListItem();
        i->digit = dig;
        if (first == NULL) cur = last = first = i;
        else
        {
                i->prev = cur;
                i->next = cur->next;
                cur->next = i;
                if (i->next) i->next->prev = i;
                else last = i;
        }
}

void BigInt::AddCur(char dig)
{
        if (first == NULL) AddAfter(0);
        cur->digit = dig;
}

BigInt::BigInt(int64_t number)
{
        SetZero();
        if (number == 0)
        {
                isNegative = false;
                AddAfter((char)0);
                length++;
        }
        else
        {
                if (number < 0)
                {
                        isNegative = true;
                        number = -number;
                }

                int64_t temp = number;
                while (temp != 0)
                {
                        length++;
                        temp /= 10;
                }

                for (size_t i = 0, GoToFirst(); i < length; i++)
                {
                        AddAfter((char)(number % 10));
                        number /= 10;
                        if (first != last) GoToNext();
                }
        }
}

const BigInt BigInt::operator+ (const BigInt& other) const
{
        BigInt res;
        if (!isNegative && other.isNegative)
        {
                BigInt temp = other;
                temp.isNegative = false;
                res = *this - temp;
        }
        if (isNegative && !other.isNegative)
        {
                BigInt temp = *this, y = other;
                temp.isNegative = false;
                res = y - temp;
        }
        if ((isNegative + other.isNegative) % 2 == 0)
        {
                res.isNegative = isNegative;
                ListItem *t = new ListItem();
                ListItem *y = new ListItem();
                for (t = other.first, y = first, res.GoToFirst(); (y != NULL) && (t != NULL); y = y->next, t = t->next, res.GoToNext())
                {
                        int64_t d = res.GetCurrent() + t->digit + y->digit;
                        if (d / 10 != 0)
                        {
                                res.AddCur((char)(d % 10));
                                res.AddAfter(1);
                        }
                        else
                        {
                                res.AddCur((char)d);
                                res.AddAfter(0);
                        }
                }
                while (y != NULL)
                {
                        int64_t d = res.GetCurrent() + y->digit;
                        if (d / 10 != 0)
                        {
                                res.AddCur((char)(d % 10));
                                res.AddAfter(1);
                        }
                        else
                        {
                                res.AddCur((char)d);
                                res.AddAfter(0);
                        }
                        res.GoToNext();
                        y = y->next;
                }
                while (t != NULL)
                {
                        int64_t d = res.GetCurrent() + t->digit;
                        if (d / 10 != 0)
                        {
                                res.AddCur((char)(d % 10));
                                res.AddAfter(1);
                        }
                        else
                        {
                                res.AddCur((char)d);
                                res.AddAfter(0);
                        }
                        res.GoToNext();
                        t = t->next;
                }
        }

        res.GoToLast();
        while (!res.IsEmpty() && !(res.GetCurrent()) && (res.first != res.last))
        {
                res.cur = res.last->prev;
                delete res.last;
                res.last = res.cur;
                res.last->next = NULL;
        }

        res.length = 0;
        for (res.GoToFirst(); !res.IsEmpty(); res.GoToNext()) res.length++;

        return res;
}

const BigInt BigInt::operator- (const BigInt &other) const
{
        BigInt res;
        if (!isNegative && other.isNegative)
        {
                BigInt temp = other;
                temp.isNegative = false;
                res = *this + temp;
                res.isNegative = false;
        }
        if (isNegative && !other.isNegative)
        {
                BigInt temp = *this;
                temp.isNegative = false;
                res = temp + other;
                res.isNegative = true;
        }
        if (!isNegative && !other.isNegative)
        {
                if (*this >= other)
                {
                        res.isNegative = false;
                        ListItem *t = new ListItem();
                        ListItem *y = new ListItem();
                        for (t = other.first, y = first, res.GoToFirst(); (y != NULL) && (t != NULL); y = y->next, t = t->next, res.GoToNext())
                        {
                                int64_t d = y->digit - t->digit;
                                if (d < 0)
                                {
                                        ListItem *p = new ListItem();
                                        p = y->next;
                                        while (p->digit == 0)
                                        {
                                                p->digit = (char)9;
                                                p = p->next;
                                        }
                                        p->digit--;

                                        d += 10;
                                }

                                res.AddCur((char)d);
                                if (y->next) res.AddAfter(0);
                        }
                        while (y != NULL)
                        {
                                res.AddCur(GetCurrent());
                                if (y->next) res.AddAfter(0);

                                res.GoToNext();
                                y = y->next;
                        }
                }
                else
                {
                        BigInt temp;
                        temp = other;
                        res = temp - *this;
                        res.isNegative = true;
                }
        }
        if (isNegative && other.isNegative)
        {
                if (*this <= other)
                {
                        res.isNegative = true;
                        ListItem *y = new ListItem();
                        ListItem *t = new ListItem();
                        for (t = other.first, y = first, res.GoToFirst(); (y != NULL) && (t != NULL); y = y->next, t = t->next, res.GoToNext())
                        {
                                int64_t d = y->digit - t->digit;
                                if (d < 0)
                                {
                                        ListItem *p = new ListItem();
                                        p = y->next;
                                        while (p->digit == 0)
                                        {
                                                p->digit = (char)9;
                                                p = p->next;
                                        }
                                        p->digit--;

                                        d += 10;
                                }

                                res.AddCur((char)d);
                                if (y->next) res.AddAfter(0);
                        }
                        while (y != NULL)
                        {
                                res.AddCur(GetCurrent());
                                if (y->next) res.AddAfter(0);

                                res.GoToNext();
                                y = y->next;
                        }
                }
                else
                {
                        BigInt temp;
                        temp = other;
                        res = temp - *this;
                        res.isNegative = true;
                }
        }

        res.GoToLast();
        while (!res.IsEmpty() && !(res.GetCurrent()) && (res.first != res.last))
        {
                res.cur = res.last->prev;
                delete res.last;
                res.last = res.cur;
                res.last->next = NULL;
        }

        for (res.GoToFirst(); !res.IsEmpty(); res.GoToNext()) res.length++;
        if (res.first == res.last && res.first->digit == ((char)0))
                res.isNegative = false;
        return res;
}

const BigInt BigInt::operator* (char num) const
{
        BigInt res;

        ListItem *y = new ListItem();
        for (y = first, res.GoToFirst(); (y != NULL); y = y->next, res.GoToNext())
        {
                int64_t d = res.GetCurrent() + (y->digit)*num;
                if (d / 10 != 0)
                {
                        res.AddCur((char)(d % 10));
                        res.AddAfter((char)(d / 10));
                }
                else
                {
                        res.AddCur((char)d);
                        if (y->next) res.AddAfter(0);
                }
        }

        for (res.GoToFirst(); !res.IsEmpty(); res.GoToNext()) res.length++;

        return res;
}

const BigInt BigInt::operator* (const BigInt &other) const
{
        BigInt res, y = *this;

        ListItem *t = new ListItem();
        ListItem *p = new ListItem();
        p = res.first;

        for (t = other.first; (t != NULL); t = t->next, p = p->next)
        {
                BigInt temp;
                temp = y * t->digit;
                for (temp.GoToFirst(), res.cur = p; !temp.IsEmpty(); temp.GoToNext(), res.GoToNext())
                {
                        int64_t d = res.GetCurrent() + temp.GetCurrent();
                        if (d / 10 != 0)
                        {
                                res.AddCur((char)(d % 10));
                                if (res.cur->next) res.cur->next->digit++;
                                else res.AddAfter(1);
                        }
                        else
                        {
                                res.AddCur((char)d);
                                if (!res.cur->next) res.AddAfter(0);
                        }
                }
        }

        res.GoToLast();
        while (!res.IsEmpty() && !(res.GetCurrent()) && (res.first != res.last))
        {
                res.cur = res.last->prev;
                delete res.last;
                res.last = res.cur;
                res.last->next = NULL;
        }

        for (res.GoToFirst(); !res.IsEmpty(); res.GoToNext()) res.length++;
        res.isNegative = (isNegative + other.isNegative) % 2;

        if (res.first == res.last && res.first->digit == ((char)0))
                res.isNegative = false;

        return res;
}

const BigInt BigInt::operator/ (const BigInt &other) const
{
        BigInt zero(0), one(1);
        if (length < other.length) return zero;

        BigInt res, t1 = *this, t2 = other;
        res.AddCur(0);

        t1.isNegative = false;
        t2.isNegative = false;

        while (t1 >= t2)
        {
                t1 = t1 - t2;
                res = res + one;
        }

        res.isNegative = (isNegative + other.isNegative) % 2;
        if (res.first == res.last && res.first->digit == ((char)0))
        {
                res.isNegative = false;
                res.length = 1;
        }

        return res;
}

BigInt& BigInt::operator- ()
{
        if (first == last && first->digit == ((char)0))
                isNegative = false;
        else isNegative = !isNegative;
        return *this;
}

bool BigInt::operator == (const BigInt &other) const
{
        if (isNegative != other.isNegative) return false;
        else
        {
                if (length != other.length) return false;
                else
                {
                        ListItem *t = new ListItem();
                        ListItem *y = new ListItem();
                        for (t = other.last, y = last; t != NULL; t = t->prev, y = y->prev)
                        {
                                if ((int64_t)y->digit != (int64_t)t->digit) return false;
                        }
                }
        }
        return true;
}

bool BigInt::operator > (const BigInt &other) const
{
        if (isNegative < other.isNegative) return true;
        if (isNegative > other.isNegative) return false;
        else
        {
                if (isNegative && other.isNegative)
                {
                        if (length < other.length) return true;
                        else if (length > other.length) return false;
                        else
                        {
                                ListItem *t = new ListItem();
                                ListItem *y = new ListItem();
                                for (t = other.last, y = last; t != NULL; t = t->prev, y = y->prev)
                                {
                                        if ((int64_t)y->digit < (int64_t)t->digit) return true;
                                        else if ((int64_t)y->digit > (int64_t)t->digit) return false;
                                }
                        }
                }
                if (!isNegative && !other.isNegative)
                {
                        if (length > other.length) return true;
                        else if (length < other.length) return false;
                        else
                        {
                                ListItem *t = new ListItem();
                                ListItem *y = new ListItem();
                                for (t = other.last, y = last; t != NULL; t = t->prev, y = y->prev)
                                {
                                        if ((int64_t)y->digit > (int64_t)t->digit) return true;
                                        else if ((int64_t)y->digit < (int64_t)t->digit) return false;
                                }
                        }
                }
        }
        return false;
}

bool BigInt::operator < (const BigInt &other) const
{
        if (isNegative > other.isNegative) return true;
        if (isNegative < other.isNegative) return false;
        else
        {
                if (isNegative && other.isNegative)
                {
                        if (length > other.length) return true;
                        else if (length < other.length) return false;
                        else
                        {
                                ListItem *t = new ListItem();
                                ListItem *y = new ListItem();
                                for (t = other.last, y = last; t != NULL; t = t->prev, y = y->prev)
                                {
                                        if ((int64_t)y->digit > (int64_t)t->digit) return true;
                                        else if ((int64_t)y->digit < (int64_t)t->digit) return false;
                                }
                        }
                }
                if (!isNegative && !other.isNegative)
                {
                        if (length < other.length) return true;
                        else if (length > other.length) return false;
                        else
                        {
                                ListItem *t = new ListItem();
                                ListItem *y = new ListItem();
                                for (t = other.last, y = last; t != NULL; t = t->prev, y = y->prev)
                                {
                                        if ((int64_t)y->digit < (int64_t)t->digit) return true;
                                        else if ((int64_t)y->digit > (int64_t)t->digit) return false;
                                }
                        }
                }
        }
        return false;
}

std::ostream &operator << (std::ostream& str, const BigInt& print)
{
        if (print.isNegative) str << "-";
        ListItem *t = new ListItem();
        for (t = print.last; t != NULL; t = t->prev)
                str << (int64_t) t->digit;
        str << std::endl;
        return str;
}
