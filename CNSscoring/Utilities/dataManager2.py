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
        return credentials,stulist
