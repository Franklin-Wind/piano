#coding=utf-8
import os 
import zipfile

def un_zip(file_name):  
    """unzip zip file"""  
    zip_file = zipfile.ZipFile(file_name)
    '''
    if os.path.isdir(file_name.split(".")[0]):  
        pass  
    else:  
        os.mkdir(file_name.split(".")[0])
    '''
    for names in zip_file.namelist():  
        zip_file.extract(names)  #加入到某个文件夹中 zip_file.extract(names,file_name.split(".")[0])
    zip_file.close()



filename="/home/franklin/Desktop/music.mxl"
portion = os.path.splitext(filename)
# 如果后缀是.txt
if portion[1] == ".mxl":  
    # 重新组合文件名和后缀名   
    newname = portion[0] + ".zip"   
    os.rename(filename,newname)
un_zip("/home/franklin/Desktop/music.zip")
