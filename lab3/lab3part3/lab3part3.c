#include <stdio.h>
#include <math.h>

double calcMidpointIntegral(double a, double b, int n)
{
    double integral = 0;
    double deltax = (b - a) / n;
    double xi, yi;

    for (int i = 0; i < n; i++)
    {
        xi = a + deltax / 2 + i * deltax;
        yi = exp(-xi * xi);
        integral += yi * deltax;
    }
    return integral;
}

int main(void)
{
    int n;
    double a, b, integral;

    do
    {
        printf("Please enter the number of rectangles (n): ");
        scanf("%d", &n);
        if (n >= 1)
        {
            do
            {
                printf("Please enter the interval of integration (a b): ");
                scanf("%lf%lf", &a, &b);
                if (a >= b)
                {
                    printf("Invalid interval!\n\n");
                }
            } while (a >= b);

            integral = calcMidpointIntegral(a, b, n);

            printf("The integral of e^-x^2 on [%0.5lf, %0.5lf] with n = %d is: %0.5lf\n\n", a, b, n, integral);
        }
        else
        {
            printf("Exiting.\n");
            break;
        }

    } while (n >= 1);

    return 0;
}
