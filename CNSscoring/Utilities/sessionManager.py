#encoding:utf-8
from Utilities import gV as GV
from Utilities import runSQL as DBM
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
        return False
    #print("-check--=log-in-uid=",uid)
    # check if already registed
    user = DBM.runSelect("SELECT SID FROM cns WHERE SID='%s'"%uid)
    print("check-",user)
    if len(user) > 0:
        return True
    return False

# check if an openid exist
def checkOpenID(openid):
    userdata = DBM.runSelect("SELECT SID FROM cns WHERE OPENID='%s'"%openid)
    print("OID-check-",userdata)
    if len(userdata)> 0 :
        return True,userdata[0][0]
    return False,""

# add an uid to the system
def add(sid,name,uid):
    DBM.runInsert(" INSERT INTO cns VALUES('%s','%s','%s','[]')"%(sid,name,uid))
    return True

# load all users informations
def loadSession():
    credentials  = DBM.runSelect("SELECT * FROM cns")
    print(credentials)
    return credentials

# get name of an student
def getStuName(uid):
    for x in GV.VAR_STULIST:
        if x[1].find(uid) > -1:
            return x[2]
    return None