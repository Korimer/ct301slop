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
        # tools that run on the build machine
        nativeBuildInputs = with pkgs; [
          gcc
          gnumake
          gdb
          cmake
          ninja
          pkg-config
          clang-tools
        ];

        # libraries you compile and link against
        buildInputs = with pkgs; [
          SDL2
          SDL2.dev
          libx11          # X11/Xlib.h (needed by SDL_syswm.h)
        ];

        shellHook = ''
          echo "C++ dev environment ready"
          echo "gcc: $(gcc --version | head -n1)"
          echo "sdl2: $(sdl2-config --version)"
        '';
      };
    };
}
