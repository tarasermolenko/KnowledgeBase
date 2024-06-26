

# AIR QUALITY INDEX

## Summary

Real time air quality data within specified geographic boundaries.              

The command line program calculates average of air pollutant PM2.5 over n minutes, of
all the stations map bound by two pairs of latitudes and longitudes.


Get Token Here: https://aqicn.org/data-platform/token/

## The command line program takes:
• coordinates that would represent a map bound: latitude_1, longitude_1,
latitude_2, longitude_2
• sampling period in minutes (default = 5)
• sampling rate in sample(s) / minute (default = 1)

## Data
Using the free JSON API https://aqicn.org/json-api/doc/ to retrieve the data.

### Output
Print PM2.5 sampled value for each station.
Print overall PM2.5 average of all stations over n minutes of sampling.

Specifiying Time and Sampling Rate: `python script.py <latitude_1> <longitude_1> <latitude_2> <longitude_2> <minutes> <rate>`

Sample Usage: `python script.py 49 -123 50 -124 1 5`

![Sample Run Image](AQI.png "Sample RUn")
