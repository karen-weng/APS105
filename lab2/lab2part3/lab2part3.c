#include <stdio.h>
#include <math.h>

int main(void)
{
    double q1, q2, distance, force;
    char unit1, unit2;

    printf("Enter the value of the two charges separated by a space: ");
    scanf("%lf%c %lf%c", &q1, &unit1, &q2, &unit2);
    printf("Enter distance between charges in metres: ");
    scanf("%lf", &distance);

    if (unit1 == 'n' || unit1 == 'N')
    {
        q1 = q1 * 1e-9;
    }
    else if (unit1 == 'u' || unit1 == 'U')
    {
        q1 = q1 * 1e-6;
    }

    if (unit2 == 'n' || unit2 == 'N')
    {
        q2 = q2 * 1e-9;
    }
    else if (unit2 == 'u' || unit2 == 'U')
    {
        q2 = q2 * 1e-6;
    }

    force = 8.9875 * 1e9 * fabs(q1) * fabs(q2) / (distance * distance);

    if (force < 1e-6)
    {
        force *= 1e9;
        printf("The force between charges is %.2lfnN (less than 1uN)\n", force);
    }
    else if (force < 1e-3)
    {
        force *= 1e6;
        printf("The force between charges is %.2lfuN (less than 1mN)\n", force);
    }
    else if (force < 1)
    {
        force *= 1e3;
        printf("The force between charges is %.2lfmN (less than 1N)\n", force);
    }
    else
    {
        printf("The force between charges is %.2lfN (1N or greater)\n", force);
    }

    return 0;
}
