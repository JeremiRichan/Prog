import sys
import shutil

rep_dst = sys.argv[1]

shutil.copytree(".", rep_dst, dirs_exist_ok=True)