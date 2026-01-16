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
      llvmPackages = pkgs.llvmPackages_19;
      appleSdk = pkgs.apple-sdk_15;
      sdkRoot = "${appleSdk}/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk";
      sdkInclude = "${sdkRoot}/usr/include";
    in {
      devShells.default = pkgs.mkShell {
        packages =
          [
            # General tooling
            pkgs.uv
            pkgs.just
            pkgs.alejandra
            # General c++ tooling
            pkgs.cmake
            pkgs.ccache
            pkgs.lldb
            llvmPackages.llvm
            llvmPackages.lld
            llvmPackages.clang
            llvmPackages.libcxx
            llvmPackages.clang-tools
            # Dependencies for ClickHouse c++ build
            pkgs.git
            pkgs.ccache
            pkgs.cmake
            pkgs.ninja
            pkgs.libtool
            pkgs.libxml2
            pkgs.gettext
            pkgs.binutils
            pkgs.gnugrep
            pkgs.findutils
            pkgs.nasm
            pkgs.bash
            # Other dependencies for skbuild
            pkgs.openjdk_headless
            pkgs.libxslt
          ]
          ++ pkgs.lib.optionals pkgs.stdenv.isDarwin [
            appleSdk
          ]
          ++ pkgs.lib.optionals pkgs.stdenv.isLinux [
            pkgs.glibc
          ];

        shellHook = ''
          export CC=${llvmPackages.clang}/bin/clang
          export CXX=${llvmPackages.clang}/bin/clang++
          export LDFLAGS="-L${llvmPackages.libcxx.out}/lib"

          # For MacOS builds we also want to point cmake at the Apple SDK from Nix
          export SDKROOT=${pkgs.lib.optionalString pkgs.stdenv.isDarwin sdkRoot}

          # Custom environment variables for CMake build (prefixed to avoid conflicts with cmake and Nix utilities)
          export _CH_SQL_BUILD_APPLE_SDK_INCLUDE=${pkgs.lib.optionalString pkgs.stdenv.isDarwin sdkInclude}
          export _CH_SQL_BUILD_GLIBC_INCLUDE=${pkgs.lib.optionalString pkgs.stdenv.isLinux "${pkgs.glibc.dev}/include"}
          export _CH_SQL_BUILD_LIBCXX_INCLUDE=${llvmPackages.libcxx.dev}/include/c++/v1
          export _CH_SQL_BUILD_LIBCXX_LIB=${llvmPackages.libcxx.out}/lib

          # LibXml2 paths for CMake
          export LIBXML2_LIBRARY=${pkgs.libxml2.out}/lib/libxml2.so
          export LIBXML2_INCLUDE_DIR=${pkgs.libxml2.dev}/include/libxml2
          export LIBXSLT_LIBRARIES=${pkgs.libxslt.out}/lib
          export LIBXSLT_INCLUDE_DIR=${pkgs.libxslt.dev}/include/libxslt

          echo "🔧 DevShell for clickhouse-sql 🔧"
          echo ""
          echo "CMake build paths:"
          ${pkgs.lib.optionalString pkgs.stdenv.isDarwin ''
            echo "  Apple SDK headers: $_CH_SQL_BUILD_APPLE_SDK_INCLUDE"
          ''}
          ${pkgs.lib.optionalString pkgs.stdenv.isLinux ''
            echo "  glibc headers: $_CH_SQL_BUILD_GLIBC_INCLUDE"
          ''}
          echo "  libc++ headers: $_CH_SQL_BUILD_LIBCXX_INCLUDE"
          echo "  libc++ libraries: $_CH_SQL_BUILD_LIBCXX_LIB"
        '';
      };
    });
}
