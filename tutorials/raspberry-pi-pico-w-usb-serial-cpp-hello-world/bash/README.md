# Bash examples

- [`install_homebrew.sh`](./install_homebrew.sh) — Download and run the Homebrew installer on macOS.
- [`install_dependencies.sh`](./install_dependencies.sh) — Install required build tools (cmake) and the ARM GCC toolchain via Homebrew.
- [`fetch_pico_sdk.sh`](./fetch_pico_sdk.sh) — Create a pico workspace, clone the Raspberry Pi pico-sdk repository, and initialize its submodules.
- [`set_pico_sdk_path.sh`](./set_pico_sdk_path.sh) — Add PICO_SDK_PATH to the user's zsh configuration and reload the shell environment.
- [`create_project_dir.sh`](./create_project_dir.sh) — Create and switch into the project directory for the example.
- [`prepare_build.sh`](./prepare_build.sh) — Prepare and clean the build directory before running the build.
- [`flash_uf2.sh`](./flash_uf2.sh) — Copy the generated UF2 file to the Pico's mass-storage mount point to flash the board.
- [`serial_screen.sh`](./serial_screen.sh) — Open a serial terminal to the Pico using screen at 115200 baud (replace device path as needed).
- [`serial_minicom.sh`](./serial_minicom.sh) — Open a serial terminal to the Pico using minicom at 115200 baud (replace device path as needed).

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/raspberry-pi-pico-w-usb-serial-cpp-hello-world)  
Parts used: [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
