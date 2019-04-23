# BluetoothKeyboardEnhancer

This tool performs the following with an iOS keyboard:

- Sends an escape key event when the home key is pressed
- The emoji picker is invoked when Control-Command-Space is pressed

[Karabiner](https://pqrs.org/osx/karabiner/) is unable to do this, in fact Karabiner-Elements-12.1.0 causes this tool not to function.

## Installation

The easiest way to install is to use [Homebrew](https://brew.sh/):

`brew install https://raw.githubusercontent.com/dnicolson/BluetoothKeyboardEnhancer/master/bluetoothkeyboardenhancer.rb`

The following command will run the tool automatically:

`brew services start bluetoothkeyboardenhancer`

Alternatively, you can run `BluetoothKeyboardEnhancer`  (or `BluetoothKeyboardEnhancer&` to run in the background) from the terminal.

## Compiling

The following command will manually compile the binary:

`clang -framework IOKit -framework Carbon BluetoothKeyboardEnhancer.c -o BluetoothKeyboardEnhancer`

## License

MIT License.
