#encoding:utf-8
from Utilities import gV as GV
from Utilities import dataManager as DM
from Utilities import stringx as SS


# this script controls user scoring

# scoring an group
def score(uid,gid,score):
    for i,user in enumerate(GV.VAR_USER_DATA_LIST):
        if user[0] == uid:
            for s in uid[-1]:
                if s[0] == gid:
                    return False,"You have scored this group before!"
            GV.VAR_USER_DATA_LIST[i][-1].append([gid,score])
            DM.archive(GV.VAR_USER_DATA_LIST)

# get avg score and all score of an group
# return sum,avg
def getscore(gid):
    rbl = [ x[-1] for x in GV.VAR_USER_DATA_LIST if len(x[-1]) > 0 ]
    scorelist = []
    for u in rbl:
        scorelist.extend([ x[1] for x in u if x[0]==gid ])
    if len(scorelist) < 1:
        return False,[],[]
    return True,sum(scorelist),sum(scorelist)/len(scorelist)

# get user scored list
def getScoredlist(uid):
    for user in GV.VAR_USER_DATA_LIST:
        if user[0] == uid:
            return [ x[0] for x in user[-1] ]




# get all groups score
def getAllGroupScores():
    resultlist = "<h3>Scores List by Group </h3><br/><p></p>"
    resultlist += SS.table
    mstr = ""
    for gid in GV.GID:
        status,sumx,avgx = getscore(gid)
        if status:
            st = SS.table_item
            mstr += st.replace("@GID",str(gid)).replace("@SUM",str(sumx)).replace("@AVG",str(avgx)[:7])
    return resultlist.replace("@TBODY@",mstr)
