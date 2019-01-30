# iOSKeyboardEscapeKeyEnabler

iOS keyboards have a home key in place of an escape key, this tool enables the key to funcation as an escape key. [Karabiner](https://pqrs.org/osx/karabiner/) is unable to read this key, in fact Karabiner-Elements-12.1.0 causes this tool not to function.

## Installation

The easiest way to install is to use [Homebrew](https://brew.sh/):

`brew install https://raw.githubusercontent.com/dnicolson/iOSKeyboardEscapeKeyEnabler/master/ioskeyboardescapekeyenabler.rb`

The following command will run the tool automatically:

`brew services start ioskeyboardescapekeyenabler`

Alternatively, you can run `iOSKeyboardEscapeKeyEnabler`  (or `iOSKeyboardEscapeKeyEnabler&` to run in the background) from the terminal.

## Compiling

The following command will manually compile the binary:

`clang -framework IOKit -framework Carbon iOSKeyboardEscapeKeyEnabler.c -o iOSKeyboardEscapeKeyEnabler`

## License

Copyright © 2019 David Nicolson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
