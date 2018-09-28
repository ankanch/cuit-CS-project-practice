#encoding=utf-8
# Database Insights Localization Generate Tool
# This tool used for generate localization language strings
# Run with Python 3
#
import xml.etree.ElementTree
import os
from datetime import datetime
"""
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Apr 10 2018
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 """
print("\n\n\tDatabase Insights Localization Generation Tool\n\t\t\thttp://akakanch.com\n\n\n")

# file name map between *.java and *.xml
# chinese.xml -----> langChinese.java 
 
# target language files dir
dir_template = "./code_templates/langClass.template"
dir_templateID = "./code_templates/langID.template"
dir_langPackage = "../DatabaseInsights/src/java/dbi/localization/"      # localization main folder
dir_langIDJava = dir_langPackage + "langID.java"
dir_langSrc = dir_langPackage + "langs/"                                # XML files of different languages
                                                                        # file name e.g. chinese.xml

sym_beg = "//@DBI_LANGGEN_TOOL_BEGIN"
sym_end = "//@DBI_LANGGEN_TOOL_END"

genLangTemplate = "result.put(langID.%s, \"%s\");"
genIDTemplate = "public static int %s = %s;"

OP = "DILGT|"
SOP = "\t  |-"

def load_template(path):
    head = ""
    tail = ""
    with open(path,"r",encoding="utf-8") as f:
        origin = f.read()
        news = origin[:origin.find(sym_beg)+len(sym_beg)]
        news += "\r\n\t"
        head = news
        tail = "\r\n\t" + origin[origin.find(sym_end):]
        return head,tail

def generateCode(source,target,head="",tail=""):
    """
    generate java code from tamplate with <source> based on <sym_beg> and <sym_end>.
    save java code to target file in <dir_langPackage> folder
    """
    with open( dir_langPackage + target ,"w",encoding="utf-8") as f:
        f.truncate()
        news = head + source + tail
        news = news.replace("@LANGUAGE_NAME",target[4:target.find('.')]).replace("@CREATE_TIME",str(datetime.now()))
        f.write(news)
        return  news
    return "error"

# load template
print(OP + "INFO|load template.")
temp_head,temp_tail = load_template(dir_template)
temp_head_id,temp_tail_id = load_template(dir_templateID)


# start generate
# list language files
print(OP + "INFO|listing language files...")
langxmls = os.listdir(dir_langSrc)
print(SOP,"INFO|Found:")
for n in langxmls:
    print(SOP,"\t-",n)

# start reading lang xmls and processing 
idx = 2000         # ID sequence
dict_keys = {}
dict_keysref = {}
record_id = True
print(OP + "INFO|Start processing..")
for langxml in langxmls:
    print(OP + "INFO|Generting ",langxml,"...")
    
    # read and parse xml
    langset = xml.etree.ElementTree.parse(dir_langSrc + langxml).getroot()

    # parse lang ID set
    print(SOP,"INFO|parsing... ")
    lset = langset.findall('l')

    # record all ids then generate static integer
    if record_id:
        keys = [ l.get("id") for l in lset ]
        for k in keys:
            dict_keys[k] = idx
            dict_keysref[k] = 1
            idx += 1
        record_id = False

    # generate
    print(SOP,"INFO|generating strings... ",end="\t")
    lang = [ genLangTemplate%( l.get("id"), l.get("value") ) for l in lset ]
    print("-done")  

    # generate source code
    langstr = "\n\t".join(lang)
    print(SOP,"INFO|generating Java code...")
    fname = "lang" + langxml[:1].upper() + langxml[1:langxml.find(".")] + ".java"
    generateCode(langstr, fname ,temp_head,temp_tail)
    print(SOP,"INFO|",langxml,">done.")

# generate langID.java
print(OP,"INFO|Generating langID.java...")
langIDs = ""
for k in dict_keys.keys():
    langIDs += "\n\t" +  genIDTemplate%(k,dict_keys[k])
generateCode(langIDs, "langID.java" ,temp_head_id,temp_tail_id)

print(OP + "INFO|Code has been generated successfully!\n\n")




