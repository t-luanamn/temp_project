#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}


static float	parse_fractional_part(char **str)
{
	float	precision;
	float	divisor;

	precision = 0.0;
	divisor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			divisor *= 10.0;
			precision += (**str - '0') / divisor;
			(*str)++;
		}
	}
	return (precision);
}

float	ft_atof(char *str)
{
	float	sum;
	float	sign;
	float	precision;

	sign = 1.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	sum = (float)ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	precision = parse_fractional_part(&str);
	return ((sum + precision) * sign);
}


void test_atof_functions() {
    // Test cases
    char *test_cases[] = {
        "123.456",
        "-123.456",
        "   123.456",
        "0.456",
        "-0.456",
        "123",
        "-123",
        "   -123.456",
        "123.",
        "-123."
    };

    // Expected results using standard atof
    float expected_results[10];
    for (int i = 0; i < 10; i++) {
        expected_results[i] = atof(test_cases[i]);
    }

    // Actual results using ft_atof
    float actual_results[10];
    for (int i = 0; i < 10; i++) {
        actual_results[i] = ft_atof(test_cases[i]);
    }

    // Compare and print results
    for (int i = 0; i < 10; i++) {
        printf("Test %d: %f (expected: %f)\n", i + 1, actual_results[i], expected_results[i]);
        if (fabs(actual_results[i] - expected_results[i]) < 1e-6) {
            printf("Result: PASS\n");
        } else {
            printf("Result: FAIL\n");
        }
    }
}

int main() {
    test_atof_functions();
    return 0;
}
