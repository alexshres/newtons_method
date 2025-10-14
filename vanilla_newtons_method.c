#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

/*
 * HW1 INSTRUCTIONS
 * will need array of ints for f(x) -> complex arrays
 * will need array of ints for f'(x) -> complex arrays
 * coefficients of polynomials are real
 */

// Pretty prints complex value
void prcmx(double complex v);

// Computes polynomial
double complex polynomial(double complex* arr, double complex input, int size);

// Newton Method calculation
void newtons_method(double complex* fx, 
                    double complex* dx,
                    double complex init,
                    int size,
                    int iters);

int main()
{
    int degree;
    int size;
    double complex* coeffs;
    double complex* dx_coeffs;

    printf("Enter the degree of your polynomial: ");
    scanf("%d", &degree);

    size = degree + 1;

    if (size == 1) {
        printf("Constant functions will not have any roots unless the constant is 0 in which case the entire real number line is a solution.\n");
        return 0;
    }


    // Creating complex coefficients to make things easier when 
    // calculating derivatives and finding potential complex roots
    coeffs = (double complex*) malloc(size * sizeof(double complex));

    // For derivatives we have 1 less degree to worry about so just using
    // already gathered degree
    dx_coeffs = (double complex*) malloc(degree * sizeof(double complex));

    printf("You entered a degree of %d\n", degree);
    printf("--------------------------\n");
    printf("Now we will grab the coefficients next\n");

    double coeff;
    double complex cpx_coeff;
    double complex dx_cpx_coeff;
    double a;

    for (int i = 0; i < size; ++i) {
        printf("Please enter real valued coefficient for degree %d: ", degree - i);
        scanf("%lf", &coeff);

        // Turning into complex number
        cpx_coeff = coeff + 0*I;
        // Adding complex coefficient to appropriate degree index
        coeffs[degree-i] = cpx_coeff;

        // Updating derivative coeffs now
        // Will return error if we try to update dx_coeffs after degree - 1
        // since we have an array of a smaller size
        if (i < degree)
            dx_coeffs[degree-1-i] = (degree-i)*creal(cpx_coeff) + 0*I;
    }

    printf("--------------------------\n");
    printf("Function coefficients are:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d: ", i);
        prcmx(coeffs[i]);
    }

    printf("--------------------------\n");
    printf("Derivative coefficients are:\n");
    for (int i = 0; i < degree; ++i) {
        printf("%d: ", i);
        prcmx(dx_coeffs[i]);
    }

    double complex evaluate;
    double complex init = 1 + 1*I;

    evaluate = polynomial(coeffs, init, size);

    printf("--------------------------\n");
    printf("The polynomial evaluated at x=1+1*i is: ");
    prcmx(evaluate);


    printf("--------------------------\n");
    printf("Calling Newton's Method for root finding\n");

    int iters = 10;

    newtons_method(coeffs, dx_coeffs, init, size, iters);

    free(coeffs);
    free(dx_coeffs);

}


void prcmx(double complex v) 
{
    double a, b;

    a = creal(v);
    b = cimag(v);

    printf("%lf + %lf * i\n", a, b);
}


double complex polynomial(double complex* arr, double complex input, int size)
{
    double complex total = 0 + 0*I;

    for (int i = 0; i < size; ++i)
        total += arr[i] * cpow(input, i);

    return total;
}

void newtons_method(double complex* fx, 
                    double complex* dx,
                    double complex init,
                    int size,
                    int iters)
{
    double complex curr_root = init;
    printf("curr estimate at iter 0: ");
    prcmx(curr_root);


    for (int i = 0; i < iters; ++i) {
        curr_root = curr_root - polynomial(fx, curr_root, size)/polynomial(dx, curr_root, size-1);
        printf("curr estimate at iter %d: ", i+1);
        prcmx(curr_root);
    }

}
