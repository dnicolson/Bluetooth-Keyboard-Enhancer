# BluetoothKeyboardEnhancer

<p align="center">
  <img src="https://images-na.ssl-images-amazon.com/images/I/71t5d0fybDL._SL1500_.jpg" height="250">
</p>

This tool performs the following with an iOS keyboard:

- Sends an escape key event when the home key is pressed
- The emoji picker is invoked when Control-Command-Space is pressed

[Karabiner](https://pqrs.org/osx/karabiner/) is unable to do this, in fact Karabiner-Elements-12.1.0 causes this tool not to function.

## Installation

The easiest way to install is to use [Homebrew](https://brew.sh/):

`brew install dnicolson/bluetoothkeyboardenhancer/bluetoothkeyboardenhancer`

The following command will run the tool automatically:

`brew services start bluetoothkeyboardenhancer`

Alternatively, you can run `bke`  (or `bke&` to run in the background) from the terminal.

## Security

macOS Catalina has increased the security of keyboard input, the `bke` binary must now be added to the following panes under Security & Privacy > Privacy:
- Accessibility
- Input Monitoring

### Terminal
The `Secure Keyboard Entry` menu option must be disabled (it is by default).

### iTerm2
By default keyboard input is secure, the following command must run to enable `bke` (useful for `vim`):
`defaults write com.googlecode.iterm2 "Secure Input" 0` 

## Compilation

The following command will manually compile the binary:

`clang -framework IOKit -framework Carbon BluetoothKeyboardEnhancer.c -o bke`

## License

MIT License.
