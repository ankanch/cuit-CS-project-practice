#coding=utf-8
from tornado.wsgi import WSGIContainer
from tornado.httpserver import HTTPServer
from tornado.ioloop import IOLoop
from index import app
from Utilities import gV as GV
http_server = HTTPServer(WSGIContainer(app))
http_server.listen(GV.BIND_PORT)  #flask默认的端口
IOLoop.instance().start()