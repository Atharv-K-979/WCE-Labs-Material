package converter;

public class TemperatureConverter {
    public double celsiusToFahrenheit(double c)
    {
        return (c * 9 / 5) + 32;
    }

    public double fahrenheitToCelsius(double f)
    {
        return (f - 32) * 5 / 9;
    }

    public double celsiusToKelvin(double c) {
        return c + 273.15;
    }
}
