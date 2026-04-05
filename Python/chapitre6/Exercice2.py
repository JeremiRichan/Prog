import os
import sys
import pwd
for d in sys.argv[1:]:
    for root, _, files in os.walk(d):
        for f in files:
            p = os.path.join(root, f)
            try:
                s = os.stat(p)
                if s.st_size > 1048576:
                    print(f"{p} {pwd.getpwuid(s.st_uid).pw_name}")
            except:
                pass