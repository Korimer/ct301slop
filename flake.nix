{
  description = "Generic C++ dev environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

      guiDeps = pkgs.symlinkJoin {
        name = "gui-deps";
        paths = [ pkgs.SDL2 pkgs.SDL2.dev pkgs.libx11.dev pkgs.xorgproto ];
      };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          gcc gnumake gdb cmake ninja pkg-config clang-tools
        ];

        buildInputs = with pkgs; [ SDL2 SDL2.dev libx11 ];

        shellHook = ''
          # Stable symlink at the flake root: ./.nix-deps -> /nix/store/...-gui-deps
          ln -sfn ${guiDeps} "$PWD/.nix-deps"

          # Write .clangd into the project with absolute paths
          cat > "$PWD/hw5_gui/.clangd" <<EOF
        CompileFlags:
          Add:
            - -I$PWD/hw5_gui/imgui
            - -I$PWD/hw5_gui/imgui/backends
            - -I$PWD/.nix-deps/include
            - -I$PWD/.nix-deps/include/SDL2
        EOF

          echo "C++ dev environment ready"
          echo "gcc: $(gcc --version | head -n1)"
          echo "sdl2: $(sdl2-config --version)"
        '';
      };
    };
}
