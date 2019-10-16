print('### Pre-debug script ###############################')

from distutils.dir_util import copy_tree
import shutil, os

copy_tree("src" , "test")
os.remove("test/main.cpp")

print('### Finish Pre-debug script ########################')
