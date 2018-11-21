#!/usr/bin/python3
import os
import sys
import datetime
import argparse

fileExt={
    "html"  :"text/html",
    "xml"   :"text/xml",
    "js"    :"application/javascript",
    "css"   :"text/css",
    "json"  :"application/json"    
}
fileExtBinary={
    "png"  :"image/x-icon"
}

def convertFileName(fileName):
    return "_"+fileName.replace('.','_').replace('/','_')+"_"

def convertFile(fileName):
    fo = open(fileName, "r")
    filesize=os.path.getsize(fileName);
    print( "const char* ",convertFileName(fileName),' PROGMEM ={',sep='')

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

def convertFileBinary(fileName):
    fo = open(fileName, "rb")
    filesize=os.path.getsize(fileName);
    print( "const char PROGMEM ",convertFileName(fileName),'[] ={',sep='')

    ba = bytearray(fo.read())
    leng =len(ba);
    for x in ba:    
        print (''.join('0x{:02x}'.format(x)),sep='', end = '')
        leng=leng-1;
        if leng:
            print (',',sep='', end = '')
    print( "};")

#convertFile(FileName);

parser = argparse.ArgumentParser(description='no')
parser.add_argument('files', nargs='*', help='files to convert')
parser.add_argument('-D', dest='dir',   help='directory')

args = parser.parse_args()
#print(args)
fileList=[]
fileListBinary=[]
ignoredFiles=[]
for file in args.files:
    fileList.append(file)

if(args.dir!="None"):
    for file in os.listdir(args.dir):
        extension = os.path.splitext(file)[1][1:]
        if extension in fileExt:
            fileList.append(args.dir+file)
        if extension in fileExtBinary:
            fileListBinary.append(args.dir+file)
        else:
            ignoredFiles.append(args.dir + file)


print("#ifndef _FRONT_END_")
print("#define _FRONT_END_")
print("//converted  date time=", datetime.datetime.now())
cmdline='//cmd gen:'
for par in sys.argv:
    cmdline+=' '+str(par)
print (cmdline)

for file in fileList:
    convertFile(file)
#for file in fileListBinary:
#    convertFileBinary(file)
print("\n//converted list")
for file in (fileList+fileListBinary):
    extension = os.path.splitext(file)[1][1:]
    # file = file.strip("/")
    # try:
    #     content_type = fileExt[extension]
    # except:
    print ('//  CFrontendFS::add(server, "/'+os.path.split(file)[1]+ '", ct_'+extension+","+convertFileName(file)+");")
for file in ignoredFiles:
    print ("//file ignored "+file)
print("#endif")
print("//EOF")
