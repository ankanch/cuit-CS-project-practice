import threading
import time
import shutil

# archive session in time
def archive_session(sec):
    while True:
        time.sleep(sec)
        print("backing up....")
        shutil.copy2( "data/userdata", "data/backup/"+ str(time.time())    )

print("back up running...")
thread = threading.Thread(target = archive_session, args = (96, ))
thread.start()