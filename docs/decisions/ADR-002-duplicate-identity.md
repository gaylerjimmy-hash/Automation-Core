# ADR-002: Duplicate Module IDs Are Not Silently Replaced

Status: Accepted

A module identity already bound to another active connection or incompatible session is quarantined.

Silent last-writer-wins behavior is prohibited because it makes identity theft look like a reconnect.
