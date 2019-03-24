/**
 * \Author: YXL
 * \LastUpdated: 2018/03/25 01:00:00
 * \description:
 */

#pragma once

#ifndef YXL_CHAIN_POLYNOMIAL_H
#define YXL_CHAIN_POLYNOMIAL_H

#include "yxlPolynomial.h"

class yxlChainPolynomial final : yxlPolynomial
{
public:
	yxlChainPolynomial() = default;
	explicit yxlChainPolynomial(yxlChain<double>& that);
	yxlChainPolynomial(yxlChainPolynomial& that) = default;
	yxlChainPolynomial(yxlChainPolynomial&& that) noexcept = default;
	~yxlChainPolynomial() = default;

	void read(yxlChain<double>& that) override;
	void read(const double coef[], const int& size) override;
	void write() const override;
	void plus(yxlChainPolynomial& that);
	void minus(yxlChainPolynomial& that);
	void times(yxlChainPolynomial& that);
	double calculate(const double& x) override;
	yxlChainPolynomial differentiate(const int& x);

	yxlChainPolynomial operator+(yxlChainPolynomial& right);
	yxlChainPolynomial operator-(yxlChainPolynomial& right);
	yxlChainPolynomial operator*(yxlChainPolynomial& right);

	yxlChainPolynomial& operator=(const yxlChainPolynomial& right) = default;
	yxlChainPolynomial& operator=(yxlChainPolynomial&& right) noexcept = default;
	yxlChainPolynomial& operator+=(yxlChainPolynomial& right);
	yxlChainPolynomial& operator-=(yxlChainPolynomial& right);
	yxlChainPolynomial& operator*=(yxlChainPolynomial& right);

	friend std::ostream& operator<<(std::ostream& out, yxlChainPolynomial& item);
	friend std::ostream& operator<<(std::ostream& out, yxlChainPolynomial&& item);

private:
	yxlChain<double> coef_;
};

inline yxlChainPolynomial::yxlChainPolynomial(yxlChain<double>& that)
{
	coef_ = that;
}

inline void yxlChainPolynomial::read(yxlChain<double>& that)
{
	coef_ = that;
}

inline void yxlChainPolynomial::read(const double coef[], const int& size)
{
	for (auto i = size - 1; i >= 0; --i)
	{
		coef_.insert(0, coef[i]);
	}
}

inline void yxlChainPolynomial::write() const
{
	std::cout << coef_;
}

inline void yxlChainPolynomial::plus(yxlChainPolynomial& that)
{
	auto this_it = coef_.begin();
	auto that_it = that.coef_.begin();
	while (this_it != coef_.end() && that_it != that.coef_.end())
	{
		this_it->value += that_it->value;
		++this_it;
		++that_it;
	}
	while (that_it != that.coef_.end())
	{
		coef_.insert(coef_.size(), that_it->value);
		++that_it;
	}
}

inline void yxlChainPolynomial::minus(yxlChainPolynomial& that)
{
	auto this_it = coef_.begin();
	auto that_it = that.coef_.begin();
	while (this_it != coef_.end() && that_it != that.coef_.end())
	{
		this_it->value -= that_it->value;
		++this_it;
		++that_it;
	}
	while (that_it != that.coef_.end())
	{
		coef_.insert(coef_.size(), -that_it->value);
		++that_it;
	}
}

inline double yxlChainPolynomial::calculate(const double& x)
{
	double now = 1;
	double answer = 0;
	auto it = coef_.begin();
	while (it != coef_.end())
	{
		answer += it->value * now;
		now *= x;
		++it;
	}
	return answer;
}

inline yxlChainPolynomial yxlChainPolynomial::differentiate(const int& x)
{
	auto old = *this;
	for (auto i = 0; i < x; ++i) { coef_.erase(0); }
	auto expn = x;
	auto it = old.coef_.begin();
	while (it != old.coef_.end())
	{
		for (auto i = 1; i <= x; ++i)
		{
			it->value *= (double(expn) - double(i));
		}
		++expn;
		++it;
	}
	return old;
}

inline yxlChainPolynomial yxlChainPolynomial::operator+(yxlChainPolynomial& right)
{
	auto old = *this;
	auto this_it = old.coef_.begin();
	auto that_it = right.coef_.begin();
	while (this_it != old.coef_.end() && that_it != right.coef_.end())
	{
		this_it->value += that_it->value;
		++this_it;
		++that_it;
	}
	while (that_it != right.coef_.end())
	{
		old.coef_.insert(old.coef_.size(), that_it->value);
		++that_it;
	}
	return old;
}

inline yxlChainPolynomial yxlChainPolynomial::operator-(yxlChainPolynomial& right)
{
	auto old = *this;
	auto this_it = old.coef_.begin();
	auto that_it = right.coef_.begin();
	while (this_it != old.coef_.end() && that_it != right.coef_.end())
	{
		this_it->value -= that_it->value;
		++this_it;
		++that_it;
	}
	while (that_it != right.coef_.end())
	{
		old.coef_.insert(old.coef_.size(), -that_it->value);
		++that_it;
	}
	return old;
}

inline yxlChainPolynomial& yxlChainPolynomial::operator+=(yxlChainPolynomial& right)
{
	this->plus(right);
	return *this;
}

inline yxlChainPolynomial& yxlChainPolynomial::operator-=(yxlChainPolynomial& right)
{
	this->minus(right);
	return *this;
}

inline std::ostream& operator<<(std::ostream& out, yxlChainPolynomial& item)
{
	auto it = item.coef_.begin();
	while (it != item.coef_.end())
	{
		out << it->value << ' ';
		++it;
	}
	return out;
}

inline std::ostream& operator<<(std::ostream& out, yxlChainPolynomial&& item)
{
	auto it = item.coef_.begin();
	while (it != item.coef_.end())
	{
		out << it->value << ' ';
		++it;
	}
	return out;
}

#endif // !YXL_POLYNOMIAL_H
