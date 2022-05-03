package com.mycompany.app;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        WeatherData weatherdata = new WeatherData();
        CurrentConditionsDisplay conditions = new CurrentConditionsDisplay();
        weatherdata.registerObserver(conditions);
        weatherdata.setMeasurements(1.0f, 5.0f, 2.0f);
        weatherdata.removeObserver(conditions);
    }
}
