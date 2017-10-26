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
        if char==' ':
            converted_str+=' ';
        elif '\t' == char:
            converted_str += "    "  # tab => 4 space
        else:
            break;

    line=line.strip()
    if len(line):
        converted_str+='"';
        for char in line:
            if(("\""==char) or ("\\"==char) or ("\'"==char) ):
                converted_str+="\\"+char
            else:
                converted_str += char
        converted_str+='\\n"'
        print(converted_str, end="")
    print('\\')

print( "};")
print( "// End",FileName,"writedsz",writedsz)
