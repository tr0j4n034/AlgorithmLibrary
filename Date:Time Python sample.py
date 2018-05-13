import datetime

sundays = 0
date = datetime.datetime(1901, 1, 1)

while True:
    if date.day == 1 and date.weekday() == 6:
        sundays += 1
    if date == datetime.datetime(2000, 12, 31):
        break
    date += datetime.timedelta(days=1)
print(sundays)
