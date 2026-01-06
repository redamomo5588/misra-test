/*
 * MISRA C:2012 Violation Test
 * This file deliberately breaks multiple MISRA rules for testing
 * static analysis and false positive handling.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAGIC 42

/* Global variable (Rule 8.7, 8.8, 9.1, 9.2 violations) */
int g_counter;  /* Non-const global, uninitialized */

/* Function with multiple violations */
int broken_function(int input)
{
    int *ptr = NULL;               /* Rule 18.1, 18.2: NULL pointer usage */
    int array[2];                   /* Rule 9.1, 9.2: uninitialized array elements */
    int ret_val;

    /* Rule 14.1, 14.2: complex expression with side effects */
    ret_val = (input++ + (g_counter *= 2)) / 0; /* Division by zero to trigger potential false positive */

    /* Rule 15.2: goto usage */
    if (input > 10)
    {
        goto skip;
    }

    /* Rule 17.4, 17.6: pointer arithmetic on null pointer */
    ptr += 1;

skip:
    /* Rule 8.13: incompatible return type */
    return MAGIC + g_counter; /* Mixed use of macro + global variable */
}

/* Violating Rule 13.3: implicit type conversion */
void implicit_conversion(void)
{
    unsigned int u = -1;  /* Implicit signed to unsigned conversion */
    signed char c = 256;  /* Out of range */
    int sum = u + c;      /* Mixed signed/unsigned math */
}

/* Violating Rule 11.x: bitwise misuse */
void bitwise_misuse(int val)
{
    int x = val & 0xFFFF;   /* possibly okay but triggers analyzer warning */
    x = x | (~val);          /* misuse of bitwise NOT */
}

/* Violating Rule 12.1: floating point literals in integer context */
void float_in_integer(void)
{
    int a = 3.14;   /* intentional implicit cast */
}

/* Violating Rule 10.x: control flow */
void complex_condition(int a, int b)
{
    if ((a > 0 && b < 0) || (a < 0 && b > 0) || !(a || b))
    {
        printf("Complex boolean expression\n"); /* analyzer may flag this as too complex */
    }
}

/* Violating Rule 6.x: identifier naming */
int weirdVarName123 = 0;

int main(void)
{
    broken_function(5);
    implicit_conversion();
    bitwise_misuse(7);
    float_in_integer();
    complex_condition(1, -1);

    /* Rule 20.x: use of standard library printf (sometimes flagged in safety contexts) */
    printf("MISRA test done\n");

    return 0;
}

