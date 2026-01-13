tt-edsl

### Challenge

Programming a Tenstorrent accelerator using the Metallium SDK is a
complex task. Each accelerator is named after the processor hosted
on the accelerator. As an example, the Grayskull accelerator hosts
the Grayskull processor. The Grayskull processor is designed using
multiple Tensix processing elements. Tensix processing elements are
built using 5 RV32ILY cores (RV32I is the most basic 32 bit RISC-V
architecture; LY is a custom extension designed and implemented by
Tenstorrent for AI workloads).

Programming a Tensix processing element requires writing an independent
ISO C++17 program for each RV32ILY core. Each program is called a kernel.
Users may find managing and maintaining multiple individual programs for
Tensix processing elements burdensome.

### A Solution

tt-edsl aims to reduce the complexity of programming kernels for Tensix
processing elements by allowing users the ability to implement kernels
for each core inside the host program.

tt-edsl achieves this effect by offering users an embedded domain
specific language using ISO C++. tt-esdl exercises template
meta-programming techniques to craft a grammar using the C++ type
system.

tt-edsl is capable of describing the full suite of Tenstorrent's
existing accelerator API. This makes it possible to implement functions
(APIs) for Tenstorrent accelerators and then wrap them in tt-edsl
to maintain symmetry.

Kernels are implemented in the host program using data types that are
functionally equivalent to those found in an abstract syntax tree.
The compilation process verifies the type and syntactic correctness
of a kernel. Runtime execution of the host program generates the
kernel. The Tenstorrent SDK, called Metallium, takes care of compilation
and deployment of the kernel.

tt-edsl is "header-only" meaning users are not required to add a new
library into their existing Metallium projects. Users only need to add
a single include file "#include <tt_edsl/tt.hpp>".

tt-edsl provides optional functionality for mananaging kernels. Users
are able to store computed kernels into a cache directory in the path
"$HOME/.tt-edsl". tt-edsl provides functionality to manage the database.
Users can choose to "opt-into" using kernel cache management. Note this
feature maybe outdated as tt-metal currently provides support for this
functionality.

### INSTALLATION

To install tt-edsl without kernel cache support:

cmake ..
make
make install

To install tt-edsl with kernel cache support:

If berkeleydb is installed with cmake support..

cmake -DENABLE_BERKELEYDB_SUPPORT=ON ..
make
make install

If berkeleydb is installed without cmake support..

cmake -DENABLE_BERKELEYDB_SUPPORT=ON -DBerkeleyDB_ROOT_DIR=/opt/homebrew/opt/berkeley-db ..
make
make install

To build tt-edsl with example programs:

cmake -DBUILD_EXAMPLES=ON .. 
cmake -DBUILD_EXAMPLES=ON -DENABLE_BERKELEYDB_SUPPORT=ON .. 
cmake -DBUILD_EXAMPLES=ON -DENABLE_BERKELEYDB_SUPPORT=ON -DBerkeleyDB_ROOT_DIR=/opt/homebrew/opt/berkeley-db .. 

### Licenses

* Boost Version 1.0 (2022-)

### Date

12 November 2024

### Author

Christopher Taylor

### Notes

Tenstorrent is trademarked and owned by Tenstorrent AI ULC and its affiliated companies
