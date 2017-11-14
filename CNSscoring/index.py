#encoding:utf-8
import time
import flask
import os
import json
import threading
from Utilities import gV as GV
from Utilities import sessionManager,scoringManager
from functools import wraps
from flask import Flask, jsonify, redirect, render_template, request,make_response,send_file,Response


app = Flask(__name__)

GV.VAR_USER_DATA_LIST = sessionManager.loadSession()
thread = threading.Thread(target = sessionManager.archive_session, args = (60, ))
thread.start()
print(GV.VAR_USER_DATA_LIST)

@app.route('/')
def index():
    uid =  request.cookies.get('uid')
    if uid != None:
        print("already registed!")
        return redirect('/scoring')
    return render_template("index.html",TITLE="计算机网络打分系统 ",title="登陆")

@app.route('/error')
def error(msg="遇到未知错误！请重试！"):
    return render_template('error.html',TITLE="计算机网络打分系统 ",title="出错了",error_message=msg)


@app.route('/regist',methods=['POST'])
def registe():
    access_token = request.form['sid']
    print("access_tocken=",access_token)
    if sessionManager.check(access_token):
        print("already registed!")
        return "U22UkanchU22"
    else:
        print("1111")
        resp = make_response("OK")
        resp.set_cookie('uid',access_token)
        sessionManager.add(access_token,access_token,access_token)
        return resp

@app.route('/s/<pwd>')
def scoreslist(pwd):
    if pwd == "1996":
        return scoringManager.getAllGroupScores()
    return error("禁止访问！")

@app.route('/scoring')
def scoring():
    uid =  request.cookies.get('uid')
    scored = scoringManager.getScoredlist(uid)
    if sessionManager.check(uid):
        uGID = [ x for x in GV.GID if x not in scored ]
        return render_template('scoring.html',TITLE="计算机网络打分系统 ",title="开始评分",GID_LIST=uGID,CUR_UID=uid)
    else:
        return error("您还未登陆！")

@app.route('/sc',methods=['POST'])
def sc():
    uid = request.cookies.get('uid')
    gid = int(request.form['gid'])
    score = int(request.form['score'])
    if int(score) < 0 or int(score) > 100:
        return "U"
    scored = scoringManager.getScoredlist(uid)
    if (gid in GV.GID) and (gid not in scored):
        scoringManager.score(uid,gid,score)
        return "OK"
    return "U"

if __name__ == '__main__':
    if "mode.server" in os.listdir("./"):
        # when a specific file in current dir,bind IP below  
        app.run(host="10.139.150.91",port=80)
    else:
        # local machine for test
        print(">>>Running on local machine.")
        app.run(host='127.0.0.1',port=80,debug=True)