/**
 * \Author: YXL
 * \LastUpdated: 2018/03/29 14:29:40
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
	yxlChainPolynomial(const double coef[], const int& size);
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

inline yxlChainPolynomial::yxlChainPolynomial(const double coef[], const int& size)
{
	for (auto i = size - 1; i >= 0; --i)
	{
		coef_.insert(0, coef[i]);
	}
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
	*this = *this + that;
}

inline void yxlChainPolynomial::minus(yxlChainPolynomial& that)
{
	*this = *this - that;
}

inline void yxlChainPolynomial::times(yxlChainPolynomial& that)
{
	*this = *this * that;
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
	yxlChainPolynomial answer;
	auto it = coef_.begin() + x;
	auto answer_it = answer.coef_.before_begin();
	while (it != coef_.end())
	{
		answer.coef_.insert(answer_it, it->value);
		++it;
		++answer_it;
	}
	auto expn = x;
	answer_it = answer.coef_.begin();
	while (answer_it != answer.coef_.end())
	{
		for (auto i = 0; i < x; ++i)
		{
			answer_it->value *= (double(expn) - double(i));
		}
		++expn;
		++answer_it;
	}
	return answer;
}

inline yxlChainPolynomial yxlChainPolynomial::operator+(yxlChainPolynomial& right)
{
	yxlChainPolynomial answer;
	auto left_it = coef_.begin();
	auto right_it = right.coef_.begin();
	auto answer_it = answer.coef_.before_begin();
	while (left_it != coef_.end() && right_it != right.coef_.end())
	{
		answer.coef_.insert(answer_it, left_it->value + right_it->value);
		++left_it;
		++right_it;
		++answer_it;
	}
	while (left_it != coef_.end())
	{
		answer.coef_.insert(answer_it, left_it->value);
		++left_it;
		++answer_it;
	}
	while (right_it != right.coef_.end())
	{
		answer.coef_.insert(answer_it, right_it->value);
		++right_it;
		++answer_it;
	}
	return answer;
}

inline yxlChainPolynomial yxlChainPolynomial::operator-(yxlChainPolynomial& right)
{
	yxlChainPolynomial answer;
	auto left_it = coef_.begin();
	auto right_it = right.coef_.begin();
	auto answer_it = answer.coef_.before_begin();
	while (left_it != coef_.end() && right_it != right.coef_.end())
	{
		answer.coef_.insert(answer_it, left_it->value - right_it->value);
		++left_it;
		++right_it;
		++answer_it;
	}
	while (left_it != coef_.end())
	{
		answer.coef_.insert(answer_it, -left_it->value);
		++left_it;
		++answer_it;
	}
	while (right_it != right.coef_.end())
	{
		answer.coef_.insert(answer_it, -right_it->value);
		++right_it;
		++answer_it;
	}
	return answer;
}

inline yxlChainPolynomial yxlChainPolynomial::operator*(yxlChainPolynomial& right)
{
	yxlChainPolynomial answer;
	auto left_expn = 0;
	auto left_it = coef_.begin();
	auto answer_it = answer.coef_.before_begin();
	while (left_it != coef_.end())
	{
		auto right_expn = 0;
		auto right_it = right.coef_.begin();
		while (right_it != right.coef_.end())
		{
			const auto expn = left_expn + right_expn;
			if (expn >= int(answer.coef_.size()))
			{
				answer.coef_.insert(answer_it, left_it->value * right_it->value);
				++answer_it;
			}
			else { answer.coef_[expn] += left_it->value * right_it->value; }
			++right_expn;
			++right_it;
		}
		++left_expn;
		++left_it;
	}
	return answer;
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

inline yxlChainPolynomial& yxlChainPolynomial::operator*=(yxlChainPolynomial& right)
{
	this->times(right);
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
