# ADR-001: Every Request Carries a Message ID

Status: Accepted

Every request message includes `MSG`.

Responses echo the same `MSG` value.

Reason:

- deterministic request/response correlation
- traceable logging
- future transaction support
- cleaner retry handling
