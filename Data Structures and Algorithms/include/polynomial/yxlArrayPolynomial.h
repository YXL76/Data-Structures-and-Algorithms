/**
 * \Author: YXL
 * \LastUpdated: 2018/03/29 23:04:20
 * \Description:
 */

#pragma once

#ifndef YXL_ARRAY_POLYNOMIAL_H
#define YXL_ARRAY_POLYNOMIAL_H

#include "yxlPolynomial.h"
#include "../list/yxlArray.h"
#include <complex>

constexpr double kPi = 3.1415926;

class yxlArrayPolynomial final : yxlPolynomial
{
public:
	using comp = std::complex<double>;

	yxlArrayPolynomial() = default;
	explicit yxlArrayPolynomial(const int& initial_size);
	explicit yxlArrayPolynomial(yxlArray<double>& that);
	yxlArrayPolynomial(const double coef[], const int& size);
	yxlArrayPolynomial(yxlArrayPolynomial& that) = default;
	yxlArrayPolynomial(yxlArrayPolynomial&& that) noexcept = default;
	~yxlArrayPolynomial() = default;

	void read(yxlArray<double>& that);
	void read(const double coef[], const int& size) override;
	double calculate(const double& x) override;
	yxlArrayPolynomial differentiate(const int& x);

	yxlArrayPolynomial operator+(yxlArrayPolynomial& right);
	yxlArrayPolynomial operator-(yxlArrayPolynomial& right);
	yxlArrayPolynomial operator*(yxlArrayPolynomial& right);

	yxlArrayPolynomial& operator=(const yxlArrayPolynomial& right) = default;
	yxlArrayPolynomial& operator=(yxlArrayPolynomial&& right) noexcept = default;
	yxlArrayPolynomial& operator+=(yxlArrayPolynomial& right);
	yxlArrayPolynomial& operator-=(yxlArrayPolynomial& right);
	yxlArrayPolynomial& operator*=(yxlArrayPolynomial& right);

	friend std::ostream& operator<<(std::ostream& out, yxlArrayPolynomial& item);
	friend std::ostream& operator<<(std::ostream& out, yxlArrayPolynomial&& item);

private:
	yxlArray<double> coef_;
	static void plus(yxlArrayPolynomial& answer, yxlArrayPolynomial& left, yxlArrayPolynomial& right);
	static void minus(yxlArrayPolynomial& answer, yxlArrayPolynomial& left, yxlArrayPolynomial& right);
	yxlArrayPolynomial times(yxlArrayPolynomial& left, yxlArrayPolynomial& right) const;
	void cooley_tukey(yxlArray<comp>& that, bool inverse) const;
};

inline yxlArrayPolynomial::yxlArrayPolynomial(const int& initial_size): coef_(initial_size)
{
}

inline yxlArrayPolynomial::yxlArrayPolynomial(yxlArray<double>& that)
{
	read(that);
}

inline yxlArrayPolynomial::yxlArrayPolynomial(const double coef[], const int& size)
{
	read(coef, size);
}

inline void yxlArrayPolynomial::read(yxlArray<double>& that)
{
	coef_ = that;
}

inline void yxlArrayPolynomial::read(const double coef[], const int& size)
{
	for (auto i = 0; i < size; ++i)
	{
		coef_.insert(i, coef[i]);
	}
}

inline double yxlArrayPolynomial::calculate(const double& x)
{
	double now = 1;
	double answer = 0;
	for (auto& i : coef_)
	{
		answer += i * now;
		now *= x;
	}
	return answer;
}

inline yxlArrayPolynomial yxlArrayPolynomial::differentiate(const int& x)
{
	yxlArrayPolynomial answer;
	auto expn = x;
	for (auto i = x; i < coef_.size(); ++i)
	{
		answer.coef_.insert(answer.coef_.size(), coef_[i]);
	}
	for (auto& it : answer.coef_)
	{
		for (auto i = 0; i < x; ++i)
		{
			it *= (double(expn) - double(i));
		}
		++expn;
	}
	return answer;
}

inline yxlArrayPolynomial yxlArrayPolynomial::operator+(yxlArrayPolynomial& right)
{
	yxlArrayPolynomial answer;
	plus(answer, *this, right);
	return answer;
}

inline yxlArrayPolynomial yxlArrayPolynomial::operator-(yxlArrayPolynomial& right)
{
	yxlArrayPolynomial answer;
	minus(answer, *this, right);
	return answer;
}

inline yxlArrayPolynomial yxlArrayPolynomial::operator*(yxlArrayPolynomial& right)
{
	return times(*this, right);
}

inline yxlArrayPolynomial& yxlArrayPolynomial::operator+=(yxlArrayPolynomial& right)
{
	plus(*this, *this, right);
	return *this;
}

inline yxlArrayPolynomial& yxlArrayPolynomial::operator-=(yxlArrayPolynomial& right)
{
	minus(*this, *this, right);
	return *this;
}

inline yxlArrayPolynomial& yxlArrayPolynomial::operator*=(yxlArrayPolynomial& right)
{
	*this = times(*this, right);
	return *this;
}

inline void yxlArrayPolynomial::plus(yxlArrayPolynomial& answer, yxlArrayPolynomial& left, yxlArrayPolynomial& right)
{
	auto index = 0;
	auto l_it = left.coef_.begin();
	auto r_it = right.coef_.begin();
	for (; l_it < left.coef_.end() && r_it < right.coef_.end(); ++index, ++l_it, ++r_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(answer.coef_.size(), *l_it + *r_it); }
		else { answer.coef_[index] = *l_it + *r_it; }
	}
	for (; l_it < left.coef_.end(); ++index, ++l_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(answer.coef_.size(), *l_it); }
		else { answer.coef_[index] = *l_it; }
	}
	for (; r_it < right.coef_.end(); ++index, ++r_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(answer.coef_.size(), *r_it); }
		else { answer.coef_[index] = *r_it; }
	}
}

inline void yxlArrayPolynomial::minus(yxlArrayPolynomial& answer, yxlArrayPolynomial& left, yxlArrayPolynomial& right)
{
	auto index = 0;
	auto l_it = left.coef_.begin();
	auto r_it = right.coef_.begin();
	for (; l_it < left.coef_.end() && r_it < right.coef_.end(); ++index, ++l_it, ++r_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(answer.coef_.size(), *l_it - *r_it); }
		else { answer.coef_[index] = *l_it - *r_it; }
	}
	for (; l_it < left.coef_.end(); ++index, ++l_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(answer.coef_.size(), *l_it); }
		else { answer.coef_[index] = *l_it; }
	}
	for (; r_it < right.coef_.end(); ++index, ++r_it)
	{
		if (index == answer.coef_.size()) { answer.coef_.insert(answer.coef_.size(), -*r_it); }
		else { answer.coef_[index] = -*r_it; }
	}
}

inline yxlArrayPolynomial yxlArrayPolynomial::times(yxlArrayPolynomial& left, yxlArrayPolynomial& right) const
{
	auto size = 2;
	const auto l_size = left.coef_.size();
	const auto r_size = right.coef_.size();
	while (size < l_size + r_size) { size <<= 1; }
	yxlArray<comp> a(size), b(size);
	for (auto i = 0; i < l_size; ++i) { a[i] = left.coef_[i]; }
	cooley_tukey(a, false);
	for (auto i = 0; i < r_size; ++i) { b[i] = right.coef_[i]; }
	cooley_tukey(b, false);
	for (auto i = 0; i < size; ++i) { a[i] *= b[i]; }
	cooley_tukey(a, true);
	yxlArrayPolynomial answer(l_size + r_size - 1);
	for (auto i = 0; i < l_size + r_size - 1; ++i)
	{
		answer.coef_[i] = a[i].real();
	}
	return answer;
}

inline void yxlArrayPolynomial::cooley_tukey(yxlArray<comp>& that, const bool inverse) const
{
	const auto n = that.size();
	for (auto i = 0, j = 0; i < n; ++i)
	{
		if (j > i) { std::swap(that[i], that[j]); }
		auto k = n;
		while (j & (k >>= 1)) { j &= ~k; }
		j |= k;
	}
	const auto pi = inverse ? -kPi : kPi;
	for (auto step = 1; step < n; step <<= 1)
	{
		const auto alpha = pi / step;
		for (auto k = 0; k < step; ++k)
		{
			auto omegak = exp(comp(0, alpha * k));
			for (auto ek = k; ek < n; ek += step << 1)
			{
				auto ok = ek + step;
				auto t = omegak * that[ok];
				that[ok] = that[ek] - t;
				that[ek] += t;
			}
		}
	}
	if (inverse) { for (auto i = 0; i < n; i++) { that[i] /= n; } }
}

inline std::ostream& operator<<(std::ostream& out, yxlArrayPolynomial& item)
{
	for (auto i : item.coef_)
	{
		out << i << ' ';
	}
	return out;
}

inline std::ostream& operator<<(std::ostream& out, yxlArrayPolynomial&& item)
{
	for (auto i : item.coef_)
	{
		out << i << ' ';
	}
	return out;
}

#endif // !YXL_ARRAY_POLYNOMIAL_H
