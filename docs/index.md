# Serial Core guide

A successful transmit call accepts a frame. The link can still be transmitting when that call returns.

Read frame format and progress semantics before designing a polling loop.

- [Use the facade](api.md) for construction, results and optional capabilities.
- [Run the example](examples.md) to see the same API with a simulated resource.
- [Check portability](compatibility.md) for assumptions that belong to the target.
