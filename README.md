# Asynchronous pqxx

This is just a little example project for how to use the asynchronous networking features of libpqxx with my C++ coroutine libraries. A recent clang or gcc compiler is required.


## Trying it out

```bash
git clone git@github.com:KayEss/pqxx-async.git --recursive
cd pqxx-async
cmake -B build.tmp .
make -C build.tmp
```

Further examples can be found in [config-builds](./config-builds).

The example can be run straight from the build directory:

```bash
./build.tmp/examples/simple
```

Connection options can be provided through the environment as described in the libpq documentation.

```bash
PGUSER=postgres ./build.tmp/examples/simple
```
