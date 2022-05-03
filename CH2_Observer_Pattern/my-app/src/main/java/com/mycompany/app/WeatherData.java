package com.mycompany.app;

import java.util.ArrayList;

/**
 * This is a subject class, to which displays can subscribe
 */
public class WeatherData implements Subject {
	private ArrayList<Observer> observers = new ArrayList<Observer>();
	private float temperature;
	private float humidity;
	private float pressure;

	public void registerObserver(Observer obs) {
		observers.add(obs);
	}

	public void removeObserver(Observer obs) {
		observers.remove(obs);
	}

	public void notifyObservers() {
		for (int i = 0; i < observers.size(); i++) {
			Observer obs = observers.get(i);
			obs.update(getTemperature(), getHumidity(), getPressure());
		}
	}

	public float getTemperature() {
		return temperature;
	}

	public float getHumidity() {
		return humidity;
	}

	public float getPressure() {
		return pressure;
	}

	public void measurementsChanged() {
		notifyObservers();
	}

	public void setMeasurements(float temp, float humid, float pres) {
		temperature = temp;
		humidity = humid;
		pressure = pres;
		measurementsChanged();
	}
}
