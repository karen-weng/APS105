 #include <stdio.h>
#include <math.h>

int main(void)
{
    double const v = 20.0, l = 2.0, g = 9.81;
    double d, H, alpha, t, y;

    do
    {
        printf("Please enter the horizontal distance from the wall between 3 and 30 m:\n");
        scanf("%lf", &d);
    } while (d < 3 || d > 30);

    do
    {
        printf("Please enter the target height between 3 and 6 m:\n");
        scanf("%lf", &H);
    } while (H < 3 || H > 6);

    for (alpha = 0; alpha <= 90; alpha += 1)
    {
        t = d / (v * cos(alpha * M_PI / 180.0));
        y = l + (v * sin(alpha * M_PI / 180.0) * t) - (0.5 * g * t * t);

        if (fabs(y - H) <= 0.3)
        {
            printf("The angle should be %.2f\n", alpha);
            break;
        }
    }
    return 0;
}
