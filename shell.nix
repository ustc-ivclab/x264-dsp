{
  pkgs ? import <nixpkgs> { },
}:

with pkgs;
mkShell {
  name = "src";
  shellHook = ''
    if command -v cl6x &>/dev/null; then
      export C6X_C_DIR="$(dirname "$(dirname "$(realpath "$(command -v cl6x)")")")"
      C6X_C_DIR="$C6X_C_DIR/include;$C6X_C_DIR/lib"
    fi
  '';
}
