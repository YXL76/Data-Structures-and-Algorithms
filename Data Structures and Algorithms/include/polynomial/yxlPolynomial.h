/**
 * \Author: YXL
 * \LastUpdated: 2018/03/24 10:50:40
 * \Description:
 */

#pragma once

#ifndef YXL_POLYNOMIAL_H
#define YXL_POLYNOMIAL_H

class Polynomial
{
public:
	Polynomial() = default;
	virtual ~Polynomial() = default;
	Polynomial(Polynomial& that) noexcept = default;
	Polynomial(Polynomial&& that) noexcept = default;

	virtual void read(const double coef[], const int& size) = 0;
	virtual double calculate(const double& x) = 0;

	Polynomial& operator=(const Polynomial& right) = default;
	Polynomial& operator=(Polynomial&& right) noexcept = default ;
};

#endif // !YXL_POLYNOMIAL_H
