class Bluetoothkeyboardenhancer < Formula
  desc "Enables the corner home button on an iOS keyboard to function as an escape key"
  homepage "https://github.com/dnicolson/BluetoothKeyboardEnhancer"
  url "https://github.com/dnicolson/BluetoothKeyboardEnhancer/archive/0.2.zip"
  sha256 "7fdcde4b27704a66b200acfc4db47dce2d8c9943499c0386f1a29e595b072452"

  def install
    system "clang -framework IOKit -framework Carbon BluetoothKeyboardEnhancer.c -o BluetoothKeyboardEnhancer"
    bin.install "BluetoothKeyboardEnhancer"
  end

  def plist; <<~EOS
    <?xml version="1.0" encoding="UTF-8"?>
    <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
    <plist version="1.0">
    <dict>
      <key>Label</key>
        <string>#{plist_name}</string>
      <key>ProgramArguments</key>
      <array>
        <string>#{bin}/BluetoothKeyboardEnhancer</string>
      </array>
      <key>RunAtLoad</key>
      <true/>
      <key>KeepAlive</key>
      <true/>
    </dict>
    </plist>
    EOS
  end
end
