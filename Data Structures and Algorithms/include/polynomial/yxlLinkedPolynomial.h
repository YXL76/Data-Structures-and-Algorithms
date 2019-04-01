/**
 * \Author: YXL
 * \LastUpdated: 2018/03/29 20:59:30
 * \Description:
 */

#pragma once

#ifndef YXL_LINKED_POLYNOMIAL_H
#define YXL_LINKED_POLYNOMIAL_H

#include "yxlPolynomial.h"
#include "../list/yxlLink.h"

class LinkedPolynomial final : yxlPolynomial
{
public:
	LinkedPolynomial() = default;
	explicit LinkedPolynomial(yxlLink<double>& that);
	LinkedPolynomial(const double coef[], const int& size);
	LinkedPolynomial(LinkedPolynomial& that) = default;
	LinkedPolynomial(LinkedPolynomial&& that) noexcept = default;
	~LinkedPolynomial() = default;

	void read(yxlLink<double>& that);
	void read(const double coef[], const int& size) override;
	double calculate(const double& x) override;
	LinkedPolynomial differentiate(const int& x);

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
	yxlLink<double> coef_;
	static void plus(LinkedPolynomial& answer, LinkedPolynomial& left, LinkedPolynomial& right);
	static void minus(LinkedPolynomial& answer, LinkedPolynomial& left, LinkedPolynomial& right);
	static void times(LinkedPolynomial& answer, LinkedPolynomial& left, LinkedPolynomial& right);
};

inline LinkedPolynomial::LinkedPolynomial(yxlLink<double>& that)
{
	read(that);
}

inline LinkedPolynomial::LinkedPolynomial(const double coef[], const int& size)
{
	read(coef, size);
}

inline void LinkedPolynomial::read(yxlLink<double>& that)
{
	coef_ = that;
}

inline void LinkedPolynomial::read(const double coef[], const int& size)
{
	for (auto i = size - 1; i >= 0; --i)
	{
		coef_.insert(0, coef[i]);
	}
}

inline double LinkedPolynomial::calculate(const double& x)
{
	double now = 1;
	double answer = 0;
	for (auto& i : coef_)
	{
		answer += i.value * now;
		now *= x;
	}
	return answer;
}

inline LinkedPolynomial LinkedPolynomial::differentiate(const int& x)
{
	LinkedPolynomial answer;
	for (auto i = coef_.begin() + x, j = answer.coef_.before_begin(); i != coef_.end(); ++i, ++j)
	{
		answer.coef_.insert(j, i->value);
	}
	auto expn = x;
	for (auto& it : answer.coef_)
	{
		for (auto i = 0; i < x; ++i)
		{
			it.value *= (double(expn) - double(i));
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
	auto l_it = left.coef_.begin();
	auto r_it = right.coef_.begin();
	auto a_it = answer.coef_.before_begin();
	for (; l_it != left.coef_.end() && r_it != right.coef_.end(); ++index, ++l_it, ++r_it, ++a_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(a_it, l_it->value + r_it->value); }
		else { a_it->next->value = l_it->value + r_it->value; }
	}
	for (; l_it != left.coef_.end(); ++index, ++l_it, ++a_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(a_it, l_it->value); }
		else { a_it->next->value = l_it->value; }
	}
	for (; r_it != right.coef_.end(); ++index, ++r_it, ++a_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(a_it, r_it->value); }
		else { a_it->next->value = r_it->value; }
	}
}

inline void LinkedPolynomial::minus(LinkedPolynomial& answer, LinkedPolynomial& left,
                                       LinkedPolynomial& right)
{
	auto index = 0;
	auto l_it = left.coef_.begin();
	auto r_it = right.coef_.begin();
	auto a_it = answer.coef_.before_begin();
	for (; l_it != left.coef_.end() && r_it != right.coef_.end(); ++index, ++l_it, ++r_it, ++a_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(a_it, l_it->value - r_it->value); }
		else { a_it->next->value = l_it->value + r_it->value; }
	}
	for (; l_it != left.coef_.end(); ++index, ++l_it, ++a_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(a_it, l_it->value); }
		else { a_it->next->value = l_it->value; }
	}
	for (; r_it != right.coef_.end(); ++index, ++r_it, ++a_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(a_it, -r_it->value); }
		else { a_it->next->value = -r_it->value; }
	}
}

inline void LinkedPolynomial::times(LinkedPolynomial& answer, LinkedPolynomial& left,
                                       LinkedPolynomial& right)
{
	auto l_expn = 0;
	auto l_it = left.coef_.begin();
	auto al_it = answer.coef_.before_begin();
	for (; l_it != left.coef_.end(); ++l_expn, ++l_it, ++al_it)
	{
		auto r_expn = l_expn;
		auto r_it = right.coef_.begin();
		auto ar_it = al_it;
		for (; r_it != right.coef_.end(); ++r_expn, ++r_it, ++ar_it)
		{
			if (r_expn >= answer.coef_.size())
			{
				answer.coef_.insert(ar_it, l_it->value * r_it->value);
			}
			else { ar_it->next->value += l_it->value * r_it->value; }
		}
	}
}

inline std::ostream& operator<<(std::ostream& out, LinkedPolynomial& item)
{
	for (auto& i : item.coef_)
	{
		out << i.value << ' ';
	}
	return out;
}

inline std::ostream& operator<<(std::ostream& out, LinkedPolynomial&& item)
{
	for (auto& i : item.coef_)
	{
		out << i.value << ' ';
	}
	return out;
}

#endif // !YXL_LINKED_POLYNOMIAL_H
