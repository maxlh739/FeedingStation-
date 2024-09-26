import adafruit_ds3231
import board
from datetime import datetime
import time

i2c = board.I2C()
rtc = adafruit_ds3231.DS3231(i2c)

def getRtcDateTime():
    # Get the current date and time from the RTC and return it as a datetime object
    current_time = rtc.datetime
    return datetime(current_time.tm_year, current_time.tm_mon, current_time.tm_mday, current_time.tm_hour, current_time.tm_min, current_time.tm_sec)

def getTimeInSeconds():
    current_time = rtc.datetime
    return current_time.tm_hour * 3600 + current_time.tm_min * 60 + current_time.tm_sec

def setRtcTime():
    rtc.datetime = time.struct_time(time.localtime(time.time()))