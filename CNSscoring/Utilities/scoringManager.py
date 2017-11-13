#encoding:utf-8
from Utilities import gV as GV
from Utilities import dataManager as DM


# this script controls user scoring

# scoring an group
def score(uid,gid,score):
    for i,user in enumerate(GV.VAR_USER_DATA_LIST):
        if user[0] == uid:
            for s in uid[-1]:
                if s[0] == gid:
                    return False,"You have scored this group before!"
            GV.VAR_USER_DATA_LIST[i][-1].append([gid,score])

# get avg score and all score of an group
# return sum,avg
def getscore(gid):
    scorelist = [ y[1] for y in x[-1] for x in GV.VAR_USER_DATA_LIST if y[0] == gid]
    return sum(scorelist),sum(scorelist)/len(scorelist)

# get user scored list
def getScoredlist(uid):
    for user in GV.VAR_USER_DATA_LIST:
        if user[0] == uid:
            return [ x[0] for x in user[-1] ]

