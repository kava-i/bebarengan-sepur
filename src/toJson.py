import yaml, json
import os

files = []
for filename in os.listdir("factory"):
    if filename.endswith(".yaml"):
        path = "factory/"+filename
        files.append(path)

for path in files:
    print (filename)
    newPath = path.replace(".yaml", ".json")
    newPath = newPath[:8] + "jsons/"+ newPath[8:]
    with open(path, 'r') as yaml_in, open(newPath, "w") as json_out:
        yaml_object = yaml.safe_load(yaml_in) # yaml_object will be a list or a dict
        json.dump(yaml_object, json_out)
