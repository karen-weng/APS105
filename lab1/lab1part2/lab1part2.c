#include <stdio.h>

int main(void)
{
    double tempF, tempC, difference;
    printf("Enter the thermostat temperature: ");
    scanf("%lf", &tempF);
    tempC = (tempF - 32) * 5 / 9;
    printf("The temperature in Celsius is: %0.1lf\n\n", tempC);
    difference = tempF - (71.6);
    printf("You are %0.1lf degrees Fahrenheit away from a nice 22 degrees Celsius.", difference);

    return 0;
}
