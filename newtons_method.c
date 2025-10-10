#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

void prcmx(double complex v);

double complex func(double complex x);
double complex derivative(double complex x);

int main()
{
    int degree;
    int size;
    double complex* coeffs;
    double complex* dx_coeffs;

    printf("Enter the degree of your polynomial: ");
    scanf("%d", &degree);

    size = degree + 1;

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
        prcmx(coeffs[degree-i]);

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




   /*
    * will need array of ints for f(x) -> complex arrays
    * will need array of ints for f'(x) -> complex arrays
    * coefficients of polynomials are real
    */

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

double complex func(double complex x)
{
    return cpow(x, 3) - 30*x - 36;
}

double complex derivative(double complex x)
{
    return 3*cpow(x, 2) - 30;
}
