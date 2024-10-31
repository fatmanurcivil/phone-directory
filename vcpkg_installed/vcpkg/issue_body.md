Package: libpq[core,lz4,openssl,zlib]:x64-linux@16.4

**Host Environment**

- Host: x64-linux
- Compiler: GNU 13.2.0
-    vcpkg-tool version: 2024-09-30-ab8988503c7cffabfd440b243a383c0a352a023d
    vcpkg-scripts version: 2ddc10c8a 2024-10-07 (12 hours ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached postgresql-16.4.tar.bz2.
-- Cleaning sources at /home/fatmanur/.vcpkg-clion/vcpkg/buildtrees/libpq/src/tgresql-16-0b2040c781.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source /home/fatmanur/.vcpkg-clion/vcpkg/downloads/postgresql-16.4.tar.bz2
-- Applying patch unix/installdirs.patch
-- Applying patch unix/fix-configure.patch
-- Applying patch unix/single-linkage.patch
-- Applying patch unix/no-server-tools.patch
-- Applying patch unix/mingw-install.patch
-- Applying patch unix/python.patch
-- Applying patch windows/macro-def.patch
-- Applying patch windows/win_bison_flex.patch
-- Applying patch windows/msbuild.patch
-- Applying patch windows/spin_delay.patch
-- Applying patch android/unversioned_so.patch
-- Using source at /home/fatmanur/.vcpkg-clion/vcpkg/buildtrees/libpq/src/tgresql-16-0b2040c781.clean
-- Found external ninja('1.11.1').
-- Getting CMake variables for x64-linux
-- Getting CMake variables for x64-linux-dbg
-- Getting CMake variables for x64-linux-rel
CMake Error at scripts/cmake/vcpkg_configure_make.cmake:721 (message):
  libpq requires autoconf from the system package manager (example: "sudo
  apt-get install autoconf")
Call Stack (most recent call first):
  buildtrees/versioning_/versions/libpq/dcaa1ec8552b8ef987d6d80f708b8828bcd795eb/portfile.cmake:115 (vcpkg_configure_make)
  scripts/ports.cmake:192 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "ddd-test",
  "version": "1.0.0",
  "builtin-baseline": "2ddc10c8afa00a762a69f21f6427849fe906ede0",
  "dependencies": [
    {
      "name": "crow"
    },
    {
      "name": "nlohmann-json"
    },
    {
      "name": "libpqxx"
    },
    {
      "name": "libpq"
    }
  ]
}

```
</details>
