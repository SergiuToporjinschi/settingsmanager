print('### Post-debug script ###############################')

from distutils.dir_util import copy_tree
import os
import glob

for files in glob.iglob('test/*.*'):
    if not os.path.basename(files).startswith('test'):
        print("del")
        os.remove(files)

print('### Finish Post-debug script ########################')
