# encoding=utf-8
# Database Insights Sensitive Information Secure Tool
# This tool used for replace sensitive infomation before commit to github.
# Run with Python 3
#
import os
import sys
from securedinfo import DBIConfig


DBI_CONFIG_PATH = "../DatabaseInsights/src/java/dbi/utils/GlobeVar.java"


def findCfg(src):
    for key in DBIConfig.SI.keys():
        if key in src.split(" "):
            return True, key
    return False, ""


config = None
with open(DBI_CONFIG_PATH, "r",encoding="utf-8") as f:
    config = f.readlines()
for i, line in enumerate(config):
    status, key = findCfg(line)
    if status:
        sv = line.split("=")
        if len(sys.argv)  < 2:
            config[i] = sv[0] + "= " + DBIConfig.SI[key] + " ;" + sv[1][-2:]
        else:
            config[i] = sv[0] + "= \"FILL YOUR OWN DATA HERE\" ;" + sv[1][-2:]

with open(DBI_CONFIG_PATH,"w",encoding="utf-8") as f:
    f.writelines(config)