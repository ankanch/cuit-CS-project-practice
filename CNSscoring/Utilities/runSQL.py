import pymysql as SQL
from Utilities import gV as GV

#DBCONN = SQL.connect(host=GV.DB_HOST, port=3306,user=GV.DB_USER,passwd=GV.DB_PASSWORD,db=GV.DB_NAME,charset='UTF8')

def runSelect(sql):
    DBCONN = SQL.connect(host=GV.DB_HOST, port=3306,user=GV.DB_USER,passwd=GV.DB_PASSWORD,db=GV.DB_NAME,charset='UTF8')
    result = []
    with DBCONN.cursor() as CUR:
        CUR.execute(sql)
        DBCONN.commit()
        result = CUR.fetchall()
    DBCONN.close()
    return result

def runInsert(sql):
    DBCONN = SQL.connect(host=GV.DB_HOST, port=3306,user=GV.DB_USER,passwd=GV.DB_PASSWORD,db=GV.DB_NAME,charset='UTF8')
    with DBCONN.cursor() as CUR:
        try:
            CUR.execute(sql)
            DBCONN.commit()
        except Exception as e:
            DBCONN.close()
            print(">>>ERROR\n",e)
            return False
    DBCONN.close()
    return True

def runDelete(sql):
    DBCONN = SQL.connect(host=GV.DB_HOST, port=3306,user=GV.DB_USER,passwd=GV.DB_PASSWORD,db=GV.DB_NAME,charset='UTF8')
    with DBCONN.cursor() as CUR:
        try:
            CUR.execute(sql)
            DBCONN.commit()
        except:
            DBCONN.close()
            return False
    DBCONN.close()
    return True

def runUpdate(sql):
    DBCONN = SQL.connect(host=GV.DB_HOST, port=3306,user=GV.DB_USER,passwd=GV.DB_PASSWORD,db=GV.DB_NAME,charset='UTF8')
    with DBCONN.cursor() as CUR:
        try:
            CUR.execute(sql)
            DBCONN.commit()
        except:
            DBCONN.close()
            return False
    DBCONN.close()
    return True
