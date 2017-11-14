import os
from Utilities import gV as GV
from time import sleep

WORKERS_COUNT = 6
WORKERS_TIMEOUT = 180 # seconds


if "mode.server" in os.listdir("./"):
    # when a specific file in current dir,bind IP below  
    os.system("/home/ubuntu/.local/bin/gunicorn -w %d -t %d -b %s:%s index:app"%(GV.WORKER_COUNT,GV.TIMEOUT,GV.BIND_IP,GV.BIND_PORT))  
elif "mode.debug" in os.listdir("../"):
    # used for debug, only run on a single thread
    os.system("python index.py")

while True:
    sleep(36000)