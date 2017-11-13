#encoding:utf-8
from Utilities import gV as GV
from Utilities import dataManager as DM
import os
import random
import string
import time
import datetime


# check if an uid  valid
def check(uid):
    print("-check--=log-in-uid=",uid)
    print("-check--=current-uids=",GV.VAR_USER_DATA_LIST)
    for user in GV.VAR_USER_DATA_LIST:
        if user[0] == uid:
            return True
    return False

# add an uid to the system
def add(uid,name,sid):
    sdata = [ uid,name,sid, [] ]
    GV.VAR_USER_DATA_LIST.append(sdata)
    DM.add(sdata)

# load all users
def loadSession():
    return DM.init()

# add an test user to system
def add_test():
    if len(GV.VAR_USER_DATA_LIST) == 0:
        add("test","Kanch Zhang","2015051152")

# archive session in time
def archive_session(sec):
    while True:
        time.sleep(sec)
        print("saving data...")
        GV.VAR_USER_DATA_LIST = [ x for x in GV.VAR_USER_DATA_LIST if len(x)==4 ]
        DM.archive(GV.VAR_USER_DATA_LIST)
        print("done.")