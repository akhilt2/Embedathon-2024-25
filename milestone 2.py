import websocket
import base64

SERVER_IP = "192.168.4.1"  # ESP32's default IP
PORT = 81

def decrypt_message(message):
    # To split the message into array seperated by newline
    message = message.split("\n")
    # To remove the ?= in the message
    lines = [i[2:] for i in message]

    new_lines = []
    for line in lines:
        new_line = ""
        position = 0
        for char in line:
            position += 1
            if position % 2 == 0:
                new_line += " " * int(char)
            else:
                new_line += "█" * int(char)
        new_lines.append(new_line)

    for line in new_lines:
        print(line)

def on_message(ws, message):
    print("Encoded message received from ESP32:")
    print(message)

    decoded_message = base64.b64decode(message)
    print("\nDecoded message:")
    print(decoded_message)

    print("\nDecrypted message:")
    decrypt_message(decoded_message.decode('utf-8', 'ignore'))

def on_error(ws, error):
    print(f"Error: {error}")

def on_close(ws, close_status_code, close_msg):
    print("Connection closed.")

def on_open(ws):
    print("Connected to ESP32 WebSocket server.")

if __name__ == "__main__":
    ws = websocket.WebSocketApp(f"ws://{SERVER_IP}:{PORT}",
                                 on_message=on_message,
                                 on_error=on_error,
                                 on_close=on_close)
    ws.on_open = on_open
    ws.run_forever()
