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

class yxlLinkedPolynomial final : yxlPolynomial
{
public:
	yxlLinkedPolynomial() = default;
	explicit yxlLinkedPolynomial(yxlLink<double>& that);
	yxlLinkedPolynomial(const double coef[], const int& size);
	yxlLinkedPolynomial(yxlLinkedPolynomial& that) = default;
	yxlLinkedPolynomial(yxlLinkedPolynomial&& that) noexcept = default;
	~yxlLinkedPolynomial() = default;

	void read(yxlLink<double>& that);
	void read(const double coef[], const int& size) override;
	double calculate(const double& x) override;
	yxlLinkedPolynomial differentiate(const int& x);

	yxlLinkedPolynomial operator+(yxlLinkedPolynomial& right);
	yxlLinkedPolynomial operator-(yxlLinkedPolynomial& right);
	yxlLinkedPolynomial operator*(yxlLinkedPolynomial& right);

	yxlLinkedPolynomial& operator=(const yxlLinkedPolynomial& right) = default;
	yxlLinkedPolynomial& operator=(yxlLinkedPolynomial&& right) noexcept = default;
	yxlLinkedPolynomial& operator+=(yxlLinkedPolynomial& right);
	yxlLinkedPolynomial& operator-=(yxlLinkedPolynomial& right);
	yxlLinkedPolynomial& operator*=(yxlLinkedPolynomial& right);

	friend std::ostream& operator<<(std::ostream& out, yxlLinkedPolynomial& item);
	friend std::ostream& operator<<(std::ostream& out, yxlLinkedPolynomial&& item);

private:
	yxlLink<double> coef_;
	static void plus(yxlLinkedPolynomial& answer, yxlLinkedPolynomial& left, yxlLinkedPolynomial& right);
	static void minus(yxlLinkedPolynomial& answer, yxlLinkedPolynomial& left, yxlLinkedPolynomial& right);
	static void times(yxlLinkedPolynomial& answer, yxlLinkedPolynomial& left, yxlLinkedPolynomial& right);
};

inline yxlLinkedPolynomial::yxlLinkedPolynomial(yxlLink<double>& that)
{
	read(that);
}

inline yxlLinkedPolynomial::yxlLinkedPolynomial(const double coef[], const int& size)
{
	read(coef, size);
}

inline void yxlLinkedPolynomial::read(yxlLink<double>& that)
{
	coef_ = that;
}

inline void yxlLinkedPolynomial::read(const double coef[], const int& size)
{
	for (auto i = size - 1; i >= 0; --i)
	{
		coef_.insert(0, coef[i]);
	}
}

inline double yxlLinkedPolynomial::calculate(const double& x)
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

inline yxlLinkedPolynomial yxlLinkedPolynomial::differentiate(const int& x)
{
	yxlLinkedPolynomial answer;
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

inline yxlLinkedPolynomial yxlLinkedPolynomial::operator+(yxlLinkedPolynomial& right)
{
	yxlLinkedPolynomial answer;
	plus(answer, *this, right);
	return answer;
}

inline yxlLinkedPolynomial yxlLinkedPolynomial::operator-(yxlLinkedPolynomial& right)
{
	yxlLinkedPolynomial answer;
	minus(answer, *this, right);
	return answer;
}

inline yxlLinkedPolynomial yxlLinkedPolynomial::operator*(yxlLinkedPolynomial& right)
{
	yxlLinkedPolynomial answer;
	times(answer, *this, right);
	return answer;
}

inline yxlLinkedPolynomial& yxlLinkedPolynomial::operator+=(yxlLinkedPolynomial& right)
{
	plus(*this, *this, right);
	return *this;
}

inline yxlLinkedPolynomial& yxlLinkedPolynomial::operator-=(yxlLinkedPolynomial& right)
{
	minus(*this, *this, right);
	return *this;
}

inline yxlLinkedPolynomial& yxlLinkedPolynomial::operator*=(yxlLinkedPolynomial& right)
{
	times(*this, *this, right);
	return *this;
}

inline void yxlLinkedPolynomial::plus(yxlLinkedPolynomial& answer, yxlLinkedPolynomial& left,
                                      yxlLinkedPolynomial& right)
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

inline void yxlLinkedPolynomial::minus(yxlLinkedPolynomial& answer, yxlLinkedPolynomial& left,
                                       yxlLinkedPolynomial& right)
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

inline void yxlLinkedPolynomial::times(yxlLinkedPolynomial& answer, yxlLinkedPolynomial& left,
                                       yxlLinkedPolynomial& right)
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

inline std::ostream& operator<<(std::ostream& out, yxlLinkedPolynomial& item)
{
	for (auto& i : item.coef_)
	{
		out << i.value << ' ';
	}
	return out;
}

inline std::ostream& operator<<(std::ostream& out, yxlLinkedPolynomial&& item)
{
	for (auto& i : item.coef_)
	{
		out << i.value << ' ';
	}
	return out;
}

#endif // !YXL_LINKED_POLYNOMIAL_H
