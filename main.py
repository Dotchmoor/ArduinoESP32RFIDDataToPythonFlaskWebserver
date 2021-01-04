import os, json
from datetime import datetime
from flask import Flask, request

path = os.path.dirname(__file__)
saveDic = {}
name = ""

app = Flask(__name__)

@app.route("/", methods=["POST", "GET"])
def home():
    if request.method == "POST":
        name = ""

        UID = request.form.get('UID')
        UID = " ".join(UID.split(" ")[1:])
        print(UID)

        now = datetime.now()
        dt = now.strftime("%d/%m/%Y %H:%M:%S")
        print(dt)

        if UID in saveDic:
            with open(os.path.join(path, "data", "bekannteUIDs.csv"), "r", encoding="UTF-8") as UIDFile:
                for line in UIDFile:
                    splitLine = line.split(";")
                    print(splitLine)
                    if UID in splitLine:
                        name = splitLine[-1].split(" ")[-1]
                        print(name)

                with open(os.path.join(path, "data", "save.csv"), "a", encoding="UTF-8") as saveFile:
                    saveFile.write(name + "; " + saveDic[UID] + "; " + dt + "\n")
                    del saveDic[UID]
        else:
            saveDic[UID] = dt

        print(saveDic)

    return "NOTHING TO SEE HERE YET"
