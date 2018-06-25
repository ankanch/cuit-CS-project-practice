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
                    <p style="margin-bottom:2px;"> Made with ♥ by Kanch</p>
                    <p style="margin-bottom:2px;"> kanch@ieee.org</p>
                    <a href="/s/1997">→view student score list</a>
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
    DBM.runUpdate("UPDATE stu SET SCORELIST=CONCAT(SCORELIST,'%s') WHERE SID='%s'"%(ss,sid))

# this function comment a student
def commentStudent(sid,comment):
    if len(comment) < 1:
        return False
    cc = comment + GV.SPLITER
    comment = DM2.secureString(cc)
    sql = "UPDATE stu SET COMMENTS=CONCAT(COMMENTS,'%s') WHERE SID=\"%s\""%(comment,sid)
    DBM.runUpdate(sql)


# this function returns group member data
# returns group list [id,[member list]]
def getGroupData(gid):
    for g in GV.VAR_GROUPLIST:
        if g[0] == gid:
            return True,g
    return False,[]


# get All setudent socres and comments 
def getAllStudetnScoresComments():
    resultlist = """
                    <h3>Scores List by Student </h3>
                    <p style="margin-bottom:2px;"> Made with ♥ by Kanch</p>
                    <p style="margin-bottom:2px;"> kanch@ieee.org</p>
                    <a href="/s/1996">→view group score list</a>
                    <br/>
                """
    resultlist += SS.student_table
    mstr = ""
    result = DBM.runSelect("SELECT * FROM stu")
    stst = ""
    for student in result:
        mstr = SS.student_item
        mstr = mstr.replace("@NAME",student[1]).replace("@SID",student[0])
        scores = [int(x) for x in student[3].split(",") if len(x) > 0]
        sumx = sum(scores)
        if len(scores) > 0:
            mstr = mstr.replace("@SUM",str(sumx)).replace("@AVG",str(sumx/len(scores)))
        else:
            mstr = mstr.replace("@SUM",str(sumx)).replace("@AVG","0")
        comments = "<br/>".join(student[4].split(GV.SPLITER))
        mstr = mstr.replace("@COMMENTS",comments)
        stst += mstr
    resultlist = resultlist.replace("@TBODY@",stst)
    return resultlist