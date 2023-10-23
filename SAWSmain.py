from flask import Flask, request
import serial

app = Flask(__name)

# Define Arduino serial port (update with your Arduino's port)
arduino_serial = serial.Serial('/dev/ttyACM0', 9600)  # Use the correct port and baud rate

# Lookup tables for Clients and Statuses
client_table = {
    'WINAD01': 1,
    'UNRAIDFS01': 2,
    # You can add more clients if needed
}

status_table = {
    'High Temp': 1,
    'High CPU': 2,
    'Low Disk Space Available': 3,
    # You can add more statuses if needed
}

@app.route('/webhook', methods=['POST'])
def receive_webhook():
    data = request.get_json()

    if 'name' in data and 'status' in data:
        server_name = data['name']
        server_status = data['status']

        # Translate the server name and status into numeric format
        client_number = client_table.get(server_name, 0)  # Default to 0 if not found
        status_number = status_table.get(server_status, 0)  # Default to 0 if not found

        # Send the numeric format to the Arduino
        command = f'{client_number},{status_number}\n'
        arduino_serial.write(command.encode())

        return f"Received status update for {server_name}: {server_status}\n", 200
    else:
        return "Invalid request. Make sure to provide 'name' and 'status' parameters in the JSON data.\n", 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
