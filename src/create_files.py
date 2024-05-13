import os

new_dir = os.path.join(os.path.dirname(__file__), "files/");

try:
    os.mkdir(new_dir);
except:
    pass

f = open(os.path.join(new_dir, "user.json"), "w");
f.write("{}")
f.close();
