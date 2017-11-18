#encoding:utf-8
from Utilities import gV as GV
from Utilities import stringx as SS
from Utilities import runSQL as DBM
from Utilities import dataManager2 as DM2


# this script controls user scoring

# scoring an group
def score(sid,gid,score):
    result = DBM.runSelect("SELECT SCORELIST FROM cns WHERE SID='%s'"%sid)[0][0]
    data = eval(result)
    data.append([ gid,score ])
    strd = str(data)
    DBM.runUpdate("UPDATE cns SET SCORELIST='%s' WHERE SID='%s'"%(strd,sid))

# get avg score and all score of an group
# return sum,avg
def getscore(gid,rbl):
    scorelist = [ x[1] for x in rbl if x[0]==gid ]
    if len(scorelist) < 1:
        return False,[],[]
    return True,sum(scorelist),sum(scorelist)/len(scorelist)

# get user scored list
def getScoredlist(sid):
    data = DBM.runSelect("SELECT SCORELIST FROM cns WHERE SID='%s'"%sid)[0][0]
    #print(data)
    data = eval(data)
    #print(data)
    return [ x[0] for x in data ]


# get all groups score
def getAllGroupScores():
    resultlist = """
                    <h3>Scores List by Group </h3>
                    <p style="margin-bottom:2px;">Made with ♥ by Kanch</p>
                    <p style="margin-bottom:2px;">kanch@ieee.org</p>
                    <br/>
                """
    resultlist += SS.table
    mstr = ""
    result = DBM.runSelect("SELECT SCORELIST FROM cns")
    rbl = []
    for uscorelist in result:
        x = eval(uscorelist[0])
        if len(x) < 1:
            continue
        #print(x)
        rbl.extend(x)
    for gid in GV.GID:
        status,sumx,avgx = getscore(gid,rbl)
        if status:
            st = SS.table_item
            mstr += st.replace("@GID",str(gid)).replace("@SUM",str(sumx)).replace("@AVG",str(avgx)[:7])
    return resultlist.replace("@TBODY@",mstr)


#this function scores a student by SID
def scoreStudent(sid,score):
    ss = str(score) + ","
    DBM.runUpdate("UPDATE stu SET SCORELIST=SCORELIST+'%s' WHERE SID='%s'"%(ss,sid))

# this function comment a student
def commentStudent(sid,comment):
    cc = comment + GV.SPLITER
    comment = DM2.secureString(comment)
    DBM.runUpdate("UPDATE stu SET COMMENTS=COMMENTS+'%s' WHERE SID='%s'"%(cc,sid))

# get score list of an student
def getScoreListOf(sid):
    result = DBM.runSelect("SELECT SCORELIST FROM stu WHERE SID='%s'"%(sid))

def getCommentsListOf(sid):
    result = DBM.runSelect("SELECT COMMENTS FROM stu WHERE SID='%s'"%(sid))
    result = DM2.unsecureString(result)

# this function returns group member data
# returns group list [id,[member list]]
def getGroupData(gid):
    for g in GV.VAR_GROUPLIST:
        if g[0] == gid:
            return True,g
    return False,[]