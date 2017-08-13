--------------------------------------------------------
o2sim - The ALICE simulation software package for the o2
--------------------------------------------------------

This software is supposed to be structured more or less as follows

- event generator manager
  a class that takes care of the selection and configuration of the
  event generator

- condition manager
  a class that takes care of the

- detector manager

- decay manager

- ModuleManager
  The manager responsible of adding modules to the simulation.
  It should work with the help of detector-level managers that are delegated
  for the creation and configuration of the module itself.

  