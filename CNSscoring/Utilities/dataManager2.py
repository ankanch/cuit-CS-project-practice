#encoding:utf-8

from Utilities import runSQL as DBM

# reading current esist data
def init():
    credentials  = DBM.runSelect("SELECT * FROM cns")
    print(credentials)
    # open student list
    with open("data/stulist.txt",'r',errors='ignore',encoding='utf-8') as f:
        data = f.readlines()
        stulist = [ line.split(",") for line in data if len(line) > 15 ]
        with open("data/grouplist.txt",'r',errors='ignore',encoding='utf-8') as f:
            data = f.readlines()
            grouplist = [ line.split("@") for line in data if len(line) > 15 ]
            gl = []
            for group in grouplist:
                gm = [ x.split(",") for x in group[1].split("#") ]
                gl.append([int(group[0]) , gm ])
            return credentials,stulist,gl


SECURE_LIST = [
    ["'","@SIN@"],
    ["\"","@DSIN@"],
    ["=","@EQUAL@"],
    [";","@semicolon@"]
]
# secure an input for database
def secureString(data):
    for x in SECURE_LIST:
        data.replace(x[0],x[1])
    return data

# unsecure an input from databse
def unsecureString(data):
    for x in SECURE_LIST:
        data.replace(x[1],x[0])
    return data