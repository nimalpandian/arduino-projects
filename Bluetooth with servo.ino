#include <Servo.h>
#include <SoftwareSerial.h>

Servo lockServo;
SoftwareSerial bluetoothSerial(2, 3); // RX, TX pins for Bluetooth module

int lockedPosition = 0;  // Angle for locked position
int unlockedPosition = 90; // Angle for unlocked position
int currentLockPosition = lockedPosition; // Current position of the lock

void setup() {
  lockServo.attach(9);  // Attach servo to pin 9
  bluetoothSerial.begin(9600); // Initialize Bluetooth communication
  lockServo.write(lockedPosition); // Initial position is locked
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    char command = bluetoothSerial.read();
    
    if (command == 'L') { // Command to unlock
      if (currentLockPosition == lockedPosition) {
        lockServo.write(unlockedPosition);
        currentLockPosition = unlockedPosition;
        bluetoothSerial.write("Unlocked");
      }
    } else if (command == 'L') { // Command to lock
      if (currentLockPosition == unlockedPosition) {
        lockServo.write(lockedPosition);
        currentLockPosition = lockedPosition;
        bluetoothSerial.write("Locked");
      }
    }
  }
}
