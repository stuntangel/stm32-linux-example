{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs:
  with inputs; 
  let
  system = "x86_64-linux";
  pkgs = import nixpkgs {
    inherit system;
    config.allowUnfree = true;
  };
  stm32cubemx = pkgs.callPackage ./stm32cubemx.nix { };
  
  stm32cubemxapp = pkgs.writeShellApplication {
    name = "stm32cubemx";
    text = "DISPLAY=:1 stm32cubemx";
    runtimeInputs = [stm32cubemx];
  };
  in
  {
        inherit stm32cubemxapp;
        defaultPackage.${system} = stm32cubemxapp;
#        devShells.default = pkgs.mkShell {
#          nativeBuildInputs = [
#            pkgs.bashInteractive
#            pkgs.clang-tools
#            pkgs.cmake
#            pkgs.gcc-arm-embedded
#            pkgs.ninja
#            pkgs.nixfmt-rfc-style
#            pkgs.picocom
#            pkgs.tio
#            stm32cubemx
#          ];
#        };
      };
}
