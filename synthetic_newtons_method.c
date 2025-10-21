#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

/*
 * HW2 INSTRUCTIONS 
 * Use synthetic division to find ALL roots
 * of a polynomial.
 */

// Pretty prints complex value
void prcmx(double complex v);

// Synthetic division
void syntheticDivision(double complex* fx,
                       double complex root,
                       int size,
                       double complex* fx_val,
                       double complex* dx_val);

// Newton Method calculation
void newtons_method(double complex* fx, 
                    double complex* dx,
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

    printf("--------------------------\n");
    printf("Calling Newton's Method for root finding\n");

    int iters = 50;

    newtons_method(coeffs, dx_coeffs, size, iters);

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

void synthetic_division(double complex* fx,
                        double complex root,
                        int size,
                        double complex* fx_val,
                        double complex* dx_val)
{

    double complex*b = (double complex*) malloc(size*sizeof(double complex));

    // first synthetic division
    b[size-1] = fx[size-1];

    for (int i = size-2; i >= 0; --i)
        b[i] = fx[i] + b[i+1]*root;

    // b[0] is f(x) -> the remainder
    *fx_val = b[0];

    // second synthetic division
    double complex carry = b[size-1];
    for (int i = size-2; i>=1; --i)
        carry = b[i] + carry*root;

    // carry is f'(x)
    *dx_val = carry;

    free(b);
}

void newtons_method(double complex* fx, 
                    double complex* dx,
                    int size,
                    int iters)
{
    int curr_size = size;
    int num_roots = size-1;

    // allocating for storing deflated polynomials
    double complex* curr_fx = (double complex*) malloc(size * sizeof(double complex));
    double complex* temp_fx = (double complex*) malloc(size * sizeof(double complex));

    for (int i=0; i < size; ++i) 
        curr_fx[i] = fx[i];

    double complex curr_root;

    // find each root
    for (int r = 0; r < num_roots; ++r) {
        printf("\n--------------------------\n");
        printf("Finding root %d:\n", r+1);

        /*
        printf("curr estimate at iter 0: ");
        prcmx(curr_root);
        */

        curr_root = 2.0 * cexp(2.0 * M_PI * I * r / (num_roots + 1));

        double complex f_val, df_val;

        // newtons method iteration with current guess
        for (int i = 0; i < iters; ++i) {
            synthetic_division(curr_fx, curr_root, curr_size, &f_val, &df_val);
            curr_root = curr_root - f_val/df_val;
            /*
            printf("curr estimate ater %d: ", i+1);
            prcmx(curr_root);
            */
        }

        printf("Root %d found: ", r+1);
        prcmx(curr_root);

        // if not the final root, deflate polynomial
        if (r < num_roots-1) {
            temp_fx[curr_size-1] = curr_fx[curr_size-1];
            for (int i = curr_size-2; i>=0; --i) {
                temp_fx[i] = curr_fx[i] + temp_fx[i+1]*curr_root;
            }

            curr_size--;
            for (int i = 0; i < curr_size; ++i) {
                curr_fx[i] = temp_fx[i+1];
            }
        }
    }

    printf("\n--------------------------\n");
    printf("All roots have been found!\n");

    free(curr_fx);
    free(temp_fx);
}
