{
  description = "Generic C++ dev environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          gcc
          gdb
          cmake
          ninja
          pkg-config
          clang-tools
        ];

        shellHook = ''
          echo "C++ dev environment ready"
          echo "gcc: $(gcc --version | head -n1)"
        '';
      };
    };
}
