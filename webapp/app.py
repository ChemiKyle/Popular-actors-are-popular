#!/usr/bin/env python3

from flask import Flask, render_template, request, jsonify
import random
import time                     # buffer between simulated queries
import cpp_interface as cli
import pandas as pd             # using just to populate dropdown on frontend
import math
import string                   # used for python-side simulation of data

app = Flask(__name__)

# flag toggled on initial page load
structures_ready = False


@app.route('/', methods=['GET'])
def home():
    global structures_ready
    # empty maps serving as schemas
    hash_data = {
        "x": [],
        "y": [],
        "text": [],
        "name": "HashMap"
    }

    splay_data = {
        "x": [],
        "y": [],
        "text": [],
        "name": "Splay Tree"
    }

    # populate select2 dropdown to allow fuzzy searching of which actor to select
    df = pd.read_csv("../data/actors_with_titles.csv", nrows = 1000)

    return render_template(
        'index.html',
        hash_data = hash_data,
        splay_data = splay_data,
        structures_ready = structures_ready,
        dropdown_list = df.to_json()
    )


def getFromCpp(name):
    # HACK: interface to C++
    cli.write(p, name)

    hash_time = cli.read(p)
    splay_time = cli.read(p)

    response = {
        "name": name,
        "hash_time": hash_time,
        "splay_time": splay_time
    }
    return(response)

@app.route('/ajax', methods=['GET'])
def respond():
    name = request.args.get("search")
    response = getFromCpp(name)
    return jsonify(response)


# simulate searching for a handful of actors repeatedly
@app.route('/simulate', methods=['GET'])
def simulateSearches(n = 10):
    responses = {
        "name": [],
        "hash_time": [],
        "splay_time": []
    }
    popular_actors = [1, 10, 100]
    popular_actors = [1]
    for i in range(0, n):
        idx = i % len(popular_actors)
        name = popular_actors[idx]
        time.sleep(0.05)
        response = getFromCpp(f"nm{name}")

        responses['name'].append(name)
        responses['hash_time'].append(response['hash_time'])
        responses['splay_time'].append(response['splay_time'])

    return jsonify(responses)


@app.route('/buildStructures', methods=['GET'])
def buildStructures():
    # I'm aware global vars aren't best practice, but it's easy
    # the focus of this project is the data structure performance
    global p
    global structures_ready

    if (not structures_ready):
        # HACK: globally available object connected to CLI API
        # TODO: check available RAM and limit rows read accordingly
        # p = cli.start(["../src/a.out"])
        p = cli.start(["../src/a.out", "100000"])

        # HACK: flush stdout to avoid strange initial values
        build_time = cli.read(p)
        structures_ready = True

    return({
        'structures_ready': structures_ready,
        'build_time': build_time
         })


# early function used to test passing data to frontend
def simulateResponse(name):
    # NOTE: will need to interface to C++
    time1 = round(random.uniform(1, 10) * 1000, 3)
    time2 = round(random.uniform(1, 10) * 1000, 3)

    response = {
        "name": name,
        "time1": time1,
        "time2": time2
    }
    return(response)


@app.route('/getRandom', methods=['GET'])
def getRandomData(alpha = 0.01):
    hash_data, splay_data = generateRandomData(alpha = 0.005)
    response = {
        "hash_data": hash_data,
        "splay_data": splay_data
    }
    return(response)


# Used to simulate an idealized final graph
# HashMap was expected to take time within a range
# SplayTree was expected to appear as an exponentially decaying sine wave
def generateRandomData(alpha = 0.01):
    fake_hash_data = {
        "x": [],
        "y": [],
        "text": [],
        "name": "HashMap"
    }
    fake_splay_data = {
        "x": [],
        "y": [],
        "text": [],
        "name": "Splay Tree"
    }
    for i in range(1, 500):
        fake_hash_data["x"].append(i)
        fake_splay_data["x"].append(i)

        # decaying sine to ensure value converges to 0
        fake_time = 100_000 * abs( math.sin(random.uniform(0, 1)) ) * math.exp(-i * alpha) + 1
        fake_splay_data["y"].append(fake_time)

        fake_time = round(random.uniform(10, 50) * 1000, 3)
        fake_hash_data["y"].append(fake_time)

        fake_name = (''.join(random.choice(string.ascii_lowercase) for j in range(5)))
        fake_hash_data["text"].append(fake_name)
        fake_splay_data["text"].append(fake_name)

    return (fake_hash_data, fake_splay_data)


if __name__ == '__main__':
    app.run(debug = True)
