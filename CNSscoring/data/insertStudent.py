import pymysql as SQL

with open("grouplist.txt",errors='ignore',encoding='utf-8') as f:
    DBCONN = SQL.connect(host="115.159.197.66*", port=3306,user="cns",passwd="*FMRRzV5Zcq9b2Jah*",db="CNS",charset='UTF8')
    # preprocess
    data = f.readlines()
    grouplist = [ line.split("@") for line in data if len(line) > 15 ]
    gl = []
    for group in grouplist:
        gm = [ x.split(",") for x in group[1].split("#") ]
        gl.append([int(group[0]) , gm ])
    # insert into data base
    STRINSERT = "INSERT INTO stu VALUES('@SID','@NAME',@GID,'','')"
    with DBCONN.cursor() as CUR:
        for group in gl:
            for s in group[1]:
                sql = STRINSERT
                sql = sql.replace("@SID",s[1]).replace("@NAME",s[0]).replace("@GID",str(group[0]))
                try:
                    CUR.execute(sql)
                    print(".",end=' ')
                except Exception as e:
                    DBCONN.close()
                    print("ERROR",e,end=' ')
        DBCONN.commit()
    DBCONN.close()