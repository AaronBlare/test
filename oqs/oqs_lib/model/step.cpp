#include "step.h"

void qj_step(const std::vector<COMPLEX_OQS>& x, const std::vector<COMPLEX_OQS>& a, std::vector<COMPLEX_OQS>& y, const int n)
{
	COMPLEX_OQS zero{ 0.0, 0.0 };
	COMPLEX_OQS one{ 1.0, 0.0 };
	cblas_zgemv(CblasRowMajor, CblasNoTrans, n, n, &one, a.data(), n, x.data(), 1, &zero, y.data(), 1);
}
