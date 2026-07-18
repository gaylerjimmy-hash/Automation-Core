# Automation Core — Milestone 1 Skeleton

Milestone 1 proves one narrow vertical slice:

```text
Transport
    -> Connection Manager
    -> Frame Assembler
    -> Protocol Parser
    -> Protocol Validator
    -> Message Router
    -> Module Registry
    -> HELLO_ACK / ERROR
```

This repository is intentionally skeletal. The structure and interfaces exist so each component can be implemented and tested one at a time without turning `Core` into a god object.

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Milestone 1 Scope

Implemented later, one component at a time:

- HELLO
- HELLO_ACK
- ERROR
- connection IDs
- session IDs
- message IDs
- frame limits
- frame timeout handling
- protocol version validation
- duplicate identity quarantine
- CLI tracing
- exhaustive failure-path tests

Not included yet:

- MQTT
- TCP
- persistence
- process engine
- GUI
- command transactions
- capability discovery
- real serial I/O
