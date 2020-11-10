# PS Command


## Process IDS File
Here we do one thing, read all the PIDs from the proc/ directory. When reading the PIDs we have to itterate through the user processes in the /proc/ directory and store those in a list to later return. Overall this module completes a lot of the dirty work when working with files.

## Process File
This modules main purpose is to process command line arguments. Internally it also preforms checks to see if the argumetns given are valid and dont overwite eachother. In the case that there is a issue, errors are thrown. COmmand line parameters are then stored in vsriables inside a struct. This is then returned to the main file for processing. Overall this module cleans up the workflow in the main file.

## Main file
This is the main file which strings everything together. It sends arguments to the Process module and gets back a struct to work with. Then extra safty checks are made and the main fucntion calls the printInfoByPid function for as many times there are pids sepcifed or avaible. This function also reads the info inside the stat, statm, and cmdline files for printing. We iterate through specific files in /proc/PID/ to gather specific details requested by the user. This functions purpose to write to the console the output that the user desired.
