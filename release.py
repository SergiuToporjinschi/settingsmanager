from platformio import util
import glob, shutil, os, sys
print '########### Run release script ###########'

config = util.load_project_config()


exampleFolder = config.get("common", "examples_folder")
version = config.get("common", "version").replace("\"","")

dirpath = os.getcwd()

def prepExamples():
    print 'Create examples folder %s' % (exampleFolder)
    if os.path.exists(exampleFolder):
        shutil.rmtree(exampleFolder)
    os.makedirs(exampleFolder)
    exampleFolderPath = exampleFolder + "/" + os.path.basename(dirpath)
    os.makedirs(exampleFolder + "/" + os.path.basename(dirpath))
    os.makedirs(exampleFolder + "/" + os.path.basename(dirpath) + "/data")
    return exampleFolderPath

def createExamples():
    exampleFolder = prepExamples()
    exampleFolderData = exampleFolder + "/data"
    print 'Copy main.cpp file'
    shutil.copy2('src/main.cpp', exampleFolder + "/main.cpp")
    os.rename(exampleFolder + "/main.cpp", exampleFolder + "/" + os.path.basename(dirpath) + ".ino")

    for file in glob.iglob('data/*.*'):
        print 'Copied file %s' % (file)
        shutil.copy2(file, exampleFolderData)

# replace version in library file
def createLibraryPropertiesFile():
    f = open("library.properties", "r")
    nf = open("library_.properties", "w+")
    for l in f:
        if l.startswith("version"):
            nf.write("version=%s\n" % version)
        else: 
            nf.write(l)
    f.close()
    nf.close()
    os.remove("library.properties")
    os.rename("library_.properties", "library.properties")

createExamples()
createLibraryPropertiesFile()

print '########### Finish release script ###########'
