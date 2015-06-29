# Start here

This post will serve as a step 0 for Castalia beginners. Since Castalia is an Omnetpp based framework, the first step is to install Omnetpp. This [guide](http://pharos.ece.utexas.edu/wiki/index.php/How_to_Install_OMNeT%2B%2B_4.2.2_on_Ubuntu_12.04) will help you do that. Follow this [guide](https://forge.nicta.com.au/docman/view.php/301/593/Castalia+-+Installation.pdf) for setting up Omnet++ (given under Installing Omnet++ title) before installing Castalia.

## Compilation 

+ Clone Castalia-stable repository

 `git clone https://github.com/suriyadeepan/Castalia-stable`

+ Compile Castalia
```
  cd Castalia-stable
  ./makemake
  make -j$(nproc)
```

## Further Reading

Once you have successfully installed it, next thing to do is to open up the [Castalia Manual](https://forge.nicta.com.au/docman/view.php/301/592/Castalia+-+User+Manual.pdf) and spend time reading through Chapter 2, until you get bored. This will give you a good idea about the architecture and basic usage of scripts in Castalia.

## Simulation

Implementation of Application layer, Routing layer or MAC layer protocols should be done in C++ and placed inside the appropriate subdirectory under the src/node/communication/ directory. Let us start by running simulations using existing protocols that are already implemented in Castalia. Simulation scenarios can be created in the Simulation/ folder. It can be configured by using omnetpp.ini file. Go to _Simulation/radioTest/_. 

```
# assuming that you are in Castalia-stable folder
cd Simulation/radioTest
../../bin/Castalia -c General
```

Run the command given above. The Castalia script used above has a number of additional options which you can see using the _-h_ switch. The _-c_ switch selects the configuration that you want to run. _General_ refers to one of the configuration sections mentioned in _omnetpp.ini_ file. This is useful when you want to do multiple simulation runs with different set of configurations and also with a general set of global configurations. You can read about combining configurations and more, in the [Castalia Manual](https://forge.nicta.com.au/docman/view.php/301/592/Castalia+-+User+Manual.pd) : Chapter 3. 

## Configuration : omnetpp.ini
