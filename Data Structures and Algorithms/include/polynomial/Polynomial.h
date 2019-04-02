/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:09:30
 * \Description:
 */

#pragma once

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

namespace yxl
{
	template <typename T>
	class Polynomial
	{
	public:
		Polynomial() = default;
		virtual ~Polynomial() = default;
		Polynomial(Polynomial<T>& that) noexcept = default;
		Polynomial(Polynomial<T>&& that) noexcept = default;

		virtual void read(const double coef[], const int& size) = 0;
		virtual double calculate(const double& x) = 0;
		virtual T differentiate(const int& x) = 0;
		virtual void plus(T& answer, T& left, T& right) = 0;
		virtual void minus(T& answer, T& left, T& right) = 0;
		virtual void times(T& answer, T& left, T& right) = 0;
		virtual T times(T& left, T& right) const = 0;

		Polynomial& operator=(const Polynomial<T>& right) = default ;
		Polynomial& operator=(Polynomial<T>&& right) noexcept = default ;
	};
}
#endif // !POLYNOMIAL_H
