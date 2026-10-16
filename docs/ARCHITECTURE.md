# Architecture

## Purpose

FORDLink is the Ford manufacturer product face over Link. It is deliberately richer than the current BMW/Audi faces because the repository already owns a Ford-specific network, module, signal and procedure model.

## Dependency hierarchy

```text
Libraries
        ↓
       Link
        ↓
    FORDLink
```

`fordlink-core` links publicly against `Link::Core`. Generic transport, standards, diagnostic sequencing, safety and shared application behaviour remain in Link.

## Ford product core

The product core is split by responsibility:

- `src/network.c` — Ford network/lane model;
- `src/module.c` — module catalogue and identity;
- `src/identity.c` — product/vehicle identity helpers;
- `src/module_scan.c` — bounded manufacturer module probing;
- `src/signal.c` — Ford-specific signal metadata/model;
- `src/procedure.c` — Ford procedure metadata/contract;
- `src/fordlink.c` — product facade/version identity.

This separation prevents a growing manufacturer layer from turning into one undifferentiated database.

## Network model

FORDLink distinguishes HS-CAN, MS-CAN and additional profile-specific Ford network lanes. Standard OBD activity uses the normal Link/OBD lane. Enhanced lanes require explicit adapter capability and verified physical routing; the data model does not pretend one generic CAN path reaches every Ford module.

## Module discovery

The manufacturer scanner uses Link's shared ECU-probe/safety machinery. Ford-specific target candidates and interpretation stay here.

A module catalogue entry or known endpoint does not itself authorize every possible service. Discovery and procedure permissions remain bounded.

## Signals and procedures

Signals and procedures are separate domains. A decoded live-data item does not imply a service procedure is safe; a documented procedure does not make every parameter writable.

## Platform faces

Linux GTK4, Link-shared Windows Discover and native iPhone presentation all consume FORDLink::Core. Product identity remains local; shared application mechanics remain in Link.

## Version identity

Root VERSION and the public FORDLink version are checked for agreement. The smoke test also records the pinned Link version, making dependency drift visible.

## Tests

Dedicated tests cover network modelling, module catalogue, module scanning, signals, procedures and product smoke/dependency integration.

## Build boundaries

`BUILD_TESTING` is the caller-owned CMake switch. The product registers its own tests only when enabled and never rewrites that cache setting while adding Link. Link owns its test policy independently. Apple packages receive the actual checked-out Link commit through `LINK_SOURCE_REVISION`; a direct Xcode build without that input reports an unavailable revision instead of a stale hard-coded SHA. Manufacturer code and identity remain product-owned.
