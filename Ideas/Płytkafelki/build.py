import os, shutil, zipfile

os.system(r"iotapack pyk sol/pyk.cpp cpp in doc/pyk.pdf --zip --cfg cfg.yml -a sol/pykb1.cpp -a sol/pykb2.cpp -a sol/pyks1.cpp -a sol/pyks2.cpp -ps doc/pyk.tex")
os.system("pause")
