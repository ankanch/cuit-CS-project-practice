#encoding:utf-8

# this file controls the file operation
# we stores data in local disk

# stores user id
# format :  uid,name,sid,[score_list: [group_no,score],[...],...]
PATH_USER_CREDENTIALS = "data/userdata"  

# reading current esist data
def init():
    with open(PATH_USER_CREDENTIALS,"r",errors='ignore') as f:
        data = f.readlines()
        credentials = []
        for line in data:
            if len(line) > 4:
                s = line.split("@")
                print(s[-1])
                s[-1] = eval(s[-1])
                credentials.append(s)
        return credentials

# archive data to the local disk
def archive(all_list):
    with open(PATH_USER_CREDENTIALS,"w",errors='ignore') as f:
        f.truncate()
        for x in all_list:
            print(x,":",type(x),len(x))
            if len(x) == 4 and type(x) == list:
                f.write("@".join([ str(xx) for xx in x ]) + "\n"  )

# add esist data into a data file
def add(dlist):
    with open(PATH_USER_CREDENTIALS,"a",errors='ignore') as f: 
        ras = "@".join([ str(x) for x in dlist ])
        print("ras=",ras)
        f.write( ras + "\n" )

# update exist data
def update(dlist):
    cur = init()
    for i,x in enumerate(cur):
        if dlist[0] == x[0]:
            cur[i] = dlist
            break
    archive(cur)

# delete a specified data
def delete():
    pass




    