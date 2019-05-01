from platformio import util
import glob, shutil, os, sys
print '########### Run release script ###########'

config = util.load_project_config()


exampleFolder = config.get("env:nodemcuv2", "examples_folder")
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

exampleFolder = prepExamples()
exampleFolderData = exampleFolder + "/data"

print 'Copy main.cpp file'
shutil.copy2('src/main.cpp', exampleFolder + "/main.cpp")
os.rename(exampleFolder + "/main.cpp", exampleFolder + "/" + os.path.basename(dirpath) + ".ino")

for file in glob.iglob('data/*.*'):
    print 'Copied file %s' % (file)
    shutil.copy2(file, exampleFolderData)

print '########### Finish release script ###########'
