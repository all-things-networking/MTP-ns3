# MTP-ns-3

## Initialize

Run MTP-ns-3.sh to initialize ns-3 for MTP development. See file for full details.

Note that ns-3 is only configured to build the following modules:
- core
- network
- internet
- applications
- point-to-point
- modular-transport

## Develop

```
./ns3 build
./ns3 run <test>
```

## Versions

Package | Version
--- | ---
cmake | 3.22.1+
