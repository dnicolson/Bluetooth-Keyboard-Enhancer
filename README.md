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

`brew services restart bluetoothkeyboardenhancer` might need to be run after installation.

### Terminal
The `Secure Keyboard Entry` menu option must be disabled (it is by default).

### iTerm2
By default keyboard input is secure, the following command must run to enable `bke` (useful for `vim`):

`defaults write com.googlecode.iterm2 "Secure Input" 0`

## Limitations

- CGEvents are used to trigger some of the key commands, this means apps such as the Xcode Simulator will not respond to the escape key as they listen to the lower IOHID level.
- It seems that keyboards with the Airoha AB1108 integrated SoC produce incorrect values for Control-Command-Up and Control-Command-Space (https://github.com/dnicolson/BluetoothKeyboardEnhancer/issues/4), this [gist](https://gist.github.com/dnicolson/4c095d5f7662cfe0fb84c60c55fbc6e3) documents this in more detail.

## Compilation

The following command will manually compile the binary:

`clang -framework IOKit -framework Carbon BluetoothKeyboardEnhancer.c -o bke`

## License

MIT License.
