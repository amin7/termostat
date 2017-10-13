#!/usr/bin/python3
import os
import sys

if 2!= len(sys.argv):
    print("no file name")
    os._exit(1)

FileName=sys.argv[1];

fo = open(FileName, "r")
filesize=os.path.getsize(FileName);
print("//converted from ",FileName," getsize=",filesize)

print( "const char* _",FileName.replace('.','_'),'_ PROGMEM ={\\',sep='')

writedsz=0;
for line in fo:
    writedsz+=len(line)
    converted_str=""
    for char in line:
        if(char==' '):
            converted_str+=' ';
        else:
            break;

    line=line.rstrip('\r\n').replace('"','\\\"').strip()
    converted_str+='"'
    if len(line) :
        converted_str+=line+'\\n'
    converted_str += '"\\'
    print(converted_str)

print( "};")
print( "// End",FileName,"writedsz",writedsz)
