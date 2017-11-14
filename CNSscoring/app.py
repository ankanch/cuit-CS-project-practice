import os
from time import sleep

WORKERS_COUNT = 6
WORKERS_TIMEOUT = 180 # seconds


if "mode.server" in os.listdir("./"):
    # when a specific file in current dir,bind IP below  
    os.system("gunicorn -w %d -t %d -b %s:80 index:app"%(8,120,"10.139.150.91"))
elif "mode.debug" in os.listdir("../"):
    # used for debug, only run on a single thread
    os.system("python index.py")
else:
    # local machine for test
    os.system("gunicorn -w %d -t %d -b 127.0.0.1:8000 index:app"%(8,120))

while True:
    sleep(36000)