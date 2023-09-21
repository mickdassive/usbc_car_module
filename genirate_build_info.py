import os
import datetime

# Get the current date and time in EST
est_time = datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=-5)))

with open("build_info.h", "w") as f:
    f.write(f'#define FIRMWARE_VERSION "1.0.0"\n')
    f.write(f'#define BUILD_DATETIME "{est_time.strftime("%d/%m/%Y %H:%M:%S")}"\n')
