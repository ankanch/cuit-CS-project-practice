#encoding:utf-8
from Utilities import gV as GV
from Utilities import dataManager as DM
import os
import shutil
import time
import datetime


# check if an uid  valid
def check(uid):
    if uid == None:
        return False
    # check if in list
    if getStuName(uid) == None:
        return True
    #print("-check--=log-in-uid=",uid)
    # check if already registed
    for user in GV.VAR_USER_DATA_LIST:
        if user[0].find(uid) > -1:
            return True
    return False

# add an uid to the system
def add(uid,name,sid):
    sdata = [ uid,name,sid, [] ]
    GV.VAR_USER_DATA_LIST.append(sdata)
    DM.add(sdata)
    DM.archive(GV.VAR_USER_DATA_LIST)

# load all users
def loadSession():
    return DM.init()

# get name of an student
def getStuName(uid):
    for x in GV.VAR_STULIST:
        if x[1].find(uid) > -1:
            return x[2]
    return None

# archive session in time
def archive_session(sec):
    while True:
        time.sleep(sec)
        shutil.copy2( "data/userdata", "data/backup/"+ str(time.time())    )