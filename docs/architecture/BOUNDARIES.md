# Architectural Boundaries

- Modules own hardware.
- The Core coordinates process intent.
- Modules may perform local protective actions without Core approval.
- Modules do not implement process coordination.
- Transport moves bytes.
- Connection Manager owns physical connection state.
- Frame Assembler owns framing limits and timeout behavior.
- Parser converts validated frames into typed messages.
- Validator checks protocol rules.
- Registry owns module identity.
- Router routes; it does not decide policy.
- Response Builder creates protocol responses.
- Core wires components together.
