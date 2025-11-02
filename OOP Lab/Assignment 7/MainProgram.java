import converter.TemperatureConverter;

public class MainProgram {
    public static void main(String[] args) {
        TemperatureConverter t = new TemperatureConverter();
        System.out.println("25°C = " + t.celsiusToFahrenheit(25) + "°F");
        System.out.println("77°F = " + t.fahrenheitToCelsius(77) + "°C");
        System.out.println("0°C = " + t.celsiusToKelvin(0) + " K");
    }
}
