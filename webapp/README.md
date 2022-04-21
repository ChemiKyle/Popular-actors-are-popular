# Setup

The web interface requires python 3.6+.

Install python dependencies via `pip`:

``` bash
pip install -r requirements.txt
```

## Prerequisites

Download the necessary datasets to the `data` directory and run `clean.R`. See the [data README](../data/README.org) for more information on data acquisition and pre-processing.

Compile the C++ application in `src` with:

``` bash
g++ -std=c++11 main.cpp
```

See the [CLI README](../src/README.md) for more information on compilation.

# Running

Note: the web interface is not fully functional on [Windows machines](https://github.com/ChemiKyle/Popular-actors-are-popular/issues/6), but does work on MacOS and Linux.

Once you have processed data and compiled the CLI API, you can spin up the flask app with:

```sh
python3 app.py
```

Once the application is running, point your favorite web browser at [localhost:5000](http://localhost:5000)
