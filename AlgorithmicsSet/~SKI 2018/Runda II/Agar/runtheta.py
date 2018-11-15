import os
app = input("app: ")
os.system(f"thetacheck -a {app} -d tests -rd 0.000000001 -t")