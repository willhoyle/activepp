# activepp
C++ wrapper for Activetick data service to facilitate back testing and live trading

## Installation

#### Requirements
**activepp** only requires *cmake* and the *activetick* shared library

#### Getting started
```
sudo apt-get install cmake # skip this if you already have it
git clone https://github.com/willhoyle/activepp.git
cd activepp
mkdir build
cd build 
cmake ..
make
```

## Features
This library is essentially a high-level wrapper around the activetick library with built-in support for backtesting and optimizing strategies.

* Download data from the activetick servers
* Data management in HDF5 storage. activepp will handle all the work behind the scenes to store and organize all the tick data. We use this library internally to handle 3TB+ of data
* Optional compression for efficient disk storage
* Simple and intuitive API
* Fast backtesting and strategy optimization
* Live Trading: Seamlessly integrated through our activepp-python and activepp-node libraries 




