import os
import datetime

# Get the current date and time in EST
est_time = datetime.datetime.now(datetime.timezone(datetime.timedelta(hours=-5)))

# Define the relative path to the directory where you want to save build_info.h
relative_output_directory = ''

# Create the full path to the build_info.h file in the specified directory
output_directory = os.path.join(os.getcwd(), relative_output_directory)
build_info_path = os.path.join(output_directory, 'build_info.h')

# Ensure the output directory exists; create it if it doesn't
os.makedirs(output_directory, exist_ok=True)

# Write the firmware version and build date/time to build_info.h in the output directory
with open(build_info_path, "w") as f:
    f.write(f'#define BUILD_DATETIME "{est_time.strftime("%d/%m/%Y %H:%M:%S")}"\n')
