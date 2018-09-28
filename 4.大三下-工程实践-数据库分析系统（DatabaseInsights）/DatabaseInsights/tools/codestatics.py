import os
import sys

JAVA_SOURCE_PATH = "../DatabaseInsights/src/java"
JSP_SOURCE_PATH = "../DatabaseInsights/web"
JS_SOURCE_PATH = "../DatabaseInsights/web/static/oplib"

def countlines(fpath):
    with open(fpath,"r",encoding="utf-8") as f:
        return len(f.readlines())

linecount = {'java':0,'jsp':0,'js':0}
# stat for java source code
javacount = 0
for path, subdirs, files in os.walk(JAVA_SOURCE_PATH):
    for name in files:
        javapath = os.path.join(path, name)
        if javapath[::-1][:4][::-1] == "java":
            javacount+=1
            linc = countlines(javapath)
            linecount['java'] += linc
            print(linc," lines code in file ",javapath)

# stat for JSP pages
jspcount = 0
for path, subdirs, files in os.walk(JSP_SOURCE_PATH):
    for name in files:
        jsppath = os.path.join(path, name)
        if jsppath[::-1][:3][::-1] == "jsp":
            jspcount+=1
            linc = countlines(jsppath)
            linecount['jsp'] += linc
            print(linc," lines code in file ",jsppath)

# stat for javascript code
jscount = 0
for path, subdirs, files in os.walk(JS_SOURCE_PATH):
    for name in files:
        jspath = os.path.join(path, name)
        if jspath[::-1][:2][::-1] == "js":
            jscount+=1
            linc = countlines(jspath)
            linecount['js'] += linc
            print(linc," lines code in file ",jspath)

print("\n\n\nCode Stats(Excluding third party libary):\n=============================")
print("project contains",javacount,"java files,",jspcount,"JSP pages,",jscount,"non-third party javascript files.")
print("#total lines of code:",linecount['java'] + linecount['jsp'] + linecount['js'])
print("\t\t|--java:",linecount['java'],"\n\t\t|--jsp:",linecount['jsp'],"\n\t\t|--javascript:",linecount['js'])
print("=============================\n\n\n")