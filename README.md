# MTP-ns-3

## Initialize

Run `init.sh` to initialize ns-3 for MTP development. See file for full details.

Note that ns-3 is configured to only build the following modules:
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

Ubuntu 22.04.04 LTS (green05 in SYN cluster)

Package | Version
--- | ---
build-essential | N/A
cmake | 3.22.1+
