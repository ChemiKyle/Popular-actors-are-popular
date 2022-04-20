# Setup

The web interface requires python 3.6+.

Install python dependencies via `pip`:

``` bash
pip install -r requirements.txt
```

Download the necessary datasets to the `data` directory and run `clean.R`. See the [data README][../data/README.org] for more information.

Compile the C++ application in `src` with:

``` bash
g++ -std=c++11 main.cpp
```


# Running
You can spin up with `python3 app.py`.  
Once the application is running, point your favorite web browser at [localhost:5000](locahost:5000)
