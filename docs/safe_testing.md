# Safe Testing — CAN Bus Intrusion Detection System

## Test environment
Use only a disconnected, isolated CAN laboratory setup with test nodes or synthetic frame data. Never attach this prototype to a live vehicle network.

| Test | Input | Expected observation |
|---|---|---|
| Known identifier | Identifier in test allowlist | Logged as expected traffic |
| Unknown identifier | Synthetic identifier outside allowlist | Flagged for review |
| Normal rate | Frames within baseline | No rate alert |
| Elevated test rate | Controlled synthetic traffic above threshold | Rate alert recorded |
| Serial interruption | Disconnect USB serial in the lab | Receiver reports loss of input |
| Invalid serial record | Malformed test record | Parser rejects and logs the error |

## Metrics to record
- Total frames in test set
- Correctly flagged events
- False positives and false negatives
- Processing-time measurement method
- Serial data loss, if measured
- Test hardware and software versions

Do not claim accuracy or latency without raw results and a documented method. Alerts are diagnostic indicators, not proof of an attack.
