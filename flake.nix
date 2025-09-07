{
  description = "Python bindings to the ClickHouse SQL parser.";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";
  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }: let
  in
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
        overlays = [];
      };
    in {
      devShells.default = pkgs.mkShell {
        packages = [
          # General tooling
          pkgs.uv
          pkgs.just
          pkgs.alejandra
          # General c++ tooling
          pkgs.cmake
          pkgs.ccache
          pkgs.lldb
          pkgs.llvmPackages_19.llvm
          pkgs.llvmPackages_19.lld
          pkgs.llvmPackages_19.clang
          pkgs.llvmPackages_19.libcxx
          pkgs.llvmPackages_19.clang-tools
          # TODO: This is just for MacOS builds (I think?)
          pkgs.apple-sdk_15
          # Dependencies for ClickHouse c++ build
          pkgs.git
          pkgs.ccache
          pkgs.cmake
          pkgs.ninja
          pkgs.libtool
          pkgs.gettext
          pkgs.binutils
          pkgs.gnugrep
          pkgs.findutils
          pkgs.nasm
          pkgs.bash
        ];

        shellHook = ''
          export SDKROOT=${pkgs.apple-sdk_15}/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
          # LDFLAGS are used for linking against Nix libc++ libraries. Note that this can't be passed to the Clickhouse build
          export LDFLAGS="-L${pkgs.llvmPackages_19.libcxx.out}/lib"

          # Custom environment variables for CMake build (prefixed to avoid conflicts)
          export _CH_SQL_BUILD_APPLE_SDK_INCLUDE=${pkgs.apple-sdk_15}/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
          export _CH_SQL_BUILD_LIBCXX_INCLUDE=${pkgs.llvmPackages_19.libcxx.dev}/include/c++/v1
          export _CH_SQL_BUILD_LIBCXX_LIB=${pkgs.llvmPackages_19.libcxx.out}/lib

          echo "DevShell: using LLVM 19 clang + libc++ + Apple SDK 15"
          echo "CMake build paths:"
          echo "  Apple SDK headers: $_CH_SQL_BUILD_APPLE_SDK_INCLUDE"
          echo "  libc++ headers: $_CH_SQL_BUILD_LIBCXX_INCLUDE"
          echo "  libc++ libraries: $_CH_SQL_BUILD_LIBCXX_LIB"
        '';
      };
    });
}
