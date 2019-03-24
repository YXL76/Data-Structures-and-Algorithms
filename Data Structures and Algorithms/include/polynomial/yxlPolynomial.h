/**
 * \Author: YXL
 * \LastUpdated: 2018/03/24 10:50:40
 * \description:
 */

#pragma once

#ifndef YXL_POLYNOMIAL_H
#define YXL_POLYNOMIAL_H

class yxlPolynomial
{
public:
	yxlPolynomial() = default;
	virtual ~yxlPolynomial() = default;
	yxlPolynomial(yxlPolynomial& that) noexcept = default;
	yxlPolynomial(yxlPolynomial&& that) noexcept = default;

	virtual void read(yxlChain<double>& that) = 0;
	virtual void read(const double coef[], const int& size) = 0;
	virtual void write() const = 0;
	virtual double calculate(const double& x) = 0;

	yxlPolynomial& operator=(const yxlPolynomial& right) = default;
	yxlPolynomial& operator=(yxlPolynomial&& right) noexcept = default ;
};

#endif // !YXL_POLYNOMIAL_H
