#include <stdio.h>
#include <math.h>

int main(void)
{
   double c, a, r, m, v;

   printf("Circumference (km) of planet? ");
   scanf("%lf", &c);
   printf("Acceleration due to gravity (m/s^2) on planet? ");
   scanf("%lf", &a);
   printf("\n\nCalculating the escape velocity...\n");
   r = c / (2 * 3.14159);
   printf("Planet radius: %0.1f km\n", r);
   m = a * pow(r, 2) * pow(10.0, -15) / (6.6726 * pow(10.0, -11));
   printf("Planet mass: %0.1lf x 10^21 kg\n", m);
   v = sqrt((2 * 6.6726 * pow(10.0, -11) * m) * pow(10.0, 12) / r);
   printf("Escape velocity: %0.1lf km/s\n", v);
   return 0;
}
