BitNexus (BitcoinNode Community Take Over Coin)
===============================

http://www.bitnexus.online   http://btnodes.online
http://explorer.bitnexus.online
https://bitcointalk.org/index.php?topic=4541359.0
https://twitter.com/btnx_bitnexus

What is BitNexus (BitcoinNode)?
----------------

BitNexus (BTNX) is a community take over coin, which rebanded from BitcoinNode(BTN) with an alternative architecture. BTNX-network is based on Nodes, also known as Master Nodes.

### Description:

1. Cryptographically secured
2. Built on top of Bitcoin and Dash
3. Master Nodes get 50% to %200 reward depends on their level.

### Highlights:

1. Fast
2. Secure
3. Anonymous
4. Multi-Level Masternodes
5. X16S Algorithm 

### Specifications:

1. Block time: 150 sec.
2. Block reward 20 BTNX. For miner (POW: X16S) 50% (10 BTNX). 
3. Supply: 21,000,000
4. Two level of Master Node.
   - Level 1 : Required 10,000 BTN get 50%  of reward. (10 BTNX)
   - Level 2 : Required 50,000 BTN get 200% of reward. (40 BTNX)
5. 0.0% Premine (Developer Premine had blocked.)
6. Dark Gravity Wave

Additional information, wallets, specifications & roadmap: http://btnodes.online

License
-------

BitNexus Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/btnodes/btnodes/tags) are created to indicate new official,
stable release versions of BitcoinNode Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/doc/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows
and Linux, OS X, and that unit and sanity tests are automatically run.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
