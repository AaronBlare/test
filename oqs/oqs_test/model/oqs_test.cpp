#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "types.h"
#include "step.h"
#include <vector>

template <class T>
::testing::AssertionResult are_vectors_equal(const std::vector<T>& actual, const std::vector<T>& expected)
{
	auto result = ::testing::AssertionFailure();
	if (actual.size() != expected.size())
	{
		result << "Vectors have different size";
		return result;
	}

	auto errors_found = 0;
	auto separator = " ";
	for (auto index = 0; index < actual.size(); index++)
	{
		if (expected[index] != actual[index])
		{
			if (errors_found == 0)
			{
				result << "Differences found:";
			}
			if (errors_found < 3)
			{
				result << separator
					<< expected[index] << " != " << actual[index]
					<< " @ " << index;
				separator = ", ";
			}
			errors_found++;
		}
	}
	if (errors_found > 0)
	{
		result << separator << errors_found << " differences in total";
		return result;
	}
	return ::testing::AssertionSuccess();
}

TEST(PropagationStepTest, QuantumJumpsStep)
{
	const auto n = 4;

	std::vector<COMPLEX_OQS> x(n, { 0.0, 0.0 });
	std::vector<COMPLEX_OQS> a(n * n, { 0.0, 0.0 });
	std::vector<COMPLEX_OQS> y(n, { 0.0, 0.0 });
	for (auto i = 0; i < n; i++)
	{
		x[i] = { static_cast<double>(i), -static_cast<double>(i) };
		for (auto j = 0; j < n; j++)
		{
			const auto index = i * n + j;
			a[index] = { static_cast<double>(index), static_cast<double>(index) };
		}
	}

	const std::vector<COMPLEX_OQS> y_pred{ {28.0, 0.0}, {76.0, 0.0}, {124.0, 0.0}, {172.0, 0.0} };

	std::vector<COMPLEX_OQS> y_test(n, { 0.0, 0.0 });

	qj_step(x, a, y_test, n);

	EXPECT_TRUE(are_vectors_equal(y_pred, y_test));
}