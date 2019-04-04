#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/29 23:04:20
 * \Description:
 */

#ifndef ARRAY_POLYNOMIAL_H
#define ARRAY_POLYNOMIAL_H

#include "Polynomial.h"
#include "../List/Array.h"
#include <complex>

namespace yxl
{
	class LinkedPolynomial;
	constexpr double kPi = 3.1415926;

	class ArrayPolynomial final : public Array<double>,
	                              public Polynomial<ArrayPolynomial>
	{
	public:
		using comp = std::complex<double>;

		ArrayPolynomial() = default;
		explicit ArrayPolynomial(const int& initial_size);
		explicit ArrayPolynomial(const Array<double>& that);
		ArrayPolynomial(const double coef[], const int& size);
		ArrayPolynomial(ArrayPolynomial& that) = default;
		ArrayPolynomial(ArrayPolynomial&& that) noexcept = default;
		~ArrayPolynomial() override = default;

		void read(const double coef[], const int& size) override;
		double calculate(const double& x) override;
		ArrayPolynomial differentiate(const int& x) override;

		ArrayPolynomial operator+(ArrayPolynomial& right);
		ArrayPolynomial operator-(ArrayPolynomial& right);
		ArrayPolynomial operator*(ArrayPolynomial& right);

		ArrayPolynomial& operator=(const ArrayPolynomial& right) = default;
		ArrayPolynomial& operator=(ArrayPolynomial&& right) noexcept = default;
		ArrayPolynomial& operator+=(ArrayPolynomial& right);
		ArrayPolynomial& operator-=(ArrayPolynomial& right);
		ArrayPolynomial& operator*=(ArrayPolynomial& right);

		friend std::ostream& operator<<(std::ostream& out, ArrayPolynomial& item);
		friend std::ostream& operator<<(std::ostream& out, ArrayPolynomial&& item);

	private:
		void plus(ArrayPolynomial& answer, ArrayPolynomial& left, ArrayPolynomial& right) override;
		void minus(ArrayPolynomial& answer, ArrayPolynomial& left, ArrayPolynomial& right) override;
		ArrayPolynomial times(ArrayPolynomial& left, ArrayPolynomial& right) const override;
		void cooley_tukey(Array<comp>& that, bool inverse) const;

		void times(ArrayPolynomial& answer, ArrayPolynomial& left, ArrayPolynomial& right) override
		{
		}
	};

	inline ArrayPolynomial::ArrayPolynomial(const int& initial_size): Array<double>(initial_size)
	{
	}

	inline ArrayPolynomial::ArrayPolynomial(const Array<double>& that) : Array<double>(that)
	{
	}

	inline ArrayPolynomial::ArrayPolynomial(const double coef[], const int& size)
	{
		read(coef, size);
	}

	inline void ArrayPolynomial::read(const double coef[], const int& size)
	{
		for (auto i = 0; i < size; ++i)
		{
			insert(i, coef[i]);
		}
	}

	inline double ArrayPolynomial::calculate(const double& x)
	{
		double now = 1;
		double answer = 0;
		for (auto& i : *this)
		{
			answer += i * now;
			now *= x;
		}
		return answer;
	}

	inline ArrayPolynomial ArrayPolynomial::differentiate(const int& x)
	{
		ArrayPolynomial answer;
		auto expn = x;
		for (auto i = x; i < size_; ++i)
		{
			answer.insert(answer.size(), array_[i]);
		}
		for (auto& it : answer)
		{
			for (auto i = 0; i < x; ++i)
			{
				it *= double(expn) - double(i);
			}
			++expn;
		}
		return answer;
	}

	inline ArrayPolynomial ArrayPolynomial::operator+(ArrayPolynomial& right)
	{
		ArrayPolynomial answer;
		plus(answer, *this, right);
		return answer;
	}

	inline ArrayPolynomial ArrayPolynomial::operator-(ArrayPolynomial& right)
	{
		ArrayPolynomial answer;
		minus(answer, *this, right);
		return answer;
	}

	inline ArrayPolynomial ArrayPolynomial::operator*(ArrayPolynomial& right)
	{
		return times(*this, right);
	}

	inline ArrayPolynomial& ArrayPolynomial::operator+=(ArrayPolynomial& right)
	{
		plus(*this, *this, right);
		return *this;
	}

	inline ArrayPolynomial& ArrayPolynomial::operator-=(ArrayPolynomial& right)
	{
		minus(*this, *this, right);
		return *this;
	}

	inline ArrayPolynomial& ArrayPolynomial::operator*=(ArrayPolynomial& right)
	{
		*this = times(*this, right);
		return *this;
	}

	inline void ArrayPolynomial::plus(ArrayPolynomial& answer, ArrayPolynomial& left, ArrayPolynomial& right)
	{
		auto index = 0;
		auto l_it = left.begin();
		auto r_it = right.begin();
		for (; l_it < left.end() && r_it < right.end(); ++index, ++l_it, ++r_it)
		{
			if (index == answer.size()) { answer.insert(answer.size(), *l_it + *r_it); }
			else { answer[index] = *l_it + *r_it; }
		}
		for (; l_it < left.end(); ++index, ++l_it)
		{
			if (index == answer.size()) { answer.insert(answer.size(), *l_it); }
			else { answer[index] = *l_it; }
		}
		for (; r_it < right.end(); ++index, ++r_it)
		{
			if (index == answer.size()) { answer.insert(answer.size(), *r_it); }
			else { answer[index] = *r_it; }
		}
	}

	inline void ArrayPolynomial::minus(ArrayPolynomial& answer, ArrayPolynomial& left, ArrayPolynomial& right)
	{
		auto index = 0;
		auto l_it = left.begin();
		auto r_it = right.begin();
		for (; l_it < left.end() && r_it < right.end(); ++index, ++l_it, ++r_it)
		{
			if (index == answer.size()) { answer.insert(answer.size(), *l_it - *r_it); }
			else { answer[index] = *l_it - *r_it; }
		}
		for (; l_it < left.end(); ++index, ++l_it)
		{
			if (index == answer.size()) { answer.insert(answer.size(), *l_it); }
			else { answer[index] = *l_it; }
		}
		for (; r_it < right.end(); ++index, ++r_it)
		{
			if (index == answer.size()) { answer.insert(answer.size(), -*r_it); }
			else { answer[index] = -*r_it; }
		}
	}

	inline ArrayPolynomial ArrayPolynomial::times(ArrayPolynomial& left, ArrayPolynomial& right) const
	{
		auto size = 2;
		const auto l_size = left.size();
		const auto r_size = right.size();
		while (size < l_size + r_size) { size <<= 1; }
		Array<comp> a(size), b(size);
		for (auto i = 0; i < l_size; ++i) { a[i] = left[i]; }
		cooley_tukey(a, false);
		for (auto i = 0; i < r_size; ++i) { b[i] = right[i]; }
		cooley_tukey(b, false);
		for (auto i = 0; i < size; ++i) { a[i] *= b[i]; }
		cooley_tukey(a, true);
		ArrayPolynomial answer(l_size + r_size - 1);
		for (auto i = 0; i < l_size + r_size - 1; ++i)
		{
			answer[i] = a[i].real();
		}
		return answer;
	}

	inline void ArrayPolynomial::cooley_tukey(Array<comp>& that, const bool inverse) const
	{
		const auto n = that.size();
		for (auto i = 0, j = 0; i < n; ++i)
		{
			if (j > i) { std::swap(that[i], that[j]); }
			auto k = n;
			while ((j & (k >>= 1)) != 0) { j &= ~k; }
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

	inline std::ostream& operator<<(std::ostream& out, ArrayPolynomial& item)
	{
		for (auto i : item)
		{
			out << i << ' ';
		}
		out << std::endl;
		return out;
	}

	inline std::ostream& operator<<(std::ostream& out, ArrayPolynomial&& item)
	{
		for (auto i : item)
		{
			out << i << ' ';
		}
		out << std::endl;
		return out;
	}
} // namespace yxl

#endif // !ARRAY_POLYNOMIAL_H
