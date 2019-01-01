#pragma once
#include "types.h"
#include <mkl.h>
#include <vector>
#include <complex>

/**
 * \brief Performing propagation step: y=A*x
 * \param x
 * \param a
 * \param y
 * \param n
 */
void qj_step(const std::vector<COMPLEX_OQS>& x, const std::vector<COMPLEX_OQS>& a, std::vector<COMPLEX_OQS>& y, const int n);

