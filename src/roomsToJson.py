import yaml, json
import os

files = []
for filename in os.listdir("factory"):
    if filename.endswith(".yaml"):
        path = "factory/"+filename
        files.append(path)

for filename in files:
    print (filename)
    with open(filename, 'r') as yaml_in, open(filename.replace(".yaml", ".json"), "w") as json_out:
        yaml_object = yaml.safe_load(yaml_in) # yaml_object will be a list or a dict
        json.dump(yaml_object, json_out)
