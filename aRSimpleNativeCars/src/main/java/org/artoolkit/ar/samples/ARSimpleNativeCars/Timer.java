package org.artoolkit.ar.samples.ARSimpleNativeCars;

public class Timer {

    private long startTimeMillis;

    public long getTimeMillis() {
        return System.currentTimeMillis() - startTimeMillis;
    }

    public void start() {
        startTimeMillis = System.currentTimeMillis();
    }

    @Override
    public String toString() {
        long millis = getTimeMillis();
        long second = (millis / 1000) % 60;
        long minute = (millis / (1000 * 60)) % 60;
        long hour = (millis / (1000 * 60 * 60)) % 24;

        return hour + ":" + minute + ":" + second;
    }
}
