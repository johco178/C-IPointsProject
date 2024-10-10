import sys
import time
import os

#Comment
def log_message(message):
    with open("python_debug.log", "a") as log_file:
        log_file.write(f"{message}\n")

log_message("Script started")
log_message(f"Python version: {sys.version}")
log_message(f"Script arguments: {sys.argv}")
log_message(f"Current working directory: {os.getcwd()}")

try:
    import winsound
    log_message("Successfully imported winsound")
except ImportError as e:
    log_message(f"Failed to import winsound: {e}")

def play_sound(filename):
    log_message(f"Attempting to play {filename}")
    if not os.path.exists(filename):
        log_message(f"File does not exist: {filename}")
        return
    try:
        winsound.PlaySound(filename, winsound.SND_FILENAME | winsound.SND_ASYNC | winsound.SND_LOOP)
        log_message("PlaySound function called successfully")
    except Exception as e:
        log_message(f"Error playing sound: {e}")

if __name__ == "__main__":
    if len(sys.argv) > 2 and sys.argv[1] == "play":
        audio_file = sys.argv[2]
        log_message(f"Attempting to play: {audio_file}")
        play_sound(audio_file)
        log_message("After play_sound call")
        while True:
            time.sleep(1)
    else:
        log_message("Invalid arguments. Use 'play <filename>'")

log_message("Script ended")