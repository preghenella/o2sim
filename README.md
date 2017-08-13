# o2sim - The ALICE simulation software package for the o2

* `o2sim/o2sim`

   This is the executable.

* `Core/ConfigurationManager`

   The base class that establishes the protocol used by the configuraton managers and which provides communication.

* `Core/RunManager`

   This class is the top node of the configuration stack. It is responsible to steer the main configuration managers.

* `SimulationManager/SimulationManager`

   This class is the main manager responsible to configure the basics of the simulation run.

* `ModuleManager/ModuleManager`

   This class is the main manager responsible to configure and add modules to the simulation. It works with the help of detector-level managers that are delegated for the actual configuration and creation of the module itself. The delegates must comply with the `ModuleManagerDelegate` protocol.
  
* `GeneratorManager/GeneratorManager`

   This class is the main manager responsible to configure and add event generators to the simulation. It works with the help of generator-level managers that are delegated for the actual configuration and creation of the generator itself. The delegates must comply with the `GeneratorManagerDelegate` protocol.
  
