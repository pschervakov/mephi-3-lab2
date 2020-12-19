import threading
import os
from flask import Flask, render_template, request

app = Flask(__name__)


def run_app():
    server = threading.Thread(target=app.run, kwargs={
        'host': '0.0.0.0',
        'port': '5050'
    })

    server.start()
    return server


@app.route('/alpha', methods=["POST", "GET"])
def alpha():
    if request.method == "GET":
        return render_template("./menu.html"), 200
    elif request.method == "POST":
        st = request.form["str"]
        type_ = request.form["type"]
        size = request.form["size"]
        return render_template("./menu.html", table=get_result(st, size, type_)), 200


def get_result(st, str_size, size_type):
    st_length = len(st.split())
    a = os.popen(
        f'/home/philip/projects/mephi_labs/mephi-3-lab2/cmake-build-debug/mephi_3_lab2_menu {st_length} "{st}" {str_size} {size_type}').read()
    return a


run_app()
