import bluetooth

def find_device_by_name(device_name):

    # Discover available Bluetooth devices
    devices = bluetooth.discover_devices(lookup_names=True)

    # Iterate over the devices and find the one with the given name
    for address, name in devices:

        if name == device_name:
        
            return address

    # If no device with the given name is found, return None
    return None

def send_data_to_bluetooth_device(device_address, data):

    # Create the client socket
    client_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)

    try:

        # Connect to the device
        client_socket.connect((device_address, 1))

        # Send the data
        client_socket.send(data)

        print(f"Dato '{data}' fue enviado exitosamente al dispositivo con dirección {device_address}.")

    except bluetooth.btcommon.BluetoothError as error:
        
        print(f"Ocurrió un error al conectar con el dispositivo: {error}")

    finally:
        
        # Close the socket
        client_socket.close()

# Set the name of the ESP32 device
esp32_name = "ESP32Tx"

# Find the address of the ESP32 device by its name
esp32_address = find_device_by_name(esp32_name)

if esp32_address is not None:

    # Set the data to be sent
    data = "B"

    # Call the function to send the data to the ESP32 device
    send_data_to_bluetooth_device(esp32_address, data)

else:
    
    print(f"No se encontró ningún dispositivo con el nombre {esp32_name}.")