{
  description = "Python bindings to the ClickHouse SQL parser.";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";
  outputs = {
    self,
    nixpkgs,
    flake-utils,
}:
let overlay = (import nix/clickhouse-parser.nix);
in
    flake-utils.lib.eachDefaultSystem (system: let
        pkgs = import nixpkgs { inherit system; overlays = [ overlay  ]; };
    in {
        devShells.default = pkgs.mkShell {
            packages = [
                pkgs.just
                pkgs.python3
                pkgs.alejandra
                # pkgs.cmake
                # pkgs.findutils
            ];
        };
        packages.clickhouseParser = pkgs.clickhouse-parser-lib;
    });
}
