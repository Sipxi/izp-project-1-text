from pynput import keyboard

# Initialize the state
alt_pressed = False

def on_press(key):
    global alt_pressed

    try:
        # Check if the Alt key is pressed
        if key == keyboard.Key.alt:
            alt_pressed = True

        # Simulate arrow keys based on WASD
        if alt_pressed:
            if key.char == 'w':
                print("Up Arrow")
                # Here you would use a library like pyautogui or similar to simulate the key press
            elif key.char == 'a':
                print("Left Arrow")
            elif key.char == 's':
                print("Down Arrow")
            elif key.char == 'd':
                print("Right Arrow")

    except AttributeError:
        # Handle special keys like 'alt', 'shift', etc.
        pass

def on_release(key):
    global alt_pressed

    # Check if the Alt key is released
    if key == keyboard.Key.alt:
        alt_pressed = False

# Set up the listener
with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
