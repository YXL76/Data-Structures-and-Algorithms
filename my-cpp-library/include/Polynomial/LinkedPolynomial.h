#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/29 20:59:30
 * \Description:
 */

#ifndef LINKED_POLYNOMIAL_H
#define LINKED_POLYNOMIAL_H

#include "Polynomial.h"
#include "../List/Link.h"

namespace yxl
{
    class LinkedPolynomial final : public Link<double>,
                                   public Polynomial<LinkedPolynomial>
    {
    public:
        LinkedPolynomial() = default;
        explicit LinkedPolynomial(const Link<double>& that);
        explicit LinkedPolynomial(Link<double>&& that);
        LinkedPolynomial(const double coef[], const int& size);
        LinkedPolynomial(LinkedPolynomial& that) = default;
        LinkedPolynomial(LinkedPolynomial&& that) noexcept = default;
        ~LinkedPolynomial() override = default;

        void read(const double coef[], const int& size) override;
        double calculate(const double& x) override;
        LinkedPolynomial differentiate(const int& x) override;

        LinkedPolynomial operator+(LinkedPolynomial& right);
        LinkedPolynomial operator-(LinkedPolynomial& right);
        LinkedPolynomial operator*(LinkedPolynomial& right);

        LinkedPolynomial& operator=(const LinkedPolynomial& right) = default;
        LinkedPolynomial& operator=(LinkedPolynomial&& right) noexcept = default;
        LinkedPolynomial& operator+=(LinkedPolynomial& right);
        LinkedPolynomial& operator-=(LinkedPolynomial& right);
        LinkedPolynomial& operator*=(LinkedPolynomial& right);

        friend std::ostream& operator<<(std::ostream& out, LinkedPolynomial& item);
        friend std::ostream& operator<<(std::ostream& out, LinkedPolynomial&& item);

    private:
        void plus(LinkedPolynomial& answer, LinkedPolynomial& left, LinkedPolynomial& right) override;
        void minus(LinkedPolynomial& answer, LinkedPolynomial& left, LinkedPolynomial& right) override;
        void times(LinkedPolynomial& answer, LinkedPolynomial& left, LinkedPolynomial& right) override;

        LinkedPolynomial times(LinkedPolynomial& /*left*/, LinkedPolynomial& /*right*/) const override { return {}; }
    };

    inline LinkedPolynomial::LinkedPolynomial(const Link<double>& that) : Link<double>(that)
    {
    }

    inline LinkedPolynomial::LinkedPolynomial(Link<double>&& that) : Link<double>(that)
    {
    }

    inline LinkedPolynomial::LinkedPolynomial(const double coef[], const int& size)
    {
        read(coef, size);
    }

    inline void LinkedPolynomial::read(const double coef[], const int& size)
    {
        for (auto i = size - 1; i >= 0; --i)
        {
            insert(0, coef[i]);
        }
    }

    inline double LinkedPolynomial::calculate(const double& x)
    {
        double now = 1;
        double answer = 0;
        for (auto& i : *this)
        {
            answer += i.value * now;
            now *= x;
        }
        return answer;
    }

    inline LinkedPolynomial LinkedPolynomial::differentiate(const int& x)
    {
        LinkedPolynomial answer;
        for (auto i = begin() + x, j = answer.before_begin(); i != end(); ++i, ++j)
        {
            answer.insert(j, i->value);
        }
        auto expn = x;
        for (auto& it : answer)
        {
            for (auto i = 0; i < x; ++i)
            {
                it.value *= double(expn) - double(i);
            }
            ++expn;
        }
        return answer;
    }

    inline LinkedPolynomial LinkedPolynomial::operator+(LinkedPolynomial& right)
    {
        LinkedPolynomial answer;
        plus(answer, *this, right);
        return answer;
    }

    inline LinkedPolynomial LinkedPolynomial::operator-(LinkedPolynomial& right)
    {
        LinkedPolynomial answer;
        minus(answer, *this, right);
        return answer;
    }

    inline LinkedPolynomial LinkedPolynomial::operator*(LinkedPolynomial& right)
    {
        LinkedPolynomial answer;
        times(answer, *this, right);
        return answer;
    }

    inline LinkedPolynomial& LinkedPolynomial::operator+=(LinkedPolynomial& right)
    {
        plus(*this, *this, right);
        return *this;
    }

    inline LinkedPolynomial& LinkedPolynomial::operator-=(LinkedPolynomial& right)
    {
        minus(*this, *this, right);
        return *this;
    }

    inline LinkedPolynomial& LinkedPolynomial::operator*=(LinkedPolynomial& right)
    {
        times(*this, *this, right);
        return *this;
    }

    inline void LinkedPolynomial::plus(LinkedPolynomial& answer, LinkedPolynomial& left,
                                       LinkedPolynomial& right)
    {
        auto index = 0;
        auto l_it = left.begin();
        auto r_it = right.begin();
        auto a_it = answer.before_begin();
        for (; l_it != left.end() && r_it != right.end(); ++index, ++l_it, ++r_it, ++a_it)
        {
            if (index == answer.size()) { answer.insert(a_it, l_it->value + r_it->value); }
            else { a_it->next->value = l_it->value + r_it->value; }
        }
        for (; l_it != left.end(); ++index, ++l_it, ++a_it)
        {
            if (index == answer.size()) { answer.insert(a_it, l_it->value); }
            else { a_it->next->value = l_it->value; }
        }
        for (; r_it != right.end(); ++index, ++r_it, ++a_it)
        {
            if (index == answer.size()) { answer.insert(a_it, r_it->value); }
            else { a_it->next->value = r_it->value; }
        }
    }

    inline void LinkedPolynomial::minus(LinkedPolynomial& answer, LinkedPolynomial& left,
                                        LinkedPolynomial& right)
    {
        auto index = 0;
        auto l_it = left.begin();
        auto r_it = right.begin();
        auto a_it = answer.before_begin();
        for (; l_it != left.end() && r_it != right.end(); ++index, ++l_it, ++r_it, ++a_it)
        {
            if (index == answer.size()) { answer.insert(a_it, l_it->value - r_it->value); }
            else { a_it->next->value = l_it->value + r_it->value; }
        }
        for (; l_it != left.end(); ++index, ++l_it, ++a_it)
        {
            if (index == answer.size()) { answer.insert(a_it, l_it->value); }
            else { a_it->next->value = l_it->value; }
        }
        for (; r_it != right.end(); ++index, ++r_it, ++a_it)
        {
            if (index == answer.size()) { answer.insert(a_it, -r_it->value); }
            else { a_it->next->value = -r_it->value; }
        }
    }

    inline void LinkedPolynomial::times(LinkedPolynomial& answer, LinkedPolynomial& left,
                                        LinkedPolynomial& right)
    {
        auto l_expn = 0;
        auto l_it = left.begin();
        auto al_it = answer.before_begin();
        for (; l_it != left.end(); ++l_expn, ++l_it, ++al_it)
        {
            auto r_expn = l_expn;
            auto r_it = right.begin();
            auto ar_it = al_it;
            for (; r_it != right.end(); ++r_expn, ++r_it, ++ar_it)
            {
                if (r_expn >= answer.size())
                {
                    answer.insert(ar_it, l_it->value * r_it->value);
                }
                else { ar_it->next->value += l_it->value * r_it->value; }
            }
        }
    }

    inline std::ostream& operator<<(std::ostream& out, LinkedPolynomial& item)
    {
        for (auto& i : item)
        {
            out << i.value << ' ';
        }
        out << std::endl;
        return out;
    }

    inline std::ostream& operator<<(std::ostream& out, LinkedPolynomial&& item)
    {
        for (auto& i : item)
        {
            out << i.value << ' ';
        }
        out << std::endl;
        return out;
    }
} // namespace yxl

#endif // !LINKED_POLYNOMIAL_H
