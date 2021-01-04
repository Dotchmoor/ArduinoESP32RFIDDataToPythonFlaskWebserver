from flask import Flask, request

app = Flask(__name__)


@app.route("/", methods=["POST", "GET"])
def home():
    if request.method == "POST":
        UID = request.form.get('UID')

        print(UID)

    return "NOTHING TO SEE HERE YET"
